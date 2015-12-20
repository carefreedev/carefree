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

#ifndef __CFO_MANAGED_FORWARD_HPP
#define __CFO_MANAGED_FORWARD_HPP

#include "common.hpp"

#include "basic_manager.hpp"
#include "methods.hpp"

namespace cfo { namespace intern
{
  template
  <typename T, bool EXC, typename INIT_T, bool INIT_NULL, typename COPY>
  class forward<T, true, EXC, INIT_T, INIT_NULL, COPY> :
    private std::unique_ptr
      <managed<T, true, EXC, INIT_T, INIT_NULL, COPY> >
  {
  private:
    typedef managed<T, true, EXC, INIT_T, INIT_NULL, COPY>
      cfo_manager_type;

    typedef std::unique_ptr<cfo_manager_type> basic_type;

  protected:
    inline forward(T *obj) :
      basic_type(new cfo_manager_type(obj))
    {}

  public:
    // typedef typename T::template cfo_managed_const_methods
    //   <const T, true>
    //   const_accessor;

    // typedef typename T::template cfo_managed_methods<T, true>
    //   accessor;

    typedef forward<T, true, EXC, INIT_T, true, COPY> null;

    inline forward() :
      basic_type(new cfo_manager_type)
    {}

    template<typename... A>
    inline forward(A... args) :
      basic_type(new cfo_manager_type(args...))
    {}

    inline forward
    (const managed<T, true, EXC, INIT_T, false, COPY> &manager
     ) :
      basic_type(new cfo_manager_type(manager))
    {}

    template
    <typename T_, bool EXC_, typename INIT_T_, bool INIT_NULL_,
     typename COPY_
     >
    inline forward
    (const managed<T_, true, EXC_, INIT_T_, INIT_NULL_, COPY_>
     &manager
     ) :
      basic_type(new cfo_manager_type(manager))
    {}

    // inline const_accessor caccess() const
    // {
    //   return const_accessor(**this);
    // }

    // inline accessor access()
    // {
    //   return accessor(**this);
    // }

    inline T* unmanaged() const
    {
      return (*this)->unmanaged();
    }

    inline operator bool() const
    {
      return bool(*this);
    }

    inline bool operator!() const
    {
      return !*this;
    }

    inline const cfo_manager_type& const_manager() const
    {
      return **this;
    }

    inline cfo_manager_type& manager()
    {
      return **this;
    }

    inline cfo_manager_type copy() const
    {
      return this->const_manager().copy();
    }

    inline operator const cfo_manager_type&() const
    {
      return **this;
    }

    inline operator cfo_manager_type&()
    {
      return **this;
    }

    inline operator cfo_manager_type()
    {
      return **this;
    }
  };

  template
  <typename T, bool EXC, typename INIT_T, bool INIT_NULL, typename COPY>
  class forward<T, false, EXC, INIT_T, INIT_NULL, COPY> :
    private std::unique_ptr
      <managed<T, false, EXC, INIT_T, INIT_NULL, COPY> >
  {
  private:
    typedef managed<T, false, EXC, INIT_T, INIT_NULL, COPY>
      cfo_manager_type;

    typedef std::unique_ptr<cfo_manager_type> basic_type;

  protected:
    inline forward(T *obj) :
      basic_type(new cfo_manager_type(obj))
    {}

  public:
    typedef forward<T, false, EXC, INIT_T, true, COPY> null;

    inline forward() :
      basic_type(new cfo_manager_type)
    {}

    template<typename... A>
    inline forward(A... args) :
      basic_type(new cfo_manager_type(args...))
    {}

    inline forward(const managed<T, false, EXC, INIT_T, false, COPY> &manager) :
      basic_type(new cfo_manager_type(manager))
    {}

    template
    <typename T_, bool EXC_, typename INIT_T_, bool INIT_NULL_,
     typename COPY_
     >
    inline forward
    (const managed<T_, false, EXC_, INIT_T_,  INIT_NULL_, COPY_>
     &manager) :

      basic_type(new cfo_manager_type(manager))
    {}

    inline std::size_t refcount() const
    {
      return (**this).refcount();
    }

    inline T* operator->() const
    {
      return (**this).operator->();
    }

    inline T* unmanaged() const
    {
      return (**this).unmanaged();
    }

    inline const cfo_manager_type& const_manager() const
    {
      return **this;
    }

    inline cfo_manager_type& manager()
    {
      return **this;
    }

    inline cfo_manager_type copy() const
    {
      return this->const_manager().copy();
    }

    inline operator const cfo_manager_type&() const
    {
      return **this;
    }

    inline operator cfo_manager_type&()
    {
      return **this;
    }

    inline operator cfo_manager_type()
    {
      return **this;
    }
  };
} }

#endif
