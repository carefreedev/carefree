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

#ifndef __CAREFREE_TYPES_BYTES_HPP
#define __CAREFREE_TYPES_BYTES_HPP

#include "./common.hpp"

namespace cfo
{
  class byte
  {
  public:
    class except;

  public:
    typedef std::uint8_t value_type;

  public:
    value_type value = value_type(0u);

  public:
    inline byte() :
      value(value_type(0u))
    {}

{% for UINT in (UINT_TYPES > 8) %}
    inline byte(const {{ UINT }} value) :
      value((sizeof({{ UINT }}) == 1 || value <= ({{ UINT }})0xff) ?
            value_type(value) : value_type(0u))
    {}

    inline byte(const {{ UINT }} value, bool &error) :
      value((sizeof({{ UINT }}) == 1 || value <= ({{ UINT }})0xff) ?
            (error = false, value_type(value))
            : (error = true, value_type(0u)))
    {}
{% endfor %}
  };

  namespace _bytes
  {
    //- Using cfo::byte as template arg raises C2620 in VC++
    //  (union member with constructor)
    typedef std::basic_string<cfo::byte::value_type> base;
  }
  class bytes : public _bytes::base
  {
    using _bytes::base::base;
  };
}

#endif
