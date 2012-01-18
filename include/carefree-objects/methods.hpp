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

  // template<typename T>
  // class methods<T, false> : public const_methods<T, false>
  // {
  // };
}

#define cfo_MANAGED_METHODS(METHODS)                                    \
  template<typename T, bool SYNC>                                       \
  class cfo_managed_methods : public cfo::methods<T, SYNC>              \
  {                                                                     \
  private:                                                              \
    cfo_managed_methods(const cfo_managed_methods<T, true>&);           \
                                                                        \
  public:                                                               \
    inline cfo_managed_methods(const cfo::managed<T, SYNC> &manager) :  \
      cfo::methods<T, SYNC>(manager)                                    \
    {}                                                                  \
                                                                        \
    inline cfo_managed_methods                                          \
      (cfo_managed_methods<T, SYNC> &&methods) :                        \
                                                                        \
      cfo::methods<T, SYNC>                                             \
      (static_cast<cfo::methods<T, SYNC>&&>(methods))                   \
    {}                                                                  \
                                                                        \
    METHODS                                                             \
  };                                                                    \

#endif
