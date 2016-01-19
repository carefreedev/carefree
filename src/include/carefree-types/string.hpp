/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2016 Stefan Zimmermann <zimmermann.code@gmail.com>
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

#ifndef __CAREFREE_TYPES_STRING_HPP
#define __CAREFREE_TYPES_STRING_HPP

#include "./common.hpp"

namespace cfo
{
  class character
  {
  public:
    class except;

  public:
    typedef wchar_t value_type;

  public:
    value_type value = value_type(0);

  public:
    inline character() :
      value(value_type(0))
    {}

{% for INT in INT_TYPES %}
    inline character(const {{ INT }} value) :
      value((sizeof({{ INT }}) <= sizeof(value_type)
             || (value >= ({{ INT }})WCHAR_MIN
                 && value <= ({{ INT }})WCHAR_MAX
                 )
             ) ? value_type(value) : value_type(0))
    {}

    inline character
    (const {{ INT }} value, bool &error) :
      value((sizeof({{ INT }}) <= sizeof(value_type)
             || (value >= ({{ INT }})WCHAR_MIN
                 && value <= ({{ INT }})WCHAR_MAX)
             ) ?
            (error = false, value_type(value))
            : (error = true, value_type(0)))
    {}
{% endfor %}

  public:
    static void _test();
  };

  namespace _string
  {
    //- Using cfo::character as template arg raises C2620 in VC++
    //  (union member with constructor)
    typedef std::basic_string<cfo::character::value_type> super;
  }

  class string : public _string::super
  {
    using _string::super::super;

  public:
    static void _test();
  };
}

#endif
