import sys
import os
from subprocess import Popen

from distutils.core import setup

REQUIRES = [
  'path.py',
  'jinja-tools >= 0.1a6',
  ]

PYTHON_SHORT_VERSION = '%i%i' % tuple(sys.version_info[:2])

VERSION = open('VERSION').read().strip()

DATA_FILES = []

if any(cmd in sys.argv for cmd in ('build', 'install')):
    from path import path as Path

    for cmd in [
      ['scons', '-c', 'SHARED=yes', 'STATIC=yes'],
      ['scons', 'DEBUG=yes', 'SHARED=yes', 'STATIC=yes'],
      ]:
        print(' '.join(cmd))
        if Popen(cmd).wait():
            sys.exit(1)

    PREFIX = Path(sys.prefix).abspath()

    INCLUDE_FILES = []
    with Path('include'):
        for dirpath, dirnames, filenames in os.walk('.'):
            abspath = Path(dirpath).abspath()
            INCLUDE_FILES.append((dirpath, [
              abspath.joinpath(fn) for fn in filenames]))

    DATA_FILES.extend(
      (PREFIX.joinpath('include', dirpath), filenames)
      for dirpath, filenames in INCLUDE_FILES)

    DATA_FILES.append((PREFIX.joinpath('lib'), [
      'libcarefree-python-py%s.%s' % (PYTHON_SHORT_VERSION, ext)
      for ext in ('a', 'so')]))

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

  setup_requires = REQUIRES,

  data_files = DATA_FILES,
  )
