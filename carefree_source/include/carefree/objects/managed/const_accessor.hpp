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

#ifndef __CAREFREE_OBJECTS_MANAGED_CONST_ACCESSOR_HPP
#define __CAREFREE_OBJECTS_MANAGED_CONST_ACCESSOR_HPP

#include "../managed.hpp"

namespace cfo
{

  template<typename T>
  class managed<T>::const_accessor :
    private cfo::shared_sync_lock,
    public managed<T>::const_methods<const_accessor>
  {

  public:
    using managed_ = managed<T>;

  public:
    using ptr_type = const T*;

  private:
    managed_ _instance;
    ptr_type _ptr;

  public:
    inline
    const_accessor(const managed_ &instance) :
      cfo::shared_sync_lock(*instance._ptr),
      _instance(instance),
      _ptr(_instance._ptr->get())
    {}

  private:
    const_accessor(const const_accessor &);

  public:
    inline
    const_accessor(const_accessor &&acs) :
      cfo::shared_sync_lock(static_cast<cfo::shared_sync_lock&&>(acs)),
      _instance(acs._instance),
      _ptr(acs._ptr)
    {}

  public:
    inline
    auto operator->()
      const
    {
      return this->_ptr;
    }

  public:
    template<typename ACS>
    static
    inline
    auto ptr(const ACS &acs)
    {
      return static_cast<const const_accessor&>(acs)._ptr;
    }

  public:
    template<typename ACS>
    static
    inline
    auto self(const ACS &acs)
    {
      return static_cast<const const_accessor&>(acs)._instance;
    }

  }; /* class managed<T>::const_accessor */

} /* namespace cfo */

#endif /* __CAREFREE_OBJECTS_MANAGED_CONST_ACCESSOR_HPP */
