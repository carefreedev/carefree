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

#ifndef __CFO_TOOLS_IP_ADDRESS_HPP
#define __CFO_TOOLS_IP_ADDRESS_HPP

#include <carefree-types/common.hpp>

namespace cfo { namespace ip { namespace base
{
  namespace _address
  {
    extern bool no_return_error;
  }
  template<typename BASE, typename INT, std::size_t SIZE>
  class address : public BASE
  {
    using BASE::BASE;

  public:

  public:
    inline address(const BASE &address):
      BASE(static_cast<const BASE&>(address))
    {}

    // inline _address(BASE &&address):
    //   BASE(static_cast<const BASE&>(address))
    // {}

  public:
    inline INT operator[](const std::size_t index) const
    {
      return reinterpret_cast<const INT&>
        (this->to_bytes()[index * sizeof(INT)]);
    }

    template<std::size_t N>
    inline INT get() const;

    template<std::size_t N>
    inline std::uint8_t byte() const;

  public:
    inline operator std::string() const
    {
      return this->BASE::to_string();
    }
  };
} } }

#include "./v4/address.hpp"
#include "./v6/address.hpp"

#endif
