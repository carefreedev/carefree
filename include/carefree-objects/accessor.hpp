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
  template<typename T, typename... BASES>
  class accessor :
    public T::template cfo_managed_const_methods<T, true, BASES...>
  {
  private:
    accessor(accessor<T, BASES...> &);

  public:
    inline accessor(const managed<T, true, false, BASES...> &manager) :
      T::template cfo_managed_const_methods<T, true, BASES...>
      (manager, false)
    {}

    inline accessor(accessor<T, BASES...> &&access) :
      T::template cfo_managed_const_methods<T, true>
      (static_cast
       <typename T::template cfo_managed_const_methods<T, true, BASES...>&&
       >
       (access))
    {}

    inline T* operator->() const
    {
      return this->manager_ptr->obj;
    }
  };
} }

#endif
