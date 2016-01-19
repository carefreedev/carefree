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

/* the object access templates
 *
 * request object references from a manager in a thread-safe way
 * for const or non-const access to the object members
 */
#ifndef __CFO_ACCESSOR_HPP
#define __CFO_ACCESSOR_HPP

#include "common.hpp"

#include "const_methods.hpp"

namespace cfo { namespace intern
{
  template<typename T, bool EXC /* = false */, typename INIT_T /* = T */,
           typename COPY /* = cfo::copy<T> */,
           typename CONST_METHODS_T
           /* = typename T::template cfo_managed_const_methods
              <T, true, EXC, INIT_T, COPY> */
           >
  class accessor :
    public CONST_METHODS_T
    // public T::template cfo_managed_const_methods
    //   <T, true, EXC, INIT_T, COPY>
  {
  private:
    accessor(const accessor<T, EXC, INIT_T, COPY> &);

  public:
    inline accessor
    (const managed<T, true, EXC, INIT_T, false, COPY> &manager
     ) :
      // T::template cfo_managed_const_methods<T, true, EXC, INIT_T, COPY>
      CONST_METHODS_T
        (manager, false)
    {}

    inline accessor(accessor<T, EXC, INIT_T, COPY> &&access) :
      T::template cfo_managed_const_methods<T, true, EXC, INIT_T, COPY>
      (static_cast<CONST_METHODS_T&&>
       // <typename T::template cfo_managed_const_methods
       //  <T, true, EXC, INIT_T, COPY>
       //  &&>
       (access))
    {}

    inline T* operator->() const
    {
      return this->manager_ptr->obj;
    }
  };
} }

#endif
