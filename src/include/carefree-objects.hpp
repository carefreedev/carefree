/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2013 Stefan Zimmermann <zimmermann.code@gmail.com>
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

#ifndef __CAREFREE_OBJECTS_HPP
#define __CAREFREE_OBJECTS_HPP

#include "carefree-objects/managed.hpp"
#include "carefree-objects/forward.hpp"

namespace cfo
{
  template
  <typename T, bool SYNC = true, bool EXC = false,
   typename INIT_T = T, typename COPY = copy<T>
   >
  using managed = intern::managed<T, SYNC, EXC, INIT_T, false, COPY>;

  template
  <typename T, bool SYNC = true, bool EXC = false,
   typename INIT_T = T, typename COPY = copy<T>
   >
  using managed_forward = intern::forward
    <T, SYNC, EXC, INIT_T, false, COPY>;

  template
  <typename T, bool SYNC = true, bool EXC = false,
   typename INIT_T = T, typename COPY = copy<T>
   >
  using managed_vector = intern::managed
    <intern::basic_manager::vector<T, SYNC, EXC, INIT_T, COPY>, SYNC, EXC>;
}

#define cfo_MANAGER_CONSTRUCTORS(NAME)                                \
  inline NAME(const NAME &manager) :                                  \
     manager_type(manager.const_manager())                            \
  {}                                                                  \
                                                                      \
  inline NAME(const manager_type &manager) :                          \
    manager_type(manager)                                             \
  {}                                                                  \
                                                                      \
  inline NAME(const manager_type::null &nullmanager) :                \
    manager_type(nullmanager)                                         \
  {}                                                                  \

#define cfo_MANAGER_MANAGED_PTR_CONSTRUCTOR(NAME)                     \
  inline NAME(managed_ptr_type obj_ptr) :                             \
    manager_type(obj_ptr)                                             \
  {}                                                                  \

#define cfo_MANAGER_VARIADIC_CONSTRUCTOR(NAME)                        \
  template<typename... ARGS>                                          \
  inline NAME(const ARGS &...args) :                                  \
    manager_type(new managed_type(args...))                           \
  {}                                                                  \

#define cfo_MANAGER_CAST_CONSTRUCTOR(NAME, MANAGER)                   \
  inline NAME(const MANAGER &manager) :                               \
    manager_type(manager.const_manager())                             \
  {}                                                                  \

#define cfo_MANAGER_EQUAL_OPERATORS(NAME)                             \
  inline bool operator==(const NAME &manager) const                   \
  {                                                                   \
    return this->manager_type::operator==(manager.const_manager());   \
  }                                                                   \
                                                                      \
  inline bool operator==(const manager_type &manager) const           \
  {                                                                   \
    return this->manager_type::operator==(manager);                   \
  }                                                                   \
                                                                      \
  inline bool operator==(const manager_type::null &nullmanager) const \
  {                                                                   \
    return this->manager_type::operator==(nullmanager);               \
  }                                                                   \
                                                                      \
  template<typename A>                                                \
  inline bool operator!=(const A &arg) const                          \
  {                                                                   \
    return !this->operator==(arg);                                    \
  }                                                                   \

#define cfo_MANAGER_CAST_EQUAL_OPERATOR(NAME, MANAGER)                \
  inline bool operator==(const MANAGER &manager) const                \
  {                                                                   \
    return this->manager_type::operator==(manager.const_manager());   \
  }                                                                   \

#endif
