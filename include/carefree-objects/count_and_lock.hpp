/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2013 Stefan Zimmermann <zimmermann.code@googlemail.com>
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

#ifndef __CFO_COUNT_AND_LOCK_HPP
#define __CFO_COUNT_AND_LOCK_HPP

#include "common.hpp"

namespace cfo { namespace intern
{
  class count_and_lock : public boost::shared_mutex
  {
  private:
    std::size_t counter;

  public:
    inline count_and_lock() :
      boost::shared_mutex(),
      counter(0)
    {}

    inline count_and_lock& operator++()
    {
      return ++this->counter, *this;
    }

    inline count_and_lock& operator--()
    {
      return --this->counter, *this;
    }

    inline operator bool()
    {
      return this->counter;
    }
  };
} }

#endif
