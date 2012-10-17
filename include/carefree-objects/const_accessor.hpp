/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2012 Stefan Zimmermann <zimmermann.code@googlemail.com>
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
#ifndef __CFO_CONST_ACCESSOR_HPP
#define __CFO_CONST_ACCESSOR_HPP

#include "common.hpp"

namespace cfo { namespace intern
{
  template<typename T, bool EXC>
  class const_accessor
  {
    friend class accessor<T, EXC>;

  private:
    const bool shared;
    std::unique_ptr<managed<T, true, EXC, false> > manager_ptr;

    const_accessor(const_accessor<T, EXC> &);

  protected:
    inline const_accessor
    (const managed<T, true, EXC, false> &manager, bool shared) :

      shared(shared),
      manager_ptr(new managed<T, true, EXC, false>(manager))
    {
      if (manager)
        manager.cnl->lock();
    }

    inline const managed<T, true, EXC, false>& manager() const
    {
      return *this->manager_ptr;
    }

  public:
    inline const_accessor(const managed<T, true, EXC, false> &manager) :
      shared(true),
      manager_ptr(new managed<T, true, EXC, false>(manager))
    {
      if (manager)
        manager.cnl->lock_shared();
    }

    inline const_accessor(const_accessor<T, EXC> &&access) :
      shared(access.shared),
      manager_ptr(access.manager_ptr.release())
    {}

    inline ~const_accessor()
    {
      if (!this->manager_ptr || !*this->manager_ptr)
        return;

      if (this->shared)
        this->manager_ptr->cnl->unlock_shared();

      else
        this->manager_ptr->cnl->unlock();
    }

    inline const T* operator->() const
    {
      return this->manager_ptr->obj;
    }
  };
} }

#endif
