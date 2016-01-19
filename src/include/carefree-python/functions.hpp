/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2015 Stefan Zimmermann <zimmermann.code@gmail.com>
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

#ifndef __CAREFREE_PYTHON_FUNCTIONS_HPP
#define __CAREFREE_PYTHON_FUNCTIONS_HPP

#include "common.hpp"

#include "object.hpp"
#include "static_object.hpp"

#include "extract.hpp"

namespace cfo { namespace python
{
  bool is
  (const boost::python::object &left_obj,
   const boost::python::object &right_obj);

  bool is_instance(PyObject *py_obj, PyObject *py_type);

  inline bool is_instance
    (PyObject *py_obj, const boost::python::object &py_type)
  {
    return is_instance(py_obj, py_type.ptr());
  }

  inline bool is_instance
    (PyObject *py_obj, const cfo::python::object &py_type)
  {
    return is_instance(py_obj, py_type.ptr());
  }

  inline bool is_instance
    (PyObject *py_obj, const cfo::python::static_object &py_type)
  {
    return is_instance(py_obj, py_type.ptr());
  }

  inline bool is_instance
    (const boost::python::object &py_obj, PyObject *py_type)
  {
    return is_instance(py_obj.ptr(), py_type);
  }

  inline bool is_instance
    (const boost::python::object &py_obj,
     const boost::python::object &py_type)
  {
    return is_instance(py_obj.ptr(), py_type.ptr());
  }

  inline bool is_instance
    (const boost::python::object &py_obj,
     const cfo::python::object &py_type)
  {
    return is_instance(py_obj.ptr(), py_type.ptr());
  }

  inline bool is_instance
    (const boost::python::object &py_obj,
     const cfo::python::static_object &py_type)
  {
    return is_instance(py_obj.ptr(), py_type.ptr());
  }

  inline bool is_instance
    (const cfo::python::object &py_obj, PyObject *py_type)
  {
    return is_instance(py_obj.ptr(), py_type);
  }

  inline bool is_instance
    (const cfo::python::object &py_obj,
     const boost::python::object &py_type)
  {
    return is_instance(py_obj.ptr(), py_type.ptr());
  }

  inline bool is_instance
    (const cfo::python::object &py_obj,
     const cfo::python::object &py_type)
  {
    return is_instance(py_obj.ptr(), py_type.ptr());
  }

  inline bool is_instance
    (const cfo::python::object &py_obj,
     const cfo::python::static_object &py_type)
  {
    return is_instance(py_obj.ptr(), py_type.ptr());
  }

  inline bool is_instance
    (const cfo::python::static_object &py_obj, PyObject *py_type)
  {
    return is_instance(py_obj.ptr(), py_type);
  }

  inline bool is_instance
    (const cfo::python::static_object &py_obj,
     const boost::python::object &py_type)
  {
    return is_instance(py_obj.ptr(), py_type.ptr());
  }

  inline bool is_instance
    (const cfo::python::static_object &py_obj,
     const cfo::python::object &py_type)
  {
    return is_instance(py_obj.ptr(), py_type.ptr());
  }

  inline bool is_instance
    (const cfo::python::static_object &py_obj,
     const cfo::python::static_object &py_type)
  {
    return is_instance(py_obj.ptr(), py_type.ptr());
  }

  std::string str(const boost::python::object &obj);

{% for INT in CFO_PYTHON_INT_TYPES %}

  {{ INT }} {{ INT.cfo }}
    (const boost::python::object &py_value, const unsigned int base = 0u);

{% endfor %}

  std::string repr(const boost::python::object &obj);
} }

#endif
