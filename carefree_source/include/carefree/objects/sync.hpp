/*
 * CareFREE_objects :: MODELED C++ w/Python @<3
 *
 * Copyright (C) 2011-2017 Stefan Zimmermann <user@zimmermann.co>
 *
 * CareFREE_objects is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CareFREE_objects is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CareFREE_objects.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CAREFREE_OBJECTS_SYNC_HPP
#define __CAREFREE_OBJECTS_SYNC_HPP

#include "./common.hpp"

namespace cfo
{

  template<typename T = void>
  class sync_ptr : public std::unique_ptr<T>, public std::shared_mutex
  {

  public:
    inline
    sync_ptr(T* ptr) :
      std::unique_ptr<T>(ptr),
      std::shared_mutex()
    {}

  }; /* class sync_ptr<T> */

  using unique_sync_lock = std::unique_lock<std::shared_mutex>;
  using shared_sync_lock = std::shared_lock<std::shared_mutex>;

  template<typename T>
  using shared_sync_ptr = std::shared_ptr<cfo::sync_ptr<T>>;

} /* namespace cfo */

#endif /* __CAREFREE_OBJECTS_SYNC_HPP */
