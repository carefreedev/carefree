/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011 Stefan Zimmermann <zimmermann.code@googlemail.com>
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

namespace cfo
{
  template<typename T, typename... BASES>
  class const_methods<T, true, BASES...> :
    public const_accessor<T, BASES...>
  {
  private:
    const_methods(const const_methods<T, true, BASES...>&);

  protected:
    inline const_methods
    (const managed<T, true, BASES...> &manager, bool shared) :

      const_accessor<T>(manager, shared)
    {}

  public:
    inline const_methods(const managed<T, true, BASES...> &manager) :
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

    inline const_methods
    (const const_methods<T, false, BASES...> &methods) :

      std::shared_ptr<T>(methods)
    {}

    template<typename T_other, typename... BASES_other>
    inline const_methods
    (const const_methods<T_other, false, BASES_other...> &methods) :

      std::shared_ptr<T>(methods)
    {}

    inline const managed<T, false, BASES...>& manager() const
    {
      return static_cast<const managed<T, false, BASES...>&>(*this);
    }

  public:
    inline const T* operator->() const
    {
      return this->get();
    }
  };
}

#define cfo_MANAGED_BASIC_CONST_METHODS(METHODS)                        \
  template<typename cfo_T, bool cfo_SYNC, typename... cfo_BASES>        \
  class cfo_managed_const_methods :                                     \
    public cfo::const_methods<cfo_T, cfo_SYNC, cfo_BASES...>            \
  {                                                                     \
  private:                                                              \
    cfo_managed_const_methods                                           \
      (const cfo_managed_const_methods<cfo_T, true, cfo_BASES...>&);    \
                                                                        \
  protected:                                                            \
    inline cfo_managed_const_methods(cfo_T *obj) :                      \
      cfo::const_methods<cfo_T, false, cfo_BASES...>(obj)               \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo_managed_const_methods<cfo_T, false, cfo_BASES...>      \
       &methods) :                                                      \
                                                                        \
      cfo::const_methods<cfo_T, false, cfo_BASES...>(methods)           \
      {}                                                                \
                                                                        \
    template<typename cfo_T_other, typename... cfo_BASES_other>         \
      inline cfo_managed_const_methods                                  \
      (const cfo_managed_const_methods                                  \
       <cfo_T_other, false, cfo_BASES_other...>                         \
       &methods) :                                                      \
                                                                        \
      cfo::const_methods<cfo_T, false, cfo_BASES...>(methods)           \
      {}                                                                \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo::managed<cfo_T, true, cfo_BASES...> &manager,          \
       bool shared) :                                                   \
                                                                        \
      cfo::const_methods<cfo_T, true, cfo_BASES...>(manager, shared)    \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline cfo_managed_const_methods                                    \
      (const cfo::managed<cfo_T, true, cfo_BASES...> &manager) :        \
                                                                        \
      cfo::const_methods<cfo_T, true, cfo_BASES...>(manager)            \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (cfo_managed_const_methods<cfo_T, true, cfo_BASES...>             \
       &&methods) :                                                     \
                                                                        \
      cfo::const_methods<cfo_T, true, cfo_BASES...>                     \
      (static_cast<cfo::const_methods<cfo_T, true, cfo_BASES...>&&>     \
       (methods))                                                       \
    {}                                                                  \
                                                                        \
  private:                                                              \
    METHODS                                                             \
  };                                                                    \

#define cfo_MANAGED_CONST_METHODS(BASE, METHODS)                        \
  template<typename cfo_T, bool cfo_SYNC, typename... cfo_BASES>        \
  class cfo_managed_const_methods :                                     \
    public BASE::template cfo_managed_const_methods                     \
      <cfo_T, cfo_SYNC, cfo_BASES...>                                   \
  {                                                                     \
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
      (const cfo_managed_const_methods<cfo_T, false, cfo_BASES...>      \
       &methods) :                                                      \
                                                                        \
      BASE::template cfo_managed_const_methods                          \
      <cfo_T, false, cfo_BASES...>                                      \
      (methods)                                                         \
    {}                                                                  \
                                                                        \
    template<typename cfo_T_other, typename... cfo_BASES_other>         \
      inline cfo_managed_const_methods                                  \
      (const cfo_managed_const_methods                                  \
       <cfo_T_other, false, cfo_BASES_other...>                         \
       &methods) :                                                      \
                                                                        \
      BASE::template cfo_managed_const_methods                          \
      <cfo_T, false, cfo_BASES...>                                      \
      (methods)                                                         \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo::managed<cfo_T, true, cfo_BASES...> &manager,          \
       bool shared) :                                                   \
                                                                        \
      BASE::template cfo_managed_const_methods                          \
      <cfo_T, true, cfo_BASES...>                                       \
      (manager, shared)                                                 \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline cfo_managed_const_methods                                    \
      (const cfo::managed<cfo_T, true, cfo_BASES...> &manager) :        \
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
  private:                                                              \
    METHODS                                                             \
  };                                                                    \

#endif
