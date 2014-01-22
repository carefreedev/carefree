__all__ = ['CFO_PYTHON_INT_TYPES']

from itertools import chain
from moretools import starreduce, simpledict

from cfo.jinja.context import INT_TYPES, UINT_TYPES


class IntTypes(simpledict('IntTypes', iterate='values')):
    def __getitem__(self, name):
        for int_ in self:
            if name in (int_, int_.cfo):
                return int_
        raise KeyError(name)


class IntType(str):
    def __init__(self, typename):
        if typename.isalpha():
            self.cfo = typename + '_'
        else:
            self.cfo = starreduce(
              str.replace,
              [('unsigned ', 'u'), ('long ', 'l'),
               ('std::', ''), ('_t', '')],
              typename)


CFO_PYTHON_INT_TYPES = []

for typename in chain(INT_TYPES, UINT_TYPES):
    CFO_PYTHON_INT_TYPES.append(IntType(typename))

for bits in [8, 16, 32, 64]:
    for name in ['int', 'uint']:
        CFO_PYTHON_INT_TYPES.append(IntType('std::%s%s_t' % (name, bits)))

CFO_PYTHON_INT_TYPES.append(IntType('std::size_t'))

CFO_PYTHON_INT_TYPES = IntTypes(
  {int_.cfo: int_ for int_ in CFO_PYTHON_INT_TYPES})
