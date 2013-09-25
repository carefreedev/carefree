#include <cassert>

#include <carefree-types/ip.hpp>

namespace cfo { namespace ip
{
  namespace v6
{
  /*static*/ void address::_test()
  {
    bool error;
    ip::v6::address address("::", error);
    assert(!error);
  }
}
} }
