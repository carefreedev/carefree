# carefree-objects
#
# a thread-safe object manager extension for c++
#
# Copyright (C) 2011-2014 Stefan Zimmermann <zimmermann.code@gmail.com>
#
# carefree-objects is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# carefree-objects is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with carefree-objects.  If not, see <http://www.gnu.org/licenses/>.

"""libcfo

.. moduleauthor:: Stefan Zimmermann <zimmermann.code@gmail.com>
"""
__all__ = ['PREFIX', 'INCLUDE_PATH', 'LIB_PATH']

import sys
import os
from subprocess import Popen

from pkg_resources import parse_requirements

from path import Path


PREFIX = Path(__file__).abspath().dirname()

with PREFIX:
    __version__ = open('VERSION').read().strip()

    __requires__ = []
    with open('requirements.txt') as f:
        for req in f.readlines():
            req = req.strip()
            if req:
                __requires__.append(req)
    del f, req

    __requires__ = list(parse_requirements(__requires__))

    if Path('SConstruct').exists():
        env = dict(os.environ, PYTHONPATH=os.pathsep.join(sys.path))
        try:
            import libarray_ptr
        except ImportError:
            pass
        else:
            env['CPPFLAGS'] = '-I%s %s' % (
              str(libarray_ptr.INCLUDE_PATH), env.get('CPPFLAGS', ''))
        if Popen(['scons', 'DEBUG=yes'], env=env).wait():
            raise RuntimeError
        del env


INCLUDE_PATH = PREFIX / 'include'

LIB_PATH = PREFIX / 'lib'


def setup_keywords(dist):
    """Create libcarefree_objects data file lists
       and add to setup keywords.
    """
    PYTHON_SHORT_VERSION = '%i%i' % tuple(sys.version_info[:2])

    LIB_PACKAGE = 'libcfo'
    LIB_PACKAGE_DIR = '.'
    # Also gets the lib/header files if building an egg
    LIB_PACKAGE_DATA = ['VERSION', 'requirements.txt']
    # Gets the lib/header files for installing to sys.prefix
    # if doing normal build/install
    LIB_DATA_FILES = []

    LIB_PACKAGES = [LIB_PACKAGE]

    try:
        import libarray_ptr
    except ImportError:
        pass
    else:
        os.environ['CPPFLAGS'] = '-I%s %s' % (
          str(libarray_ptr.INCLUDE_PATH), os.environ.get('CPPFLAGS', ''))

    # Process the header templates and compile the libs
    env = dict(os.environ, PYTHONPATH=os.pathsep.join(sys.path))
    for cmd in [
      ## ['scons', '-c', 'SHARED=yes', 'STATIC=yes'],
      ['scons', 'DEBUG=yes', 'SHARED=yes', 'STATIC=yes'],
       ## 'PYTHON=%s' % sys.executable],
      ]:
        print(' '.join(cmd))
        if Popen(cmd, env=env).wait():
            sys.exit(1)

    LIB_PACKAGE_DIR = Path(LIB_PACKAGE_DIR)

    if 'bdist_egg' not in sys.argv:
        PREFIX = Path(sys.prefix).abspath()
        # Store sys.prefix location (where data_files are installed)
        # as part of package_data.
        # Can later be accessed with libcarefree_objects.PREFIX
        with open('PREFIX', 'w') as f:
            f.write(PREFIX)
        LIB_PACKAGE_DATA.append('PREFIX')

    INCLUDE_FILES = []
    with Path('include'):
        for dirpath, dirnames, filenames in os.walk('.'):
            if filenames:
                abspath = Path(dirpath).abspath()
                INCLUDE_FILES.append((dirpath, [
                  abspath / fn for fn in filenames]))

    LIB_FILES = []
    with Path('lib'):
        for suffix in [
          'types',
          'python-py%s' % PYTHON_SHORT_VERSION,
          ]:
            LIB_FILES.extend(
              Path('libcarefree-%s.%s' % (suffix, ext)
                   ).abspath()
              for ext in ('a', 'so'))

    if 'bdist_egg' not in sys.argv:
        # Install libs/headers as data_files to sys.prefix
        for dirpath, filenames in INCLUDE_FILES:
            LIB_DATA_FILES.append(
              (PREFIX / 'include' / dirpath, filenames))
        LIB_DATA_FILES.append((PREFIX / 'lib', LIB_FILES))
    else:
        # Install libs/headers as package_data
        for dirpath, filepaths in INCLUDE_FILES:
            for path in filepaths:
                LIB_PACKAGE_DATA.append(LIB_PACKAGE_DIR.relpathto(path))
        for path in LIB_FILES:
            LIB_PACKAGE_DATA.append(LIB_PACKAGE_DIR.relpathto(path))

    dist.package_dir[LIB_PACKAGE] = LIB_PACKAGE_DIR
    dist.packages += LIB_PACKAGES

    dist.package_data = {
      'cfo.jinja.macros': [
        'cfo',
        ],
      LIB_PACKAGE: LIB_PACKAGE_DATA,
      }
    dist.data_files = LIB_DATA_FILES
