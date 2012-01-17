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
}

#define cfo_MANAGED_CONST_METHODS(TYPE, METHODS)                        \
  template<typename T, bool SYNC>                                       \
  class cfo_managed_const_methods : public cfo::const_methods<T, SYNC>  \
  {                                                                     \
  private:                                                              \
    cfo_managed_const_methods                                           \
      (const cfo_managed_const_methods<T, true>&);                      \
                                                                        \
  protected:                                                            \
    inline cfo_managed_const_methods                                    \
      (const cfo::managed<T> &manager, bool shared) :                   \
                                                                        \
      cfo::const_methods<T, SYNC>(manager, shared)                      \
    {}                                                                  \
                                                                        \
  public:                                                               \
    inline cfo_managed_const_methods                                    \
      (const cfo::managed<T, SYNC> &manager) :                          \
                                                                        \
      cfo::const_methods<T, SYNC>(manager)                              \
    {}                                                                  \
                                                                        \
    inline cfo_managed_const_methods                                    \
      (cfo_managed_const_methods<T, SYNC> &&methods) :                  \
                                                                        \
      cfo::const_methods<T, SYNC>                                       \
      (static_cast<cfo::const_methods<T, SYNC>&&>(methods))             \
    {}                                                                  \
                                                                        \
    METHODS                                                             \
  };                                                                    \

#endif
