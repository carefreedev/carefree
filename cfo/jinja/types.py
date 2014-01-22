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

"""cfo.jinja.types

.. moduleauthor:: Stefan Zimmermann <zimmermann.code@gmail.com>
"""
__all__ = 'Typename', 'Type', 'TypesDictType', 'TypesDict', 'manager',

from collections import OrderedDict
from moretools import SimpleDictType, simpledict

class Typename(str):
  def __new__(cls, value, ref = None):
    return str.__new__(cls, value)

  def __init__(self, value, ref = None):
    try:
      self.ref = ref or value.ref
    except AttributeError:
      self.ref = value

class Type(object):
  def __init__(self, name, typename):
    self.name = name
    self.typename = Typename(typename)

class TypesDictType(SimpleDictType):
  def __init__(self, *types):
    SimpleDictType.__init__(self)

    for t in types:
      if type(t) is not Type:
        t = Type(*t)
        self[t.name] = t

TypesDict = simpledict(
  'TypesDict', basetype = TypesDictType,
  dicttype = OrderedDict, iterate = 'values')

def manager(typename):
  return Typename(typename, typename + '::manager_type')
