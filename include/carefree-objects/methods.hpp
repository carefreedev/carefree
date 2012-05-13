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

#ifndef __CFO_METHODS_HPP
#define __CFO_METHODS_HPP

#include "common.hpp"

#include "accessor.hpp"

namespace cfo { namespace intern
{
  template<typename T, typename... BASES>
  class methods<T, true, BASES...> : public accessor<T, BASES...>
  {
  private:
    methods(const methods<T, true, BASES...>&);

  public:
    inline methods(const managed<T, true, false, BASES...> &manager) :
      accessor<T, BASES...>(manager)
    {}

    inline methods(methods<T, true, BASES...> &&methods) :
      accessor<T>(static_cast<accessor<T, BASES...>&&>(methods))
    {}
  };

  template<typename T, typename... BASES>
  class methods<T, false, BASES...> :
    public T::template cfo_managed_const_methods<T, false, BASES...>
  {
  protected:
    inline methods(T *obj) :
      T::template cfo_managed_const_methods<T, false, BASES...>(obj)
    {}

    inline methods(const std::shared_ptr<T> &manager) :
      T::template cfo_managed_const_methods<T, false, BASES...>(manager)
    {}

    inline methods(const methods<T, false, BASES...> &methods) :
      T::template cfo_managed_const_methods<T, false, BASES...>(methods)
    {}

  public:
    inline T* operator->()
    {
      return this->get();
    }
  };
} }

#define cfo_MANAGED_BASIC_METHODS(METHODS)                              \
  template<typename cfo_T, bool cfo_SYNC, typename... cfo_BASES>        \
  class cfo_managed_methods :                                           \
    public cfo::intern::methods<cfo_T, cfo_SYNC, cfo_BASES...>          \
  {                                                                     \
    template                                                            \
      <typename cfo_T_other, bool cfo_SYNC_other,                       \
       typename... cfo_BASES_other                                      \
       >                                                                \
      friend class cfo_managed_methods;                                 \
                                                                        \
  private:                                                              \
    cfo_managed_methods                                                 \
      (const cfo_managed_methods<cfo_T, true, cfo_BASES...>&);          \
                                                                        \
  protected:                                                            \
    inline cfo_managed_methods(cfo_T *obj) :                            \
      cfo::intern::methods<cfo_T, false, cfo_BASES...>(obj)             \
    {}                                                                  \
                                                                        \
    inline cfo_managed_methods(const std::shared_ptr<cfo_T> &manager) : \
      cfo::intern::methods<cfo_T, false, cfo_BASES...>(manager)         \
    {}                                                                  \
                                                                        \
    inline cfo_managed_methods                                          \
      (const cfo_managed_methods<cfo_T, false, cfo_BASES...>            \
       &methods) :                                                      \
                                                                        \
      cfo::intern::methods<cfo_T, false, cfo_BASES...>(methods)         \
      {}                                                                \
                                                                        \
  public:                                                               \
    inline cfo_managed_methods                                          \
      (const cfo::intern::managed<cfo_T, true, false, cfo_BASES...>     \
       &manager) :                                                      \
                                                                        \
      cfo::intern::methods<cfo_T, true, cfo_BASES...>(manager)          \
    {}                                                                  \
                                                                        \
    inline cfo_managed_methods                                          \
      (cfo_managed_methods<cfo_T, true, cfo_BASES...> &&methods) :      \
                                                                        \
      cfo::intern::methods<cfo_T, true, cfo_BASES...>                   \
      (static_cast<cfo::intern::methods<cfo_T, true, cfo_BASES...>&&>   \
       (methods))                                                       \
    {}                                                                  \
                                                                        \
  private:                                                              \
    METHODS                                                             \
  };                                                                    \

#define cfo_MANAGED_METHODS(BASE, METHODS)                              \
  template<typename cfo_T, bool cfo_SYNC, typename... cfo_BASES>        \
  class cfo_managed_methods :                                           \
    public BASE::template cfo_managed_methods                           \
      <cfo_T, cfo_SYNC, cfo_BASES...>                                   \
  {                                                                     \
    template                                                            \
      <typename cfo_T_other, bool cfo_SYNC_other,                       \
       typename... cfo_BASES_other                                      \
       >                                                                \
      friend class cfo_managed_methods;                                 \
                                                                        \
  private:                                                              \
    cfo_managed_methods                                                 \
      (const cfo_managed_methods<cfo_T, true, cfo_BASES...>&);          \
                                                                        \
  protected:                                                            \
    inline cfo_managed_methods(cfo_T *obj) :                            \
      BASE::template cfo_managed_methods                                \
      <cfo_T, false, cfo_BASES...>(obj)                                 \
    {}                                                                  \
                                                                        \
    inline cfo_managed_methods(const std::shared_ptr<cfo_T> &manager) : \
      BASE::template cfo_managed_methods<cfo_T, false, cfo_BASES...>    \
      (manager)                                                         \
    {}                                                                  \
                                                                        \
    inline cfo_managed_methods                                          \
      (const cfo_managed_methods<cfo_T, false, cfo_BASES...>            \
       &methods) :                                                      \
                                                                        \
      BASE::template cfo_managed_methods<cfo_T, false, cfo_BASES...>    \
      (methods)                                                         \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline cfo_managed_methods                                          \
      (const cfo::intern::managed<cfo_T, true, false, cfo_BASES...>     \
       &manager) :                                                      \
                                                                        \
      BASE::template cfo_managed_methods<cfo_T, true, cfo_BASES...>     \
      (manager)                                                         \
    {}                                                                  \
                                                                        \
    inline cfo_managed_methods                                          \
      (cfo_managed_methods<cfo_T, true, cfo_BASES...> &&methods) :      \
                                                                        \
      BASE::template cfo_managed_methods<cfo_T, true, cfo_BASES...>     \
      (static_cast                                                      \
       <typename BASE::template cfo_managed_methods                     \
       <cfo_T, true, cfo_BASES...>                                      \
       &&>                                                              \
       (methods))                                                       \
    {}                                                                  \
                                                                        \
  private:                                                              \
    METHODS                                                             \
  };                                                                    \

#endif
