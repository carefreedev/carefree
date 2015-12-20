/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2015 Stefan Zimmermann <zimmermann.code@gmail.com>
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

#ifndef __CFO_TOOLS_IP_V4_ADDRESS_INL
#define __CFO_TOOLS_IP_V4_ADDRESS_INL

#include "./address.hpp"

namespace cfo { namespace ip { namespace base
{
{% for N in range(4) %}
  template<>
  template<>
  inline std::uint8_t ip::v4::_address::base::get<{{ N }}u>() const
  {
    return (*this)[{{ N }}u];
  }
{% endfor %}

{% for N in range(4) %}
  template<>
  template<>
  inline std::uint8_t ip::v4::_address::base::byte<{{ N }}u>() const
  {
    return this->to_bytes()[{{ N }}u];
  }
{% endfor %}
} } }

namespace cfo { namespace ip
{
  namespace v4
{
  template<>
  inline std::uint32_t address::_address<3u>(const std::uint8_t number)
  {
    return std::uint32_t(number);
  }
}
} }

#endif
