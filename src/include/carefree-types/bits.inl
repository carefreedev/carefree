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

#ifndef __CAREFREE_TYPES_BITS_INL
#define __CAREFREE_TYPES_BITS_INL

#include "./bits.hpp"

namespace cfo
{
  /*public*/
  inline
  bool bits::operator[](const std::size_t bit)
    const
  {
    if (bit < this->size())
      return this->_bits::super_vector::operator[](bit);

    return false;
  }

  /*public*/
  inline
  std::vector<bool>::reference bits::operator[](const std::size_t bit)
  {
    if (bit >= this->size())
      this->resize(bit + 1, false);

    return this->_bits::super_vector::operator[](bit);
  }
}

#endif
