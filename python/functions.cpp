/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2013 Stefan Zimmermann <zimmermann.code@googlemail.com>
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

#include <carefree-python/functions.hpp>

namespace cfo { namespace python
{
  bool is
  (const boost::python::object &left_obj,
   const boost::python::object &right_obj)
  {
    return left_obj.ptr() == right_obj.ptr();
  }

  std::string str(const boost::python::object &obj)
  {
    const boost::python::object &str_obj = boost::python::str(obj);
    const boost::python::extract<std::string> _str(str_obj);

    return _str();
  }

  std::string repr(const boost::python::object &obj)
  {
    const boost::python::object &repr_obj = cfo::python::import::repr(obj);
    const boost::python::extract<std::string> _repr_str(repr_obj);

    return _repr_str();
  }
} }
