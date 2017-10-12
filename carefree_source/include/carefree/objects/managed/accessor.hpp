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

#ifndef __CAREFREE_OBJECTS_MANAGED_ACCESSOR_HPP
#define __CAREFREE_OBJECTS_MANAGED_ACCESSOR_HPP

#include "../managed.hpp"

namespace cfo
{

  template<typename T>
  class managed<T>::accessor :
    private cfo::unique_sync_lock,
    public managed<T>::methods<accessor>,
    public managed<T>::const_methods<accessor>
  {

  public:
    using managed_ = managed<T>;

  public:
    using ptr_type = T*;

  private:
    managed_ _instance;
    T* _ptr;

  public:
    inline
    accessor(const managed_ &instance) :
      cfo::unique_sync_lock(*instance._ptr),
      _instance(instance),
      _ptr(_instance._ptr->get())
    {}

  private:
    accessor(const accessor &);

  public:
    accessor(accessor &&acs) :
      cfo::unique_sync_lock(static_cast<cfo::unique_sync_lock&&>(acs)),
      _instance(acs._instance),
      _ptr(acs._ptr)
    {}

  public:
    inline
    auto operator->()
    {
      return this->_ptr;
    }

  public:
    template<typename ACS>
    static
    inline
    auto ptr(ACS &acs)
    {
      return static_cast<accessor&>(acs)._ptr;
    }

    template<typename ACS>
    static
    inline
    auto ptr(const ACS &acs)
    {
      return static_cast<const accessor&>(acs)._ptr;
    }

  public:
    template<typename ACS>
    static
    inline
    auto self(ACS &acs)
    {
      return static_cast<accessor&>(acs)._instance;
    }

    template<typename ACS>
    static
    inline
    auto self(const ACS &acs)
    {
      return static_cast<const accessor&>(acs)._instance;
    }

  }; /* class managed<T>::accessor */

} /* namespace cfo */

#endif  /* __CAREFREE_OBJECTS_MANAGED_ACCESSOR_HPP */
