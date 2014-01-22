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

"""libcarefree_objects

.. moduleauthor:: Stefan Zimmermann <zimmermann.code@gmail.com>
"""
__all__ = 'PREFIX', 'INCLUDE_PATH', 'LIB_PATH',

from path import path as Path

from .libcfo import __version__, __requires__


# Determine the location prefix of libcarefree_object's data_files
PREFIX = Path(__path__[0])
with PREFIX:
    if Path('PREFIX').exists():
        with Path('PREFIX').open() as f:
            PREFIX = Path(f.read().strip())

INCLUDE_PATH = PREFIX.joinpath('include')

LIB_PATH = PREFIX.joinpath('lib')
