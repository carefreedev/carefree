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

/* the object manager template
 *
 * wraps any normal c++ class
 * to get managed object ref counting and synchronized object member access
 */
#ifndef __CFO_MANAGED_HPP
#define __CFO_MANAGED_HPP

#include "common.hpp"

#include "basic_manager.hpp"
#include "methods.hpp"

namespace cfo
{
  template<typename T>
  class managed<T, true> : public basic_manager
  {
    friend class const_accessor<T>;
    friend class accessor<T>;

  private:
    T *obj;

  public:
    typedef typename T::template cfo_managed_const_methods<const T, true>
    const_accessor;

    typedef typename T::template cfo_managed_methods<T, true> accessor;

    template<typename... A>
    inline managed(A... args) :
      basic_manager(),
      obj(new T(args...))
    {}

    inline managed(const managed<T> &manager) :
      basic_manager(manager),
      obj(this->cnl ? manager.obj : NULL)
    {}

    template<typename T_other>
    inline managed(const managed<T_other> &other_manager) :
      basic_manager(other_manager),
      obj(this->cnl ? static_cast<T*>(other_manager.unmanaged()) : NULL)
    {}

    inline ~managed()
    {
      this->basic_manager::destroy();
      if (!this->cnl)
        delete this->obj;
    }

    inline const_accessor caccess() const
    {
      return const_accessor(*this);
    }

    inline accessor access()
    {
      return accessor(*this);
    }

    inline T* unmanaged() const
    {
      return this->obj;
    }
  };

  template<typename T>
  class managed<T, false> :
    public T::template cfo_managed_methods<T, false>
  {
  public:
    template<typename... A>
    inline managed(A... args) :
      T::template cfo_managed_methods<T, false>(new T(args...))
    {}

    inline managed(const managed<T, false> &manager) :
      T::template cfo_managed_methods<T, false>(manager)
    {}

    inline T* operator->() const
    {
      return this->get();
    }

    inline T* unmanaged() const
    {
      return this->get();
    }
  };
}

#endif
