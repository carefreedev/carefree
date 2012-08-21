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
  template<typename T, typename... BASES>
  class const_methods<T, true, BASES...> :
    public const_accessor<T, BASES...>
  {
  private:
    const_methods(const const_methods<T, true, BASES...>&);

  protected:
    inline const_methods
    (const managed<T, true, false, BASES...> &manager, bool shared) :

      const_accessor<T>(manager, shared)
    {}

  public:
    inline const_methods(const managed<T, true, false, BASES...> &manager) :
      const_accessor<T>(manager)
    {}

    inline const_methods(const_methods<T, true, BASES...> &&methods) :
      const_accessor<T>
      (static_cast<const_accessor<T, BASES...>&&>(methods))
    {}
  };

  template<typename T, typename... BASES>
  class const_methods<T, false, BASES...> : protected std::shared_ptr<T>
  {
  protected:
    inline const_methods(T *obj) :
      std::shared_ptr<T>(obj)
    {}

    inline const_methods(const std::shared_ptr<T> &manager) :
      std::shared_ptr<T>(manager)
    {}

    inline const_methods
    (const const_methods<T, false, BASES...> &methods) :

      std::shared_ptr<T>(methods)
    {}

  public:
    inline managed<T, false, false, BASES...>& manager()
    {
      return static_cast<const managed<T, false, false, BASES...>&>(*this);
    }

    // inline const managed<T, false, false, BASES...>& manager() const
    // {
    //   return static_cast<const managed<T, false, false, BASES...>&>(*this);
    // }

    inline const managed<T, false, false, BASES...>& const_manager() const
    {
      return static_cast<const managed<T, false, false, BASES...>&>(*this);
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
    // (const managed<T, false, INIT_NULL, BASES...> &manager)
    //   const
    // {
    //   assert(this->get());
    //   return this->get() == manager.unmanaged();
    // }
  };
} }

#define cfo_MANAGED_BASIC_CONST_METHODS(TYPE, METHODS)                  \
  template<typename cfo_T, bool cfo_SYNC, typename... cfo_BASES>        \
  class cfo_managed_const_methods :                                     \
    public cfo::intern::const_methods<cfo_T, cfo_SYNC, cfo_BASES...>    \
  {                                                                     \
    template                                                            \
      <typename cfo_T_other, bool cfo_SYNC_other,                       \
       typename... cfo_BASES_other                                      \
       >                                                                \
      friend class cfo_managed_const_methods;                           \
                                                                        \
  private:                                                              \
    cfo_managed_const_methods                                           \
      (const cfo_managed_const_methods<cfo_T, true, cfo_BASES...>&);    \
                                                                        \
    typedef cfo::intern::const_methods<cfo_T, cfo_SYNC, cfo_BASES...>   \
      basic_type;                                                       \
                                                                        \
  protected:                                                            \
    inline cfo_managed_const_methods(cfo_T *obj) :                      \
      cfo::intern::const_methods<cfo_T, false, cfo_BASES...>(obj)       \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const std::shared_ptr<cfo_T> &manager) :                         \
                                                                        \
      cfo::intern::const_methods<cfo_T, false, cfo_BASES...>(manager)   \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo_managed_const_methods<cfo_T, false, cfo_BASES...>      \
       &methods) :                                                      \
                                                                        \
      cfo::intern::const_methods<cfo_T, false, cfo_BASES...>(methods)   \
      {}                                                                \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo::intern::managed<cfo_T, true, false, cfo_BASES...>     \
       &manager,                                                        \
                                                                        \
       bool shared) :                                                   \
                                                                        \
      cfo::intern::const_methods<cfo_T, true, cfo_BASES...>             \
      (manager, shared)                                                 \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline cfo_managed_const_methods                                    \
      (const cfo::intern::managed<cfo_T, true, false, cfo_BASES...>     \
       &manager) :                                                      \
                                                                        \
      cfo::intern::const_methods<cfo_T, true, cfo_BASES...>(manager)    \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (cfo_managed_const_methods<cfo_T, true, cfo_BASES...>             \
       &&methods) :                                                     \
                                                                        \
      cfo::intern::const_methods<cfo_T, true, cfo_BASES...>             \
      (static_cast                                                      \
       <cfo::intern::const_methods<cfo_T, true, cfo_BASES...>&&>        \
       (methods))                                                       \
    {}                                                                  \
                                                                        \
  protected:                                                            \
    inline const TYPE* operator->() const                               \
    {                                                                   \
      return static_cast<const TYPE*>                                   \
        (this->cfo::intern::const_methods                               \
         <cfo_T, cfo_SYNC, cfo_BASES...>                                \
         ::operator->());                                               \
    }                                                                   \
                                                                        \
    inline TYPE* operator->()                                           \
    {                                                                   \
      return static_cast<TYPE*>                                         \
        (this->cfo::intern::const_methods                               \
         <cfo_T, cfo_SYNC, cfo_BASES...>                                \
         ::operator->());                                               \
    }                                                                   \
                                                                        \
    METHODS                                                             \
  };                                                                    \
                                                                        \
  template<typename cfo_T, bool cfo_SYNC, typename... cfo_BASES>        \
  friend class TYPE::cfo_managed_const_methods;                         \

#define cfo_MANAGED_CONST_METHODS(TYPE, BASE, METHODS)                  \
  template<typename cfo_T, bool cfo_SYNC, typename... cfo_BASES>        \
  class cfo_managed_const_methods :                                     \
    public BASE::template cfo_managed_const_methods                     \
      <cfo_T, cfo_SYNC, cfo_BASES...>                                   \
  {                                                                     \
    template                                                            \
      <typename cfo_T_other, bool cfo_SYNC_other,                       \
       typename... cfo_BASES_other                                      \
       >                                                                \
      friend class cfo_managed_const_methods;                           \
                                                                        \
  private:                                                              \
    cfo_managed_const_methods                                           \
      (const cfo_managed_const_methods<cfo_T, true, cfo_BASES...>&);    \
                                                                        \
  protected:                                                            \
    inline cfo_managed_const_methods(cfo_T *obj) :                      \
      BASE::template cfo_managed_const_methods                          \
      <cfo_T, false, cfo_BASES...>                                      \
      (obj)                                                             \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const std::shared_ptr<cfo_T> &manager) :                         \
                                                                        \
      BASE::template cfo_managed_const_methods                          \
      <cfo_T, false, cfo_BASES...>                                      \
      (manager)                                                         \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo_managed_const_methods<cfo_T, false, cfo_BASES...>      \
       &methods) :                                                      \
                                                                        \
      BASE::template cfo_managed_const_methods                          \
      <cfo_T, false, cfo_BASES...>                                      \
      (methods)                                                         \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo::intern::managed<cfo_T, true, false, cfo_BASES...>     \
       &manager,                                                        \
                                                                        \
       bool shared) :                                                   \
                                                                        \
      BASE::template cfo_managed_const_methods                          \
      <cfo_T, true, cfo_BASES...>                                       \
      (manager, shared)                                                 \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline cfo_managed_const_methods                                    \
      (const cfo::intern::managed<cfo_T, true, false, cfo_BASES...>     \
       &manager) :                                                      \
                                                                        \
      BASE::template cfo_managed_const_methods                          \
      <cfo_T, true, cfo_BASES...>                                       \
      (manager)                                                         \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (cfo_managed_const_methods<cfo_T, true, cfo_BASES...>             \
       &&methods) :                                                     \
                                                                        \
      BASE::template cfo_managed_const_methods                          \
      <cfo_T, true, cfo_BASES...>                                       \
      (static_cast<typename BASE::template cfo_managed_const_methods    \
       <cfo_T, true, cfo_BASES...>                                      \
       &&>                                                              \
       (methods))                                                       \
    {}                                                                  \
                                                                        \
  protected:                                                            \
    inline const TYPE* operator->() const                               \
    {                                                                   \
      return static_cast<const TYPE*>                                   \
        (this->BASE::template cfo_managed_const_methods                 \
         <cfo_T, cfo_SYNC, cfo_BASES...>                                \
         ::operator->());                                               \
    }                                                                   \
                                                                        \
    inline TYPE* operator->()                                           \
    {                                                                   \
      return static_cast<TYPE*>                                         \
        (this->BASE::template cfo_managed_const_methods                 \
         <cfo_T, cfo_SYNC, cfo_BASES...>                                \
         ::operator->());                                               \
    }                                                                   \
                                                                        \
    METHODS                                                             \
  };                                                                    \
                                                                        \
  template<typename cfo_T, bool cfo_SYNC, typename... cfo_BASES>        \
  friend class TYPE::cfo_managed_const_methods;                         \

#endif
