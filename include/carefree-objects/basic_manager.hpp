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

/* the object manager base class
 *
 * implements synchronized ref counting and access control
 * indepentendently from the object type
 */
#ifndef __CFO_BASIC_MANAGER_HPP
#define __CFO_BASIC_MANAGER_HPP

#include "common.hpp"

#include "count_and_lock.hpp"

namespace cfo { namespace intern
{
  class basic_manager
  {
  private:
    boost::mutex *mutex;

    inline bool lock() const
    {
      if (!this->mutex)
        return false;

      return this->mutex->lock(), true;
    }

    inline void unlock() const
    {
      this->mutex->unlock();
    }

  protected:
    count_and_lock *cnl;

    inline basic_manager() :
      mutex(new boost::mutex),
      cnl(&++*new count_and_lock)
    {}

    inline basic_manager(const basic_manager &manager) :
      mutex(new boost::mutex),
      cnl(NULL)
    {
      if (!manager.lock())
        return;

      this->lock();

      if ((this->cnl = manager.cnl))
        ++*this->cnl;

      this->unlock();
      manager.unlock();
    }

    inline void destroy()
    {
      boost::mutex *mutex = this->mutex;
      mutex->lock();

      if (!--*this->cnl)
        {
          delete this->cnl;
          this->cnl = NULL;
        }

      this->mutex = NULL;

      mutex->unlock();
      delete mutex;
    }

  public:
    template<typename T, bool SYNC, typename M = managed<T, SYNC> >
    class vector;

    template
    <typename I, typename T, bool SYNC, typename M = managed<T, SYNC>,
     typename... E
     >
    class map;

    inline operator bool() const
    {
      return this->cnl;
    }

    inline bool operator!() const
    {
      return !this->cnl;
    }
  };
} }

#include "vector.hpp"
#include "map.hpp"

#endif
