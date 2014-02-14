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
from __future__ import division

__all__ = ['ARCH_BITS', 'INT_TYPES', 'UINT_TYPES']

import platform
from itertools import starmap


ARCH_BITS = int(platform.architecture()[0].split('bit')[0])


## INT_TYPES = ['std::int%i_t' % size for size in 8, 16, 32, 64]
## if ARCH_BITS == 32:
##   INT_TYPES.append('long')

## UINT_TYPES = ['std::uint%i_t' % size for size in 8, 16, 32, 64]
## if ARCH_BITS == 32:
##   UINT_TYPES.append('unsigned long')


class IntType(str):
    def __new__(cls, name, bits):
        return str.__new__(cls, name)

    def __init__(self, name, bits):
        self.bits = bits
        self.size = bits // 8
        if name.startswith('unsigned'):
            self.min = 0
            self.max = 2 ** bits - 1
        else:
            self.min = -2 ** (bits - 1)
            self.max = 2 ** (bits - 1) - 1


class IntTypes(list):
    def __init__(self, names_and_sizes):
        list.__init__(self, starmap(IntType, names_and_sizes))

    def __gt__(self, bits):
        return (i for i in self if i.bits > bits)

    def __ge__(self, bits):
        return (i for i in self if i.bits >= bits)

    def __lt__(self, bits):
        return (i for i in self if i.bits < bits)

    def __le__(self, bits):
        return (i for i in self if i.bits <= bits)


INT_TYPES = IntTypes([
  ('char', 8),
  ('short', 16),
  ('int', 32),
  ('long', ARCH_BITS),
  ('long long', 64),
  ])

UINT_TYPES = IntTypes(('unsigned ' + i, i.bits) for i in INT_TYPES)
