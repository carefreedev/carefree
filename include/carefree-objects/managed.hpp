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

namespace cfo { namespace intern
{
  template<typename T, bool INIT_NULL, typename... BASES>
  class managed<T, true, INIT_NULL, BASES...> :
    public basic_manager,
    public BASES...
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
    typedef T managed_type;
    typedef T* managed_ptr_type;
    typedef const T* managed_const_ptr_type;

    typedef managed<T, true, INIT_NULL, BASES...> manager_type;

    typedef managed<T, true, true, BASES...> null;

    typedef typename T::template cfo_managed_const_methods
      <const T, true, BASES...>
      const_accessor;

    typedef typename T::template cfo_managed_methods<T, true, BASES...>
      accessor;

    typedef managed
      <basic_manager::vector<T, true, managed<T, true, false, BASES...> >,
       true
       >
      vector;

    template<typename I, typename... E>
      using map = managed
      <basic_manager::map
       <I, T, true, managed<T, true, false, BASES...>, E...>,

       true>;

    inline managed() :
      basic_manager(),
      obj(INIT_NULL ? NULL : new T)
    {}

    template<typename... A>
    inline managed(A... args) :
      basic_manager(),
      obj(new T(args...))
    {}

    // template<typename... BASES_other>
    // inline managed
    //   (const managed<T, true, true, BASES_other...> &/*nullmanager*/) :

    //   basic_manager(),
    //   obj(NULL)
    // {}

    inline managed(const managed<T, true, false, BASES...> &manager) :
      basic_manager(manager),
      obj(this->cnl ? manager.obj : NULL)
    {}

    template
    <typename T_other, bool INIT_NULL_other, typename... BASES_other>
    inline managed
    (const managed<T_other, true, INIT_NULL_other, BASES_other...>
     &other_manager) :

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

    inline operator bool() const
    {
      return this->obj;
    }

    inline bool operator!() const
    {
      return !this->obj;
    }
  };

  template<typename T, bool INIT_NULL, typename... BASES>
  class managed<T, false, INIT_NULL, BASES...> :
    public T::template cfo_managed_methods<T, false, BASES...>,
    public BASES...
  {
    friend T;

    template
      <typename T_other, bool SYNC, bool INIT_NULL_other,
       typename... BASES_other
       >
      friend class managed;

  protected:
    inline managed(T *obj) :
      T::template cfo_managed_methods<T, false, BASES...>(obj)
    {}

  public:
    typedef T managed_type;
    typedef T* managed_ptr_type;
    typedef const T* managed_const_ptr_type;

    typedef managed<T, false, INIT_NULL, BASES...> manager_type;

    typedef managed<T, false, true, BASES...> null;

    typedef managed
      <basic_manager::vector
       <T, false, managed<T, false, false, BASES...> >,

       false
       >
      vector;

    template<typename I, typename... E>
      using map = managed
      <basic_manager::map
       <I, T, false, managed<T, false, false, BASES...>, E...>,

       false>;

    inline managed() :
      T::template cfo_managed_methods<T, false, BASES...>
      (INIT_NULL ? NULL : new T)
    {}

    template<typename... A>
    inline managed(A... args) :
      T::template cfo_managed_methods<T, false, BASES...>(new T(args...))
    {}

    // template<typename... BASES_other>
    // inline managed
    //   (const managed<T, false, true, BASES_other...> &/*nullmanager*/) :

    //   T::template cfo_managed_methods<T, false, BASES...>(NULL)
    // {}

    inline managed(const managed<T, false, false, BASES...> &manager) :
      T::template cfo_managed_methods<T, false, BASES...>(manager)
    {}

    template
      <typename T_other, bool INIT_NULL_other, typename... BASES_other>

    inline managed
      (const managed<T_other, false, INIT_NULL_other, BASES_other...>
       &other_manager) :

      T::template cfo_managed_methods<T, false, BASES...>
      (std::static_pointer_cast<T>
       (static_cast<const std::shared_ptr<T_other>&>(other_manager)))
    {}

    inline std::size_t refcount() const
    {
      return this->use_count();
    }

    inline T* operator->() const
    {
      assert(this->get());
      return this->get();
    }

    inline T* unmanaged() const
    {
      assert(this->get());
      return this->get();
    }
  };
} }

#endif
