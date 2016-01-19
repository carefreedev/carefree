/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2016 Stefan Zimmermann <zimmermann.code@gmail.com>
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
  template<typename T, bool EXC, typename INIT_T, typename COPY>
  class const_methods<T, true, EXC, INIT_T, COPY> :
    public const_accessor<T, EXC, INIT_T, COPY>
  {
  private:
    const_methods(const const_methods<T, true, EXC, INIT_T, COPY>&);

  protected:
    template<bool SYNC_>
    using cfo_sync = const_methods<T, SYNC_, EXC, INIT_T, COPY>;

    inline const_methods
    (const managed<T, true, EXC, INIT_T, false, COPY> &manager,
     bool shared
     ) :
      const_accessor<T, EXC, INIT_T, COPY>(manager, shared)
    {}

  public:
    inline const_methods
    (const managed<T, true, EXC, INIT_T, false, COPY> &manager
     ) :
      const_accessor<T, EXC, INIT_T, COPY>(manager)
    {}

    inline const_methods
    (const_methods<T, true, EXC, INIT_T, COPY> &&methods
     ) :
      const_accessor<T, EXC, INIT_T, COPY>
      (static_cast<const_accessor<T, EXC, INIT_T, COPY>&&>(methods))
    {}
  };

  template<typename T, bool EXC, typename INIT_T, typename COPY>
  class const_methods<T, false, EXC, INIT_T, COPY> :
    protected std::shared_ptr<T>
  {
  protected:
    template<bool SYNC_>
    using cfo_sync = const_methods<T, SYNC_, EXC, INIT_T, COPY>;

    inline const_methods(T *obj) :
      std::shared_ptr<T>(obj)
    {}

    inline const_methods(const std::shared_ptr<T> &manager) :
      std::shared_ptr<T>(manager)
    {}

    inline const_methods
    (const const_methods<T, false, EXC, INIT_T, COPY> &methods) :

      std::shared_ptr<T>(methods)
    {}

  public:
    inline const managed<T, false, EXC, INIT_T, false, COPY>& manager()
      const
    {
      return static_cast
        <const managed<T, false, EXC, INIT_T, false, COPY>&>
        (*this);
    }

    inline managed<T, false, EXC, INIT_T, false, COPY>& manager()
    {
      return static_cast<managed<T, false, EXC, INIT_T, false, COPY>&>
        (*this);
    }

    inline const managed<T, false, EXC, INIT_T, false, COPY>&
    const_manager()
      const
    {
      return static_cast
        <const managed<T, false, EXC, INIT_T, false, COPY>&>
        (*this);
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
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   >                                                                    \
  class _cfo_managed_const_methods : public cfo_BASE                    \
  {                                                                     \
    template                                                            \
      <typename cfo_T_, bool cfo_SYNC_, bool cfo_EXC_,                  \
       typename cfo_INIT_T_, typename cfo_COPY_,                        \
       typename cfo_BASE_                                               \
       >                                                                \
      friend class _cfo_managed_const_methods;                          \
                                                                        \
  private:                                                              \
    _cfo_managed_const_methods                                          \
      (const _cfo_managed_const_methods                                 \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>&);        \
                                                                        \
    template<bool cfo_SYNC_ = cfo_SYNC>                                 \
      using cfo_basic_type                                              \
      = typename cfo_BASE::template cfo_sync<cfo_SYNC_>;                \
                                                                        \
  protected:                                                            \
    template<bool cfo_SYNC_>                                            \
      using cfo_sync                                                    \
      = _cfo_managed_const_methods                                      \
      <cfo_T, cfo_SYNC_, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>;      \
                                                                        \
    inline _cfo_managed_const_methods(cfo_T *obj) :                     \
      cfo_basic_type<false>(obj)                                        \
    {}                                                                  \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const std::shared_ptr<cfo_T> &manager                            \
       ) :                                                              \
      cfo_basic_type<false>(manager)                                    \
    {}                                                                  \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const _cfo_managed_const_methods                                 \
       <cfo_T, false, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>          \
       &methods                                                         \
       ) :                                                              \
      cfo_basic_type<false>(methods)                                    \
    {}                                                                  \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const cfo::intern::managed                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, false, cfo_COPY>              \
       &manager                                                         \
       , bool shared) :                                                 \
                                                                        \
      cfo_basic_type<true>(manager, shared)                             \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline _cfo_managed_const_methods                                   \
      (const cfo::intern::managed                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, false, cfo_COPY>              \
       &manager                                                         \
       ) :                                                              \
      cfo_basic_type<true>(manager)                                     \
    {}                                                                  \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (_cfo_managed_const_methods                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>           \
       &&methods                                                        \
       ) :                                                              \
      cfo_basic_type<true>                                              \
      (static_cast<cfo_basic_type<true>&&>(methods))                    \
    {}                                                                  \
                                                                        \
    template<typename cfo_M>                                            \
    inline typename cfo_M::managed_type                                 \
      ::template cfo_managed_const_methods                              \
      <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                  \
    & cast()                                                            \
    {                                                                   \
      return *this;                                                     \
    }                                                                   \
                                                                        \
    template<typename cfo_MGR>                                          \
    inline const typename cfo_MGR::managed_type                         \
      ::template cfo_managed_const_methods                              \
      <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                  \
    & cast()                                                            \
    const {                                                             \
      return *this;                                                     \
    }                                                                   \
                                                                        \
  protected:                                                            \
    inline const TYPE* operator->() const                               \
    {                                                                   \
      return static_cast<const TYPE*>                                   \
        (this->cfo_basic_type<>::operator->());                         \
    }                                                                   \
                                                                        \
    inline TYPE* operator->()                                           \
    {                                                                   \
      return static_cast<TYPE*>(this->cfo_basic_type<>::operator->());  \
    }                                                                   \
                                                                        \
    METHODS                                                             \
  };                                                                    \
                                                                        \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   = cfo::intern::const_methods                                         \
   <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                     \
   >                                                                    \
  using cfo_managed_const_methods                                       \
  = _cfo_managed_const_methods                                          \
    <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>;         \
                                                                        \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   >                                                                    \
  friend class TYPE::_cfo_managed_const_methods;                        \

#define cfo_DECLARE_MANAGED_BASIC_CONST_METHODS(TYPE)                   \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   >                                                                    \
  class _cfo_managed_const_methods;                                     \
                                                                        \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   = cfo::intern::const_methods                                         \
   <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                     \
   >                                                                    \
  using cfo_managed_const_methods                                       \
  = _cfo_managed_const_methods                                          \
    <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>;         \
                                                                        \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   >                                                                    \
  friend class TYPE::_cfo_managed_const_methods;                        \

#define cfo_DEFINE_MANAGED_BASIC_CONST_METHODS(SCOPE, TYPE)             \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   >                                                                    \
  class SCOPE::_cfo_managed_const_methods : public cfo_BASE             \
  {                                                                     \
    template                                                            \
      <typename cfo_T_, bool cfo_SYNC_, bool cfo_EXC_,                  \
       typename cfo_INIT_T_, typename cfo_COPY_,                        \
       typename cfo_BASE_                                               \
       >                                                                \
      friend class _cfo_managed_const_methods;                          \
                                                                        \
  private:                                                              \
    template<typename cfo_V = void>                                     \
    class property                                                      \
    {                                                                   \
    public:                                                             \
      typedef _cfo_managed_const_methods                                \
        <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>      \
        methods_type;                                                   \
                                                                        \
      methods_type *methods;                                            \
                                                                        \
    protected:                                                          \
      inline const TYPE* operator->() const                             \
      {                                                                 \
        return static_cast<const methods_type*>(this->methods)          \
          ->operator->();                                               \
      }                                                                 \
                                                                        \
      inline TYPE* operator->()                                         \
      {                                                                 \
        return this->methods->operator->();                             \
      }                                                                 \
                                                                        \
      inline operator const cfo_V() const                               \
      {                                                                 \
        return this->operator()();                                      \
      }                                                                 \
    };                                                                  \
                                                                        \
  private:                                                              \
    _cfo_managed_const_methods                                          \
      (const _cfo_managed_const_methods                                 \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>&);        \
                                                                        \
    template<bool cfo_SYNC_ = cfo_SYNC>                                 \
      using cfo_basic_type                                              \
      = typename cfo_BASE::template cfo_sync<cfo_SYNC_>;                \
                                                                        \
  protected:                                                            \
    template<bool cfo_SYNC_>                                            \
      using cfo_sync                                                    \
      = _cfo_managed_const_methods                                      \
      <cfo_T, cfo_SYNC_, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>;      \
                                                                        \
    inline _cfo_managed_const_methods(cfo_T *obj) :                     \
      cfo_basic_type<false>(obj)                                        \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const std::shared_ptr<cfo_T> &manager                            \
       ) :                                                              \
      cfo_basic_type<false>(manager)                                    \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const _cfo_managed_const_methods                                 \
       <cfo_T, false, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>          \
       &methods                                                         \
       ) :                                                              \
      cfo_basic_type<false>(methods)                                    \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const cfo::intern::managed                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, false, cfo_COPY>              \
       &manager                                                         \
       , bool shared) :                                                 \
                                                                        \
      cfo_basic_type<true>(manager, shared)                             \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
  public:                                                               \
    inline _cfo_managed_const_methods                                   \
      (const cfo::intern::managed                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, false, cfo_COPY>              \
       &manager                                                         \
       ) :                                                              \
      cfo_basic_type<true>(manager)                                     \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (_cfo_managed_const_methods                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>           \
       &&methods                                                        \
       ) :                                                              \
      cfo_basic_type<true>                                              \
      (static_cast<cfo_basic_type<true>&&>(methods))                    \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
    template<typename cfo_M>                                            \
    inline typename cfo_M::managed_type                                 \
      ::template cfo_managed_const_methods                              \
      <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                  \
    & cast()                                                            \
    {                                                                   \
      return *this;                                                     \
    }                                                                   \
                                                                        \
    template<typename cfo_MGR>                                          \
    inline const typename cfo_MGR::managed_type                         \
      ::template cfo_managed_const_methods                              \
      <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                  \
    & cast()                                                            \
    const {                                                             \
      return *this;                                                     \
    }                                                                   \
                                                                        \
  protected:                                                            \
    inline const TYPE* operator->() const                               \
    {                                                                   \
      return static_cast<const TYPE*>                                   \
        (this->cfo_basic_type<>::operator->());                         \
    }                                                                   \
                                                                        \
    inline TYPE* operator->()                                           \
    {                                                                   \
      return static_cast<TYPE*>(this->cfo_basic_type<>::operator->());  \
    }                                                                   \
                                                                        \
  private:                                                              \

#define cfo_DEFINE_MANAGED_PROPERTIES                                   \
  public:                                                               \
    union                                                               \
    {                                                                   \
      property<> _property;                                             \

#define cfo_END_MANAGED_PROPERTIES                                      \
    };                                                                  \
                                                                        \
  private:                                                              \

#define cfo_END_MANAGED_BASIC_CONST_METHODS                             \
  };                                                                    \

#define cfo_MANAGED_CONST_METHODS(TYPE, BASE, METHODS)                  \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   >                                                                    \
  class _cfo_managed_const_methods : public cfo_BASE                    \
  {                                                                     \
    template                                                            \
      <typename cfo_T_, bool cfo_SYNC_, bool cfo_EXC_,                  \
       typename cfo_INIT_T_, typename cfo_COPY_,                        \
       typename cfo_BASE_                                               \
       >                                                                \
      friend class _cfo_managed_const_methods;                          \
                                                                        \
  private:                                                              \
    template<bool cfo_SYNC_ = cfo_SYNC>                                 \
      using cfo_basic_type                                              \
      = typename cfo_BASE::template cfo_sync<cfo_SYNC_>;                \
                                                                        \
    _cfo_managed_const_methods                                          \
      (const _cfo_managed_const_methods                                 \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>&);        \
                                                                        \
  protected:                                                            \
    template<bool cfo_SYNC_>                                            \
      using cfo_sync                                                    \
      = _cfo_managed_const_methods                                      \
      <cfo_T, cfo_SYNC_, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>;      \
                                                                        \
    inline _cfo_managed_const_methods(cfo_T *obj) :                     \
      cfo_basic_type<false>(obj)                                        \
    {}                                                                  \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const std::shared_ptr<cfo_T> &manager) :                         \
                                                                        \
      cfo_basic_type<false>(manager)                                    \
    {}                                                                  \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const _cfo_managed_const_methods                                 \
       <cfo_T, false, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>          \
       &methods                                                         \
       ) :                                                              \
      cfo_basic_type<false>(methods)                                    \
    {}                                                                  \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const cfo::intern::managed                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, false, cfo_COPY>              \
       &manager                                                         \
       , bool shared) :                                                 \
                                                                        \
      cfo_basic_type<true>(manager, shared)                             \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline _cfo_managed_const_methods                                   \
      (const cfo::intern::managed                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, false, cfo_COPY>              \
       &manager                                                         \
       ) :                                                              \
      cfo_basic_type<true>(manager)                                     \
    {}                                                                  \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (_cfo_managed_const_methods                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>           \
       &&methods                                                        \
       ) :                                                              \
      cfo_basic_type<true>                                              \
      (static_cast<cfo_basic_type<true>&&>(methods))                    \
    {}                                                                  \
                                                                        \
    template<typename cfo_MGR>                                          \
    inline                                                              \
    typename cfo_MGR::managed_type                                      \
      ::template cfo_managed_const_methods                              \
      <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                  \
    & cast()                                                            \
    {                                                                   \
      return *this;                                                     \
    }                                                                   \
                                                                        \
    template<typename cfo_MGR>                                          \
    inline const typename cfo_MGR::managed_type                         \
      ::template cfo_managed_const_methods                              \
      <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                  \
    & cast()                                                            \
    const {                                                             \
      return *this;                                                     \
    }                                                                   \
                                                                        \
  protected:                                                            \
    inline const TYPE* operator->() const                               \
    {                                                                   \
      return static_cast<const TYPE*>                                   \
        (this->cfo_basic_type<>::operator->());                         \
    }                                                                   \
                                                                        \
    inline TYPE* operator->()                                           \
    {                                                                   \
      return static_cast<TYPE*>(this->cfo_basic_type<>::operator->());  \
    }                                                                   \
                                                                        \
    METHODS                                                             \
  };                                                                    \
                                                                        \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   = typename BASE::template cfo_managed_const_methods                  \
   <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                     \
   >                                                                    \
  using cfo_managed_const_methods                                       \
  = _cfo_managed_const_methods                                          \
    <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>;         \
                                                                        \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   >                                                                    \
  friend class TYPE::_cfo_managed_const_methods;                        \

#define cfo_DECLARE_MANAGED_CONST_METHODS(TYPE, BASE)                   \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   >                                                                    \
  class _cfo_managed_const_methods;                                     \
                                                                        \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   = typename BASE::template cfo_managed_const_methods                  \
   <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                     \
   >                                                                    \
  using cfo_managed_const_methods                                       \
  = _cfo_managed_const_methods                                          \
    <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>;         \
                                                                        \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   >                                                                    \
  friend class TYPE::_cfo_managed_const_methods;                        \

#define cfo_DEFINE_MANAGED_CONST_METHODS(SCOPE, TYPE, BASE)             \
  template                                                              \
  <typename cfo_T, bool cfo_SYNC, bool cfo_EXC,                         \
   typename cfo_INIT_T, typename cfo_COPY,                              \
   typename cfo_BASE                                                    \
   >                                                                    \
  class SCOPE::_cfo_managed_const_methods : public cfo_BASE             \
  {                                                                     \
    template                                                            \
      <typename cfo_T_, bool cfo_SYNC_, bool cfo_EXC_,                  \
       typename cfo_INIT_T_, typename cfo_COPY_,                        \
       typename cfo_BASE_                                               \
       >                                                                \
      friend class _cfo_managed_const_methods;                          \
                                                                        \
  private:                                                              \
    template<typename cfo_V = void>                                     \
    class property                                                      \
    {                                                                   \
    public:                                                             \
      typedef _cfo_managed_const_methods                                \
        <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>      \
        methods_type;                                                   \
                                                                        \
      methods_type *methods;                                            \
                                                                        \
    protected:                                                          \
      inline const TYPE* operator->() const                             \
      {                                                                 \
        return static_cast<const methods_type*>(this->methods)          \
          ->operator->();                                               \
      }                                                                 \
                                                                        \
      inline TYPE* operator->()                                         \
      {                                                                 \
        return this->methods->operator->();                             \
      }                                                                 \
                                                                        \
      inline operator const cfo_V() const                               \
      {                                                                 \
        return this->operator()();                                      \
      }                                                                 \
    };                                                                  \
                                                                        \
    template<bool cfo_SYNC_ = cfo_SYNC>                                 \
      using cfo_basic_type                                              \
      = typename cfo_BASE::template cfo_sync<cfo_SYNC_>;                \
                                                                        \
    _cfo_managed_const_methods                                          \
      (const _cfo_managed_const_methods                                 \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>&);        \
                                                                        \
  protected:                                                            \
    template<bool cfo_SYNC_>                                            \
      using cfo_sync                                                    \
      = _cfo_managed_const_methods                                      \
      <cfo_T, cfo_SYNC_, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>;      \
                                                                        \
    inline _cfo_managed_const_methods(cfo_T *obj) :                     \
      cfo_basic_type<false>(obj)                                        \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const std::shared_ptr<cfo_T> &manager) :                         \
                                                                        \
      cfo_basic_type<false>(manager)                                    \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const _cfo_managed_const_methods                                 \
       <cfo_T, false, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>          \
       &methods                                                         \
       ) :                                                              \
      cfo_basic_type<false>(methods)                                    \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (const cfo::intern::managed                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, false, cfo_COPY>              \
       &manager                                                         \
       , bool shared) :                                                 \
                                                                        \
      cfo_basic_type<true>(manager, shared)                             \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
  public:                                                               \
    inline _cfo_managed_const_methods                                   \
      (const cfo::intern::managed                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, false, cfo_COPY>              \
       &manager                                                         \
       ) :                                                              \
      cfo_basic_type<true>(manager)                                     \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
    inline _cfo_managed_const_methods                                   \
      (_cfo_managed_const_methods                                       \
       <cfo_T, true, cfo_EXC, cfo_INIT_T, cfo_COPY, cfo_BASE>           \
       &&methods                                                        \
       ) :                                                              \
      cfo_basic_type<true>                                              \
      (static_cast<cfo_basic_type<true>&&>(methods))                    \
    {                                                                   \
      this->_property.methods = this;                                   \
    }                                                                   \
                                                                        \
    template<typename cfo_MGR>                                          \
    inline                                                              \
    typename cfo_MGR::managed_type                                      \
      ::template cfo_managed_const_methods                              \
      <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                  \
    & cast()                                                            \
    {                                                                   \
      return *this;                                                     \
    }                                                                   \
                                                                        \
    template<typename cfo_MGR>                                          \
    inline const typename cfo_MGR::managed_type                         \
      ::template cfo_managed_const_methods                              \
      <cfo_T, cfo_SYNC, cfo_EXC, cfo_INIT_T, cfo_COPY>                  \
    & cast()                                                            \
    const {                                                             \
      return *this;                                                     \
    }                                                                   \
                                                                        \
  protected:                                                            \
    inline const TYPE* operator->() const                               \
    {                                                                   \
      return static_cast<const TYPE*>                                   \
        (this->cfo_basic_type<>::operator->());                         \
    }                                                                   \
                                                                        \
    inline TYPE* operator->()                                           \
    {                                                                   \
      return static_cast<TYPE*>(this->cfo_basic_type<>::operator->());  \
    }                                                                   \

#define cfo_END_MANAGED_CONST_METHODS                                   \
  };                                                                    \

#endif
