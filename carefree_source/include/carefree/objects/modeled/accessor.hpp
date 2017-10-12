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

#ifndef __CAREFREE_OBJECTS_MODELED_ACCESSOR_HPP
#define __CAREFREE_OBJECTS_MODELED_ACCESSOR_HPP

#include "../modeled.hpp"

namespace cfo
{

  template<typename T>
  class modeled<T>::accessor :
    public managed<T>::accessor,
    public modeled<T>::data<accessor>
  {

  public:
    using managed_ = managed<T>;
    using modeled_ = modeled<T>;

  public:
    using data = typename modeled_::template data<accessor>;

  public:
    inline
    accessor(const modeled_ &instance) :
      managed_::accessor(static_cast<const managed_&>(instance))
    {}

  private:
    accessor(const accessor &);

  public:
    accessor(accessor &&acs) :
      managed_::accessor(static_cast<const managed_::accessor&&>(acs))
    {}

  public:
    using managed_::accessor::operator->;

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

  }; /* class modeled<T>::accessor */

} /* namespace cfo */

#endif  /* __CAREFREE_OBJECTS_MANAGED_ACCESSOR_HPP */
