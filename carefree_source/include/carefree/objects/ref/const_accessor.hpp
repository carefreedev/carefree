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

#ifndef __CAREFREE_OBJECTS_REF_CONST_ACCESSOR_HPP
#define __CAREFREE_OBJECTS_REF_CONST_ACCESSOR_HPP

#include "../ref.hpp"

namespace cfo
{

  template<typename T>
  class ref<T>::const_accessor :
    private cfo::shared_sync_lock,
    public cfo::managed<T, const_accessor>
  {

  public:
    using ref_type = cfo::ref<T>;
    using members_type = cfo::managed<T, const_accessor>;

  public:
    using ptr_type = const T*;
    using const_ptr_type = const T*;

  protected:
    ref_type _ref;
    const_ptr_type _ptr;

  public:
    inline
    const_accessor(const ref_type &ref) :
      cfo::shared_sync_lock(*ref._ptr),
      _ref(ref),
      _ptr(_ref._ptr->get())
    {}

  private:
    const_accessor(const const_accessor &);

  public:
    inline
    const_accessor(const_accessor &&acs) :
      cfo::shared_sync_lock(static_cast<cfo::shared_sync_lock&&>(acs)),
      _ref(acs._ref),
      _ptr(acs._ptr)
    {}

  public:
    inline
    const_ptr_type operator->()
      const
    {
      return this->_ptr;
    }

  public:
    template<typename U>
    static
    inline
    const_ptr_type ptr(const cfo::managed<U, const_accessor> &members)
    {
      return static_cast<const const_accessor&>(members)._ptr;
    }

  public:
    template<typename U>
    static
    inline
    ref_type ref(const cfo::managed<U, const_accessor> &members)
    {
      return static_cast<const const_accessor&>(members)._ref;
    }

  }; /* class ref<T>::const_accessor */

} /* namespace cfo */

#endif /* __CAREFREE_OBJECTS_REF_CONST_ACCESSOR_HPP */
