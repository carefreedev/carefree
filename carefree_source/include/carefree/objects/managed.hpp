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

#ifndef __CAREFREE_OBJECTS_MANAGED_HPP
#define __CAREFREE_OBJECTS_MANAGED_HPP

#include "./common.hpp"

#include "./sync.hpp"

namespace cfo
{

  template<typename T, typename ACS>
  class managed
  {};

  // template<typename T>
  // class managed
  // {

  // public:
  //   using managed_ = managed<T>;

  // private:
  //   cfo::shared_sync_ptr<T> _ptr;

  // protected:
  //   inline
  //   managed(T *ptr) :
  //     _ptr(new cfo::sync_ptr<T>(ptr))
  //   {}

  // public:
  //   inline
  //   managed(const managed_ &other) :
  //     _ptr(other._ptr)
  //   {}

  //   inline
  //   managed(managed_ &&other) :
  //     _ptr(other._ptr)
  //   {}

  // public:
  //   class model;

  // public:
  //   class make;
  //   class make_const;

  //   friend class make;
  //   friend class make_const;

  //   inline
  //   managed(const make &made);

  //   inline
  //   managed(make &&made);

  // public:
  //   class sync :
  //     private cfo::unique_sync_lock
  //   {

  //   private:
  //     T* _ptr;

  //   public:
  //     sync(managed_ &instance) :
  //       cfo::unique_sync_lock(*instance._ptr),
  //       _ptr(instance._ptr->get())
  //     {}

  //   public:
  //     inline
  //     T* operator->()
  //     {
  //       return this->_ptr;
  //     }

  //   };

  //   friend class sync;

  //   class const_sync :
  //     private cfo::shared_sync_lock
  //   {

  //   private:
  //     const T* _ptr;

  //   public:
  //     const_sync(const managed_ &instance) :
  //       cfo::shared_sync_lock(*instance._ptr),
  //       _ptr(instance._ptr->get())
  //     {}

  //   public:
  //     inline
  //     const T* operator->()
  //       const
  //     {
  //       return this->_ptr;
  //     }

  //   };

  //   friend class const_sync;

  // public:
  //   class accessor;
  //   class const_accessor;

  // public:
  //   inline
  //   accessor access()
  //   {
  //     return accessor(*this);
  //   }

  //   inline
  //   const_accessor caccess()
  //     const
  //   {
  //     return const_accessor(*this);
  //   }

  // public:
  //   template<typename F>
  //   inline
  //   // typename std::invoke_result<F, accessor &>::type
  //   typename std::result_of<F(accessor &)>::type
  //   access(F func)
  //   {
  //     auto acs = this->access();
  //     return func(acs);
  //   }

  //   template<typename F>
  //   inline
  //   // typename std::invoke_result<F, const const_accessor &>::type
  //   typename std::result_of<F(const const_accessor &)>::type
  //   caccess(F func)
  //     const
  //   {
  //     auto acs = this->caccess();
  //     return func(acs);
  //   }

  // public:
  //   template<typename ACS>
  //   class methods;

  //   template<typename ACS>
  //   class const_methods;

  // }; /* class managed<T> */

} /* namespace cfo */

// #include "./managed/make.hpp"

// #include "./managed/accessor.hpp"
// #include "./managed/const_accessor.hpp"

#endif /* __CAREFREE_OBJECTS_MANAGED_HPP */
