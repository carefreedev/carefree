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

#ifndef __CFO_TOOLS_MAC_ADDRESS_INL
#define __CFO_TOOLS_MAC_ADDRESS_INL

#include "./address.hpp"

namespace cfo { namespace mac
{
  template<typename INT>
  inline address::address
  (const stz::const_array_ptr<INT> &bytes, bool &error
   ) :
    array_type()
  {
    if (bytes.size() != 6u)
      {
        error = true;
        return;
      }
    error = false;
    for (std::size_t n = 0u ; n < 6u ; ++n)
      (*this)[n] = bytes[n];
  }
} }

#endif
