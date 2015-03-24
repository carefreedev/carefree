/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2014 Stefan Zimmermann <zimmermann.code@gmail.com>
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

#include <carefree-python/except.hpp>
#include <carefree-python/extract.hpp>

#include <carefree-python/object.inl>

namespace cfo { namespace python
{
  bool is
  (const boost::python::object &left_obj,
   const boost::python::object &right_obj)
  {
    return left_obj.ptr() == right_obj.ptr();
  }

  bool is_instance(PyObject *py_obj, PyObject *py_type)
  {
    const int status = PyObject_IsInstance(py_obj, py_type);
    if (status != -1)
      return bool(status);

    throw boost::python::error_already_set();
  }

{% for INT in CFO_PYTHON_INT_TYPES %}
  {{ INT }} {{ INT.cfo }}
  (const boost::python::object &py_value, const unsigned int base /*= 0u*/)
  {
    const cfo::python::object py_int = base ?
      cfo::python::import::int_(py_value, boost::python::arg("base") = base)
      : cfo::python::import::int_(py_value);

    cfo::python::extract<{{ INT }}> _int(py_int);
    if (!_int.check())
      throw std::invalid_argument(py_int);

    return _int();
  }
{% endfor %}

  std::string str(const boost::python::object &obj)
  {
    const boost::python::object str_obj = boost::python::str(obj);
    const boost::python::extract<std::string> _str(str_obj);
    assert(_str.check());

    return _str();
  }

  std::string repr(const boost::python::object &obj)
  {
    const boost::python::object &repr_obj = cfo::python::import::repr(obj);
    const boost::python::extract<std::string> _repr_str(repr_obj);
    assert(_repr_str.check());

    return _repr_str();
  }
} }
