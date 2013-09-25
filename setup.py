import sys
import os
from subprocess import Popen

from pkg_resources import require
try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

REQUIRES = open('requirements.txt').read().strip().split('\n')

PYTHON_SHORT_VERSION = '%i%i' % tuple(sys.version_info[:2])

VERSION = open('VERSION').read().strip()

PACKAGE_DIR = '.'
# Gets the lib/header files if building an egg
PACKAGE_DATA = []

# Gets the lib/header files for installing to sys.prefix
# if doing normal build/install
DATA_FILES = []

# Create data file lists if some build/install cmd was given
if any(cmd in sys.argv for cmd in ('build', 'install', 'bdist_egg')):
    require(REQUIRES)

    from path import path as Path

    # Process the header templates and compile the libs
    for cmd in [
      ['scons', '-c', 'SHARED=yes', 'STATIC=yes'],
      ['scons', 'DEBUG=yes', 'SHARED=yes', 'STATIC=yes'],
      ]:
        print(' '.join(cmd))
        if Popen(cmd).wait():
            sys.exit(1)

    PACKAGE_DIR = Path(PACKAGE_DIR)

    if not 'bdist_egg' in sys.argv:
        PREFIX = Path(sys.prefix).abspath()
        # Store sys.prefix location (where data_files are installed)
        # as part of package_data.
        # Can later be accessed with libcarefree_objects.PREFIX
        with open('PREFIX', 'w') as f:
            f.write(PREFIX)
        PACKAGE_DATA.append('PREFIX')

    INCLUDE_FILES = []
    with Path('include'):
        for dirpath, dirnames, filenames in os.walk('.'):
            if filenames:
                abspath = Path(dirpath).abspath()
                INCLUDE_FILES.append((dirpath, [
                  abspath / fn for fn in filenames]))

    with Path('lib'):
        LIB_FILES = [
          Path('libcarefree-python-py%s.%s' % (PYTHON_SHORT_VERSION, ext)
               ).abspath()
          for ext in ('a', 'so')]

    if not 'bdist_egg' in sys.argv:
        # Install libs/headers as data_files to sys.prefix
        for dirpath, filenames in INCLUDE_FILES:
            DATA_FILES.append(
              (PREFIX / 'include' / dirpath, filenames))
        DATA_FILES.append((PREFIX / 'lib', LIB_FILES))
    else:
        # Install libs/headers as package_data
        for dirpath, filepaths in INCLUDE_FILES:
            for path in filepaths:
                PACKAGE_DATA.append(PACKAGE_DIR.relpathto(path))
        for path in LIB_FILES:
            PACKAGE_DATA.append(PACKAGE_DIR.relpathto(path))

setup(
  name='libcarefree-objects',
  version=VERSION,
  description=(
    "A thread-safe object manager extension for C++"
    ),
  author='Stefan Zimmermann',
  author_email='zimmermann.code@gmail.com',

  url='http://bitbucket.org/StefanZimmermann/carefree-objects',

  license='LGPLv3',

  install_requires=REQUIRES,

  package_dir={
    'libcarefree_objects': '.',
    },
  packages=[
    'libcarefree_objects',
    ],
  package_data={
    'libcarefree_objects': PACKAGE_DATA,
    },

  data_files=DATA_FILES,
  )