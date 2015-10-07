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

#ifndef __CFO_VECTOR_HPP
#define __CFO_VECTOR_HPP

#include "./common.hpp"

#include "./basic_manager.hpp"
#include "./methods.hpp"

namespace cfo { namespace intern
{
  template
  <typename T, bool SYNC, bool EXC, typename INIT_T, typename COPY,
   typename MGR
   >
  class basic_manager::vector : private std::vector<MGR*>
  {
  private:
    typedef std::vector<MGR*> _base_vector_type;

  public:
    typedef managed<T, SYNC, EXC, INIT_T, false, COPY>
    cfo_element_manager_type;

    typedef managed<vector<T, SYNC, EXC, INIT_T, COPY>, SYNC, EXC>
    cfo_manager_type;

    class iterator;
    class const_iterator;

    inline ~vector()
    {
      for (const MGR *element_ptr
             : static_cast<const _base_vector_type>(*this))

        delete element_ptr;
    }

    inline std::size_t size() const
    {
      return this->_base_vector_type::size();
    }

    inline const MGR& operator[](std::size_t index) const
    {
      return static_cast<MGR&>
        (static_cast<cfo_element_manager_type&>
         (*this->_base_vector_type::operator[](index)));
    }

    inline MGR& operator[](std::size_t index)
    {
      return static_cast<MGR&>
        (static_cast<cfo_element_manager_type&>
         (*this->_base_vector_type::operator[](index)));
    }

    template<typename... A>
    inline void push_back(const A &...args)
    {
      this->_base_vector_type::push_back
        (static_cast<MGR*>
         (static_cast<cfo_element_manager_type*>(new MGR(args...))));
    }

    template<typename... A>
    inline MGR& append(const A &...args)
    {
      MGR *element_ptr =
        static_cast<MGR*>
        (static_cast<cfo_element_manager_type*>(new MGR(args...)));

      this->_base_vector_type::push_back(element_ptr);
      return *element_ptr;
    }

#define _cfo_MANAGED_VECTOR_TEMPLATE_ARGS       \
    T, SYNC, EXC, INIT_T, COPY, MGR             \

    cfo_DECLARE_MANAGED_BASIC_CONST_METHODS
    (vector<_cfo_MANAGED_VECTOR_TEMPLATE_ARGS>)

    cfo_DECLARE_MANAGED_BASIC_METHODS
    (vector<_cfo_MANAGED_VECTOR_TEMPLATE_ARGS>)
  };
} } /* namespace cfo::intern */

#include "./vector/const_iterator.hpp"
#include "./vector/iterator.hpp"

#include "./vector/const_methods.hpp"
#include "./vector/methods.hpp"

#endif /* __CFO_VECTOR__ */
