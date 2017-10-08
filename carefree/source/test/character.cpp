#include <cassert>

#include <carefree-types/string.hpp>

namespace cfo
{
  /*static*/ void character::_test()
  {
    assert(sizeof(character) == sizeof(character::value_type));
    assert(sizeof(character::value_type) == sizeof(wchar_t));

    character c;
    assert(c.value == 0);
  }
}
