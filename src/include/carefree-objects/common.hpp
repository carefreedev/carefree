/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2014 Stefan Zimmermann <zimmermann.code@gmail.com>
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

#ifndef __CFO_COMMON_HPP
#define __CFO_COMMON_HPP

#if defined(WIN32) || defined(WIN64)
#define noexcept(_)
#endif

#include <cstdlib>

#include <typeinfo>
#include <typeindex>

#include <memory>

#include <vector>
#include <map>

#include <boost/foreach.hpp>
#include <boost/current_function.hpp>

#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>

namespace cfo
{
  template<typename T>
  struct copy
  {
    inline T* operator()(const T& obj) const
    {
      return new T(obj);
    }
  };
}

namespace cfo { namespace intern
{
  class count_and_lock;

  template<typename T, bool EXC = false, typename INIT_T = T,
           typename COPY = cfo::copy<T>
           >
  class const_accessor;

  template<typename T, bool EXC = false, typename INIT_T = T,
           typename COPY = cfo::copy<T>, // >
           typename CONST_METHODS_T
             = typename T::template cfo_managed_const_methods
                 <T, true, EXC, INIT_T, COPY>
           >
  class accessor;

  template<typename T, bool SYNC = true, bool EXC = false, typename INIT_T = T, typename COPY = cfo::copy<T> >
  class const_methods;

  template<typename T, bool SYNC = true, bool EXC = false,
           typename INIT_T = T, typename COPY = cfo::copy<T>, // >
           typename CONST_METHODS_T
             = typename T::template cfo_managed_const_methods
                 <T, true, EXC, INIT_T, COPY>
           >
  class methods;

  class basic_manager;

  template
  <typename T, bool SYNC = true, bool EXC = false, typename INIT_T = T, bool INIT_NULL = false, typename COPY = cfo::copy<T> >
  class managed;

  template
  <typename T, bool SYNC = true, bool EXC = false, typename INIT_T = T, bool INIT_NULL = false, typename COPY = cfo::copy<T> >
  class forward;
} }

#endif
