/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2013 Stefan Zimmermann <zimmermann.code@gmail.com>
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

namespace cfo { namespace python { namespace import
{
  namespace __builtin__
  {
    extern const boost::python::object
      type,

      property,

      int_,
      hash,
      iter,
      repr;
  }
  using namespace __builtin__;

  namespace functools
  {
    extern const boost::python::object
      partial;
  }
  using namespace functools;

  namespace datetime
  {
    extern const boost::python::object
      timedelta,
      tzinfo,
      datetime;
  }
} } }

#endif
