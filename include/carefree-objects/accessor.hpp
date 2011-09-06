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

namespace cfo
{
  template<typename T>
  class const_accessor
  {
    friend class accessor<T>;

  private:
    T *obj;

  protected:
    const_accessor(T* obj) :
      obj(obj)
    {}

  public:
    const_accessor(const managed<T> &manager) :
      obj(manager.unmanaged())
    {}

    T* operator->()
    {
      return this->obj;
    }
  };

  template<typename T>
  class accessor : public const_accessor<T>
  {
  public:
    accessor(managed<T> &manager) :
      const_accessor<T>(manager.unmanaged())
    {}
  };
}

#endif
