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

/* managed vector for managed objects
 */

#ifndef __CFO_VECTOR_CONST_ITERATOR_HPP
#define __CFO_VECTOR_CONST_ITERATOR_HPP

#include "../vector.hpp"

namespace cfo { namespace intern
{
  template
  <typename T, bool SYNC, bool EXC, typename INIT_T, typename COPY,
   typename MGR
   >
  class basic_manager::vector<T, SYNC, EXC, INIT_T, COPY, MGR>
    ::const_iterator
    :
    private vector<T, SYNC, EXC, INIT_T, COPY, MGR>::cfo_manager_type
  {
  private:
    std::size_t _index;

  public:
    typedef
      typename vector<T, SYNC, EXC, INIT_T, COPY, MGR>::cfo_manager_type
      cfo_vector_manager_type;

    inline const_iterator
    (const cfo_vector_manager_type &vector, const std::size_t index = 0u
     ) :
      cfo_vector_manager_type(vector),
      _index(index)
    {}

    inline const_iterator(const const_iterator &other) :
      cfo_vector_manager_type(other.const_manager()),
      _index(other._index)
    {}

    inline const_iterator(const_iterator &&other) :
      cfo_vector_manager_type
      (static_cast<cfo_vector_manager_type&&>(other)
       ),
      _index(other._index)
    {}

    inline const MGR& operator*()
    {
      return this->cfo_vector_manager_type::operator[](this->_index);
    }

    inline std::size_t index()
    {
      return this->_index;
    }

    inline const_iterator& operator++()
    {
      ++this->_index;
      return *this;
    }

    inline bool operator==(const const_iterator &other)
    {
      return this->unmanaged() == other.unmanaged()
        && this->_index == other._index;
    }

    inline bool operator!=(const const_iterator &other)
    {
      return this->unmanaged() != other.unmanaged()
        || this->_index != other._index;
    }
  }; /* class basic_manager::vector<>::const_iterator */
} } /* namespace cfo::intern */

#endif /* __CFO_VECTOR_CONST_ITERATOR_HPP */
