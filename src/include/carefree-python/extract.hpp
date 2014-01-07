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

#ifndef __CAREFREE_PYTHON_EXTRACT_HPP
#define __CAREFREE_PYTHON_EXTRACT_HPP

#include "common.hpp"

#include "object.hpp"

namespace cfo { namespace python
{
  template<typename T>
  class extract : public boost::python::extract<T>
  {
  public:
    inline extract(const cfo::python::object &py_value) :
      boost::python::extract<T>
      (static_cast<const boost::python::object&>(py_value))
    {}

    // using boost::python::extract<T>::extract;
    inline extract(const boost::python::object &py_value) :
      boost::python::extract<T>(py_value)
    {}

    inline bool check() const
    {
      return this->boost::python::extract<T>::check();
    }
  };


{% for int in [INT_TYPES, UINT_TYPES]|chain %}
  template<>
  inline bool extract<{{ int }}>::check() const
  {
    if (!this->boost::python::extract<{{ int }}>::check())
      return false;

    try
      {
        this->operator()();
      }
    catch (const boost::python::error_already_set &e)
      {
        PyObject
          *py_exc_type_ptr, *py_exc_value_ptr, *py_exc_traceback_ptr;
        PyErr_Fetch
          (&py_exc_type_ptr, &py_exc_value_ptr, &py_exc_traceback_ptr);

        if (py_exc_type_ptr != PyExc_OverflowError)
          PyErr_Restore
            (py_exc_type_ptr, py_exc_value_ptr, py_exc_traceback_ptr);

        return false;
      }

    return true;
  }
{% endfor %}

} }

#endif
