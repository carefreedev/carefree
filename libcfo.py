# carefree-objects
#
# a thread-safe object manager extension for c++
#
# Copyright (C) 2011-2013 Stefan Zimmermann <zimmermann.code@gmail.com>
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

import os
from pkg_resources import parse_requirements
from subprocess import Popen

from path import path as Path


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
        env = dict(os.environ)
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
