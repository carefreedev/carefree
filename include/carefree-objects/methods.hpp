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

namespace cfo
{
  template<typename T>
  class methods<T, true> : public accessor<T>
  {
  private:
    methods(const methods<T, true>&);

  public:
    inline methods(const managed<T> &manager) :
      accessor<T>(manager)
    {}

    inline methods(methods<T, true> &&methods) :
      accessor<T>(static_cast<accessor<T>&&>(methods))
    {}
  };

  template<typename T>
  class methods<T, false> :
    public T::template cfo_managed_const_methods<T, false>
  {
  protected:
    inline methods(T *obj) :
      T::template cfo_managed_const_methods<T, false>(obj)
    {}

    inline methods(const methods<T, false> &methods) :
      T::template cfo_managed_const_methods<T, false>(methods)
    {}

  public:
    inline T* operator->()
    {
      return this->get();
    }
  };
}

#define cfo_MANAGED_METHODS(METHODS)                                    \
  template<typename cfo_T, bool cfo_SYNC>                               \
  class cfo_managed_methods : public cfo::methods<cfo_T, cfo_SYNC>      \
  {                                                                     \
  private:                                                              \
    cfo_managed_methods(const cfo_managed_methods<cfo_T, true>&);       \
                                                                        \
  protected:                                                            \
    inline cfo_managed_methods(cfo_T *obj) :                            \
      cfo::methods<cfo_T, false>(obj)                                   \
    {}                                                                  \
                                                                        \
    inline cfo_managed_methods                                          \
      (const cfo_managed_methods<cfo_T, false> &methods) :              \
                                                                        \
      cfo::methods<cfo_T, false>(methods)                               \
      {}                                                                \
                                                                        \
  public:                                                               \
    inline cfo_managed_methods                                          \
      (const cfo::managed<cfo_T, true> &manager) :                      \
                                                                        \
      cfo::methods<cfo_T, true>(manager)                                \
    {}                                                                  \
                                                                        \
    inline cfo_managed_methods                                          \
      (cfo_managed_methods<cfo_T, true> &&methods) :                    \
                                                                        \
      cfo::methods<cfo_T, true>                                         \
      (static_cast<cfo::methods<cfo_T, true>&&>(methods))               \
    {}                                                                  \
                                                                        \
    METHODS                                                             \
  };                                                                    \

#endif
