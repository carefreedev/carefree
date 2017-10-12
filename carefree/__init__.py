# CareFREE_objects :: MODELED C++ w/Python @<3
#
# Copyright (C) 2011-2017 Stefan Zimmermann <user@zimmermann.co>
#
# CareFREE_objects is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# CareFREE_objects is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with CareFREE_objects.  If not, see <http://www.gnu.org/licenses/>.

"""
MODELED C++ w/Python @<3
"""

from carefree_config import CAREFREE_HOME, CAREFREE_PYTHON_HOME, Lib
from path import Path

import Boost
from Boost import TOOLSET

import carefree_source
from .Source import Source

__carefree = __import__('zetup').toplevel(__name__, [
    'CAREFREE_HOME', 'CAREFREE_PYTHON_HOME',
    'TOOLSET', 'SOURCE', 'PREFIX', 'INCLUDE', 'LIB',
    'Source',
])


def resolve():
    """
    Search installed libraries, and build and install if not found.
    """
    source = Source(Path(carefree_source.__file__).dirname())
    prefix = (CAREFREE_HOME / __carefree.__version__.replace('.', '_') /
              TOOLSET)
    if prefix.exists() and not __carefree.__version__.parsed.is_prerelease:
        return prefix

    source.build(prefix=prefix.makedirs_p())
    return prefix, source


PREFIX, SOURCE = resolve()

INCLUDE = [PREFIX / 'include']

LIB = Lib([PREFIX / 'lib'])
