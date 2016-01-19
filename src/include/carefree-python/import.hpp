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

#ifndef __CAREFREE_PYTHON_IMPORT_HPP
#define __CAREFREE_PYTHON_IMPORT_HPP

#include "common.hpp"

#include "static_object.hpp"

namespace cfo { namespace python { namespace import
{
  namespace __builtin__
  {
    extern cfo::python::static_object
      object, type,
      property,
      bool_,
      int_, float_, complex, number_types,
      bytes, str, string_types,
      tuple, list, list_types,
      set, dict, dict_types,
      hash,
      iter, next,
      repr;
  }
  using namespace __builtin__;

  namespace functools
  {
    extern cfo::python::static_object
      partial;
  }
  using namespace functools;

  namespace datetime
  {
    extern cfo::python::static_object
      timedelta,
      tzinfo,
      datetime;
  }

  namespace netaddr
  {
    extern cfo::python::static_object
      IPAddress,
      EUI;
  }

  namespace atexit
  {
    extern cfo::python::static_object
      register_;
  }
} } }

#endif
