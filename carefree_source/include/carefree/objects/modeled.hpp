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

#ifndef __CAREFREE_OBJECTS_MODELED_HPP
#define __CAREFREE_OBJECTS_MODELED_HPP

#include "./common.hpp"

#include "./managed.hpp"

namespace cfo
{

  template<typename T>
  class modeled : public managed<T>
  {
    using managed<T>::managed;

  public:
    using managed_ = managed<T>;
    using modeled_ = modeled<T>;

  public:
    class model;

  public:
    class make;
    class make_const;

    friend class make;
    friend class make_const;

  public:
    class accessor;
    class const_accessor;

  public:
    inline
    accessor access()
    {
      return accessor(*this);
    }

    inline
    const_accessor caccess()
      const
    {
      return const_accessor(*this);
    }

  public:
    template<typename F>
    inline
    // typename std::invoke_result<F, accessor &>::type
    typename std::result_of<F(accessor &)>::type
    access(F func)
    {
      auto acs = this->access();
      return func(acs);
    }

    template<typename F>
    inline
    // typename std::invoke_result<F, const const_accessor &>::type
    typename std::result_of<F(const const_accessor &)>::type
    caccess(F func)
      const
    {
      auto acs = this->caccess();
      return func(acs);
    }

  public:
    template<typename ACS>
    class data;

  }; /* class modeled<T> */

} /* namespace cfo */

#include "./modeled/model.hpp"

#include "./modeled/make.hpp"

#include "./modeled/accessor.hpp"
#include "./modeled/const_accessor.hpp"

#endif /* __CAREFREE_OBJECTS_MODELED_HPP */
