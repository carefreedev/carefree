/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2014 Stefan Zimmermann <zimmermann.code@gmail.com>
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

#ifndef __CAREFREE_TYPES_BYTE_ORDER_INL
#define __CAREFREE_TYPES_BYTE_ORDER_INL

namespace cfo
{
{% for INT in [INT_TYPES, UINT_TYPES]|chain %}
  inline {{ INT }} hton(const {{ INT }} value)
  {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    return value;
#endif
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  {% if INT.bits == 8 %}
    return value;
  {% endif %}
  {% if INT.bits == 16 %}
    return ({{ INT }})::htons(value);
  {% endif %}
  {% if INT.bits == 32 %}
    return ({{ INT }})::htonl(value);
  {% endif %}
  {% if INT.bits == 64 %}
    const std::uint32_t
      low = std::uint32_t(value),
      high = std::uint32_t(value >> 32);

    return ({{ INT }})(std::uint64_t(htonl(low)) << 32) + htonl(high);
  {% endif %}
#endif
  }

  inline {{ INT }} ntoh(const {{ INT }} value)
  {
    return hton(value);
  }
{% endfor %}
}

#endif
