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
 * to implement ref counting and synchronized member access
 */
#ifndef __CFO_MANAGED_HPP
#define __CFO_MANAGED_HPP

#include "common.hpp"

#include "count_and_lock.hpp"
#include "accessor.hpp"

namespace cfo
{
  class basic_manager
  {
  protected:
    count_and_lock *cnl;

    inline basic_manager() :
      cnl(new count_and_lock)
    {}
  };

  template<typename T>
  class managed : public basic_manager
  {
  private:
    T *obj;

  public:
    typedef cfo::const_accessor<const T> const_accessor;
    typedef cfo::accessor<T> accessor;

    template<typename... A>
    inline managed(A... args) :
      obj(new T(args...))
    {
      ++*this->cnl;
    }

    inline managed(const managed<T> &manager) :
      obj(manager.obj)
    {
      ++*this->cnl;
    }

    template<typename T_other>
    inline managed(const managed<T_other> &other_manager) :
      basic_manager(other_manager),
      obj(static_cast<T*>(other_manager.unmanaged()))
    {
      ++*this->cnl;
    }

    inline ~managed()
    {
      if (!--*this->cnl)
        {
          delete this->obj;
          delete this->cnl;
        }
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
}

#endif
