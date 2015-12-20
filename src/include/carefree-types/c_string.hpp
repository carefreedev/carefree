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

#ifndef __CFO_TYPES_C_STRING_HPP
#define __CFO_TYPES_C_STRING_HPP

#include "./common.hpp"

#include "./c_array.hpp"

namespace cfo
{
  class c_string : public c_array<char>
  {
    typedef c_array<char>::_except<c_string> except;

  public:
    using c_array<char>::c_array;
  };

  class const_c_string : public const_c_array<char>
  {
  public:
    typedef const_c_array<char>::_except<const_c_string> except;

  public:
    using const_c_array<char>::const_c_array;

    inline const_c_string(const std::string &str) :
      const_c_string(str.c_str(), str.length())
    {}
  };
}

#endif
