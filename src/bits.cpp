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

#include <carefree-types/bits.hpp>

namespace cfo
{
  /*public*/
  bits::bits
  (const std::string &bitstring, const std::size_t nbits, const bool fill
   ) :
    _bits::super_vector()
  {
    const std::size_t len = bitstring.length();
    if (nbits)
      if (nbits < len * 8)
        {
          this->resize(nbits);
          std::size_t bitn = 0u;
          for (const uint8_t byte : bitstring)
            //- reverse index range because bits are read from left to right
            //  but numerical bit order is right to left
            for (int n = 7; n >= 0; --n, ++bitn)
              {
                if (bitn == nbits)
                  return;

                //- use basic operator to avoid size check in bits::operator[]
                this->_bits::super_vector::operator[](bitn)
                  = bool(byte & (0x1 << n));
              }
          return;
        }
      else
        //- initialize extra bits with default `fill` value
        this->resize(nbits, fill);
    else
      this->resize(len * 8);

    std::size_t bitn = 0u;
    for (const uint8_t byte : bitstring)
      //- reverse index range because bits are read from left to right
      //  but numerical bit order is right to left
      for (int n = 7; n >= 0; --n, ++bitn)
        //- use basic operator to avoid size check in bits::operator[]
        this->_bits::super_vector::operator[](bitn)
          = bool(byte & (0x1 << n));
  }

{% for INT in [INT_TYPES, UINT_TYPES]|chain %}
  /*public*/
  bits::bits
  (const {{ INT }} bits, std::size_t nbits, const bool fill
   ) :
    _bits::super_vector()
  {
    if (nbits)
      {
        if (nbits > {{ INT.bits }})
          //- initialize extra bits with default `fill` value
          this->resize(nbits, fill);
        else
          this->resize(nbits);
      }
    else
      {
        nbits = {{ INT.bits }};
        this->resize({{ INT.bits }});
      }
    for (std::size_t n = 0u; n < nbits; ++n)
      //- use basic operator to avoid size check in bits::operator[]
      this->_bits::super_vector::operator[](n) = bits & (0x1L << n);
  }
{% endfor %}
}
