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

#ifndef __CAREFREE_OBJECTS_DATA_HPP
#define __CAREFREE_OBJECTS_DATA_HPP

#include "./common.hpp"

namespace cfo
{

  template<typename ACS, typename V>
  class data
  {

  protected:
    inline
    auto operator->()
    {
      return ACS::ptr(reinterpret_cast<ACS::members_type&>(*this));
        // (reinterpret_cast<modeled<T>::properties&>(*this));
    }

    inline
    auto operator->()
      const
    {
      return ACS::ptr(reinterpret_cast<const ACS::members_type&>(*this));
        // (reinterpret_cast<const modeled<T>::properties&>(*this));
    }

  }; /* data<ACS, V> */

} /* namespace cfo */

#endif /* __CAREFREE_OBJECTS_DATA_HPP */
