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

#ifndef __CAREFREE_OBJECTS_MODELED_CONST_ACCESSOR_HPP
#define __CAREFREE_OBJECTS_MODELED_CONST_ACCESSOR_HPP

#include "../modeled.hpp"

namespace cfo
{

  template<typename T>
  class modeled<T>::const_accessor :
    public managed<T>::const_accessor,
    public modeled<T>::data<const_accessor>
  {

  public:
    using managed_ = managed<T>;
    using modeled_ = modeled<T>;

  public:
    using data = typename modeled_::template data<const_accessor>;

  public:
    inline
    const_accessor(const modeled_ &instance) :
      managed_::const_accessor(static_cast<const managed_&>(instance))
    {}

  private:
    const_accessor(const const_accessor &);

  public:
    inline
    const_accessor(const_accessor &&acs) :
      managed_::accessor(static_cast<managed_::accessor&&>(acs))
    {}

  public:
    using managed_::const_accessor::operator->;

  public:
    template<typename ACS>
    static
    inline
    auto ptr(const ACS &acs)
    {
      return managed_::const_accessor::ptr
        (static_cast<const const_accessor&>(acs));
    }

  public:
    template<typename ACS>
    static
    inline
    auto self(const ACS &acs)
    {
      return managed_::const_accessor::self
        (static_cast<const const_accessor&>(acs));
    }

  }; /* class modeled<T>::const_accessor */

} /* namespace cfo */

#endif /* __CAREFREE_OBJECTS_MODELED_CONST_ACCESSOR_HPP */
