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
  template<typename T, typename... BASES>
  class managed<T, true, BASES...> : public basic_manager, public BASES...
  {
    friend class const_accessor<T, BASES...>;
    friend class accessor<T, BASES...>;

  private:
    T *obj;

  protected:
    inline managed(T *obj) :
      basic_manager(),
      obj(obj)
    {}

  public:
    typedef typename T::template cfo_managed_const_methods<const T, true, BASES...>
    const_accessor;

    typedef typename T::template cfo_managed_methods<T, true, BASES...> accessor;

    typedef managed<basic_manager::vector<T, true, BASES...>, true> vector;

    template<typename... A>
    inline managed(A... args) :
      basic_manager(),
      obj(new T(args...))
    {}

    inline managed(const managed<T, true, BASES...> &manager) :
      basic_manager(manager),
      obj(this->cnl ? manager.obj : NULL)
    {}

    template<typename T_other, typename... BASES_other>
    inline managed
      (const managed<T_other, true, BASES_other...> &other_manager) :

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

  template<typename T, typename... BASES>
  class managed<T, false, BASES...> :
    public T::template cfo_managed_methods<T, false, BASES...>,
    public BASES...
  {
    friend T;

  protected:
    inline managed(T *obj) :
      T::template cfo_managed_methods<T, false, BASES...>(obj)
    {}

  public:
    typedef managed<basic_manager::vector<T, false, BASES...>, false> vector;

    template<typename... A>
    inline managed(A... args) :
      T::template cfo_managed_methods<T, false, BASES...>(new T(args...))
    {}

    inline managed(const managed<T, false> &manager) :
      T::template cfo_managed_methods<T, false, BASES...>(manager)
    {}

    template<typename T_other, typename... BASES_other>
    inline managed
      (const managed<T_other, false, BASES_other...> &other_manager) :

      T::template cfo_managed_methods<T, false, BASES...>(other_manager)
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
