/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2012 Stefan Zimmermann <zimmermann.code@googlemail.com>
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

#ifndef __CFO_CONST_METHODS_HPP
#define __CFO_CONST_METHODS_HPP

#include "common.hpp"

#include "const_accessor.hpp"

namespace cfo { namespace intern
{
  template<typename T>
  class const_methods<T, true> : public const_accessor<T>
  {
  private:
    const_methods(const const_methods<T, true>&);

  protected:
    inline const_methods
    (const managed<T, true, false> &manager, bool shared) :

      const_accessor<T>(manager, shared)
    {}

  public:
    inline const_methods(const managed<T, true, false> &manager) :
      const_accessor<T>(manager)
    {}

    inline const_methods(const_methods<T, true> &&methods) :
      const_accessor<T>(static_cast<const_accessor<T>&&>(methods))
    {}
  };

  template<typename T>
  class const_methods<T, false> : protected std::shared_ptr<T>
  {
  protected:
    inline const_methods(T *obj) :
      std::shared_ptr<T>(obj)
    {}

    inline const_methods(const std::shared_ptr<T> &manager) :
      std::shared_ptr<T>(manager)
    {}

    inline const_methods
    (const const_methods<T, false> &methods) :

      std::shared_ptr<T>(methods)
    {}

  public:
    inline managed<T, false, false>& manager()
    {
      return static_cast<managed<T, false, false>&>(*this);
    }

    // inline const managed<T, false, false>& manager() const
    // {
    //   return static_cast<const managed<T, false, false>&>(*this);
    // }

    inline const managed<T, false, false>& const_manager() const
    {
      return static_cast<const managed<T, false, false>&>(*this);
    }

    inline const T* operator->() const
    {
      assert(this->get());
      return this->get();
    }

    inline operator bool() const
    {
      return this->get();
    }

    inline bool operator!() const
    {
      return !this->get();
    }

    // template<bool INIT_NULL>
    // inline bool operator==
    // (const managed<T, false, INIT_NULL> &manager)
    //   const
    // {
    //   assert(this->get());
    //   return this->get() == manager.unmanaged();
    // }
  };
} }

#define cfo_MANAGED_BASIC_CONST_METHODS(TYPE, METHODS)                  \
  template<typename cfo_T, bool cfo_SYNC>                               \
  class cfo_managed_const_methods :                                     \
    public cfo::intern::const_methods<cfo_T, cfo_SYNC>                  \
  {                                                                     \
    template<typename cfo_T_other, bool cfo_SYNC_other>                 \
      friend class cfo_managed_const_methods;                           \
                                                                        \
  private:                                                              \
    cfo_managed_const_methods                                           \
      (const cfo_managed_const_methods<cfo_T, true>&);                  \
                                                                        \
    template<bool cfo_SYNC_basic = cfo_SYNC>                            \
      using basic_type                                                  \
      = cfo::intern::const_methods<cfo_T, cfo_SYNC_basic>;              \
                                                                        \
  protected:                                                            \
    inline cfo_managed_const_methods(cfo_T *obj) :                      \
      basic_type<false>(obj)                                            \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const std::shared_ptr<cfo_T> &manager) :                         \
                                                                        \
      basic_type<false>(manager)                                        \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo_managed_const_methods<cfo_T, false> &methods) :        \
                                                                        \
      basic_type<false>(methods)                                        \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo::intern::managed<cfo_T, true, false> &manager,         \
       bool shared) :                                                   \
                                                                        \
      basic_type<true>(manager, shared)                                 \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline cfo_managed_const_methods                                    \
      (const cfo::intern::managed<cfo_T, true, false> &manager) :       \
                                                                        \
      basic_type<true>(manager)                                         \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (cfo_managed_const_methods<cfo_T, true> &&methods) :              \
                                                                        \
      basic_type<true>(static_cast<basic_type<true>&&>(methods))        \
    {}                                                                  \
                                                                        \
  protected:                                                            \
    inline const TYPE* operator->() const                               \
    {                                                                   \
      return static_cast<const TYPE*>                                   \
        (this->basic_type<>::operator->());                             \
    }                                                                   \
                                                                        \
    inline TYPE* operator->()                                           \
    {                                                                   \
      return static_cast<TYPE*>(this->basic_type<>::operator->());      \
    }                                                                   \
                                                                        \
    METHODS                                                             \
  };                                                                    \
                                                                        \
  template<typename cfo_T, bool cfo_SYNC>                               \
  friend class TYPE::cfo_managed_const_methods;                         \

#define cfo_MANAGED_CONST_METHODS(TYPE, BASE, METHODS)                  \
  template<typename cfo_T, bool cfo_SYNC>                               \
  class cfo_managed_const_methods :                                     \
    public BASE::template cfo_managed_const_methods<cfo_T, cfo_SYNC>    \
  {                                                                     \
    template<typename cfo_T_other, bool cfo_SYNC_other>                 \
      friend class cfo_managed_const_methods;                           \
                                                                        \
  private:                                                              \
    template<bool cfo_SYNC_basic = cfo_SYNC>                            \
      using basic_type                                                  \
      = typename BASE::template cfo_managed_const_methods               \
      <cfo_T, cfo_SYNC_basic>;                                          \
                                                                        \
    cfo_managed_const_methods                                           \
      (const cfo_managed_const_methods<cfo_T, true>&);                  \
                                                                        \
  protected:                                                            \
    inline cfo_managed_const_methods(cfo_T *obj) :                      \
      basic_type<false>(obj)                                            \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const std::shared_ptr<cfo_T> &manager) :                         \
                                                                        \
      basic_type<false>(manager)                                        \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo_managed_const_methods<cfo_T, false> &methods) :        \
                                                                        \
      basic_type<false>(methods)                                        \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo::intern::managed<cfo_T, true, false> &manager,         \
       bool shared) :                                                   \
                                                                        \
      basic_type<true>(manager, shared)                                 \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline cfo_managed_const_methods                                    \
      (const cfo::intern::managed<cfo_T, true, false> &manager) :       \
                                                                        \
      basic_type<true>(manager)                                         \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (cfo_managed_const_methods<cfo_T, true> &&methods) :              \
                                                                        \
      basic_type<true>(static_cast<basic_type<true>&&>(methods))        \
    {}                                                                  \
                                                                        \
    template<typename cfo_M>                                            \
    inline                                                              \
    typename cfo_M::managed_type                                        \
    ::template cfo_managed_const_methods<cfo_T, cfo_SYNC>               \
    &                                                                   \
    cast()                                                              \
    {                                                                   \
      return *this;                                                     \
    }                                                                   \
                                                                        \
    template<typename cfo_M>                                            \
    inline                                                              \
    const                                                               \
    typename cfo_M::managed_type                                        \
    ::template cfo_managed_const_methods<cfo_T, cfo_SYNC>               \
    &                                                                   \
    cast()                                                              \
      const                                                             \
    {                                                                   \
      return *this;                                                     \
    }                                                                   \
                                                                        \
  protected:                                                            \
    inline const TYPE* operator->() const                               \
    {                                                                   \
      return static_cast<const TYPE*>                                   \
        (this->basic_type<>::operator->());                             \
    }                                                                   \
                                                                        \
    inline TYPE* operator->()                                           \
    {                                                                   \
      return static_cast<TYPE*>(this->basic_type<>::operator->());      \
    }                                                                   \
                                                                        \
    METHODS                                                             \
  };                                                                    \
                                                                        \
  template<typename cfo_T, bool cfo_SYNC>                               \
  friend class TYPE::cfo_managed_const_methods;                         \

#endif
