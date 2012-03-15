/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011 Stefan Zimmermann <zimmermann.code@googlemail.com>
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

#include "basic_manager.hpp"
#include "methods.hpp"

namespace cfo
{
  template<typename T, bool SYNC, typename M>
  class basic_manager::vector
    : private std::vector<managed<T, SYNC>*>
  {
  private:
    typedef managed<T, SYNC> manager_type;
    typedef std::vector<manager_type*> vector_type;

  public:
    inline ~vector()
    {
      BOOST_FOREACH
        (manager_type *manager_ptr, *static_cast<vector_type*>(this))

        delete manager_ptr;
    }

    inline std::size_t size() const
    {
      return this->vector_type::size();
    }

    inline M& operator[](std::size_t index)
    {
      return *static_cast<M*>(this->vector_type::operator[](index));
    }

    template<typename... A>
    inline void push_back(const A &...args)
    {
      this->vector_type::push_back(new M(args...));
    }

    cfo_MANAGED_BASIC_CONST_METHODS
    (public:

     inline std::size_t size() const
     {
       return (*this)->size();
     })

     // const inline M& operator[](std::size_t index) const
     // {
     //   return *static_cast<M*>(this->vector_type::operator[](index));
     // })

    cfo_MANAGED_BASIC_METHODS
    (public:

     template<typename... A>
     inline void push_back(const A &...args)
     {
       (*this)->push_back(args...);
     }

     inline M& operator[](std::size_t index)
     {
       return (*this)->operator[](index);
     })
  };
}

#endif
