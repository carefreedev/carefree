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
  template<typename T>
  class const_methods<T, true> : public const_accessor<T>
  {
  private:
    const_methods(const const_methods<T, true>&);

  protected:
    inline const_methods(const managed<T> &manager, bool shared) :
      const_accessor<T>(manager, shared)
    {}

  public:
    inline const_methods(const managed<T> &manager) :
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

    inline const_methods(const const_methods<T, false> &methods) :
      std::shared_ptr<T>(methods)
    {}

  public:
    inline const T* operator->() const
    {
      return this->get();
    }
  };
}

#define cfo_MANAGED_BASIC_CONST_METHODS(METHODS)                        \
  template<typename cfo_T, bool cfo_SYNC>                               \
  class cfo_managed_const_methods :                                     \
    public cfo::const_methods<cfo_T, cfo_SYNC>                          \
  {                                                                     \
  private:                                                              \
    cfo_managed_const_methods                                           \
      (const cfo_managed_const_methods<cfo_T, true>&);                  \
                                                                        \
  protected:                                                            \
    inline cfo_managed_const_methods(cfo_T *obj) :                      \
      cfo::const_methods<cfo_T, false>(obj)                             \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo::managed<cfo_T, true> &manager, bool shared) :         \
                                                                        \
      cfo::const_methods<cfo_T, true>(manager, shared)                  \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline cfo_managed_const_methods                                    \
      (const cfo::managed<cfo_T, true> &manager) :                      \
                                                                        \
      cfo::const_methods<cfo_T, true>(manager)                          \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (cfo_managed_const_methods<cfo_T, true> &&methods) :              \
                                                                        \
      cfo::const_methods<cfo_T, true>                                   \
      (static_cast<cfo::const_methods<cfo_T, true>&&>(methods))         \
    {}                                                                  \
                                                                        \
    METHODS                                                             \
  };                                                                    \

#define cfo_MANAGED_CONST_METHODS(BASE, METHODS)                        \
  template<typename cfo_T, bool cfo_SYNC>                               \
  class cfo_managed_const_methods :                                     \
    public BASE::cfo_managed_const_methods<cfo_T, cfo_SYNC>             \
  {                                                                     \
  private:                                                              \
    cfo_managed_const_methods                                           \
      (const cfo_managed_const_methods<cfo_T, true>&);                  \
                                                                        \
  protected:                                                            \
    inline cfo_managed_const_methods(cfo_T *obj) :                      \
      BASE::cfo_managed_const_methods<cfo_T, false>(obj)                \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (const cfo::managed<cfo_T, true> &manager, bool shared) :         \
                                                                        \
      BASE::cfo_managed_const_methods<cfo_T, true>(manager, shared)     \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline cfo_managed_const_methods                                    \
      (const cfo::managed<cfo_T, true> &manager) :                      \
                                                                        \
      BASE::cfo_managed_const_methods<cfo_T, true>(manager)             \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (cfo_managed_const_methods<cfo_T, true> &&methods) :              \
                                                                        \
      BASE::cfo_managed_const_methods<cfo_T, true>                      \
      (static_cast<BASE::cfo_managed_const_methods<cfo_T, true>&&>      \
       (methods))                                                       \
    {}                                                                  \
                                                                        \
    METHODS                                                             \
  };                                                                    \

#endif
