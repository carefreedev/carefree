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

"""cfo.jinja.context

.. moduleauthor:: Stefan Zimmermann <zimmermann.code@gmail.com>
"""
__all__ = ['ARCH_BITS', 'INT_TYPES', 'UINT_TYPES']

import platform

ARCH_BITS = int(platform.architecture()[0].split('bit')[0])

## INT_TYPES = ['std::int%i_t' % size for size in 8, 16, 32, 64]
## if ARCH_BITS == 32:
##   INT_TYPES.append('long')

## UINT_TYPES = ['std::uint%i_t' % size for size in 8, 16, 32, 64]
## if ARCH_BITS == 32:
##   UINT_TYPES.append('unsigned long')

class IntTypes(list):
    def __init__(self, names_and_sizes):
        self._items = list(names_and_sizes)

    def __iter__(self):
        return (item[0] for item in self._items)

    def __gt__(self, bits):
        return (item[0] for item in self._items if item[1] > bits)

INT_TYPES = IntTypes([
  ('char', 8),
  ('short', 16),
  ('int', 32),
  ('long', ARCH_BITS),
  ('long long', 64),
  ])

UINT_TYPES = IntTypes(
  ('unsigned ' + name, size) for name, size in INT_TYPES._items)
