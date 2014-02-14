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

"""cfo.jinja.macros

.. moduleauthor:: Stefan Zimmermann <zimmermann.code@gmail.com>
"""

__all__ = ['SEARCH_PATH', 'LOADER', 'CFO']

from path import path as Path

import jinja2


SEARCH_PATH = Path(__path__[0])

LOADER = jinja2.FileSystemLoader(SEARCH_PATH)

CFO = (SEARCH_PATH / 'cfo').open().read()
