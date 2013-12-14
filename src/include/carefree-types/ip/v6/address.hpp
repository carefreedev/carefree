/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2013 Stefan Zimmermann <zimmermann.code@gmail.com>
 *
 * carefree-objects is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * carefree-objects is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with carefree-objects.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CFO_TOOLS_IP_V6_ADDRESS_HPP
#define __CFO_TOOLS_IP_V6_ADDRESS_HPP

#include <carefree-types/common.hpp>

#include <carefree-types/ip/address.hpp>

namespace cfo { namespace ip
{
  namespace v6
{
  namespace _address
  {
    typedef ip::base::address
      <boost::asio::ip::address_v6, std::uint16_t, 8u>
      base;
  }
  class address : public _address::base
  {
  protected:
    inline boost::asio::ip::address_v6 _from
    (const std::string &numbers,
     bool &return_error = ip::base::_address::no_return_error);

  public:
    inline address
    (const std::string &numbers,
     bool &error = ip::base::_address::no_return_error
     ) :
      ip::v6::_address::base(this->_from(numbers, error))
    {}

    inline address
    (const char *numbers,
     bool &error = ip::base::_address::no_return_error
     ) :
      address(std::string(numbers), error)
    {}

    inline address(const boost::asio::ip::address_v6 &address) :
      ip::v6::_address::base(address)
    {}

    // inline address(const boost::asio::ip::address &address) :
    //   ip::v6::_address::base
    //   (address.is_v6() ? address.to_v6().to_ulong() : 0u)
    // {}

  public:
    static void _test();
  };

}
} }

#include "./address.inl"

#endif
