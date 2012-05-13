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

#ifndef __CFO_COMMON_HPP
#define __CFO_COMMON_HPP

#include <cstdlib>

#include <memory>

#include <boost/foreach.hpp>

#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>

namespace cfo { namespace intern
{
  class count_and_lock;

  template<typename T, typename... BASES>
  class const_accessor;

  template<typename T, typename... BASES>
  class accessor;

  template<typename T, bool SYNC = true, typename... BASES>
  class const_methods;

  template<typename T, bool SYNC = true, typename... BASES>
  class methods;

  class basic_manager;

  template
  <typename T, bool SYNC = true, bool INIT_NULL = false, typename... BASES>
  class managed;
} }

#endif
