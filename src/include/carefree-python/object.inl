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

#ifndef __CAREFREE_PYTHON_OBJECT_INL
#define __CAREFREE_PYTHON_OBJECT_INL

#include "./object.hpp"

namespace cfo { namespace python
{
  inline object::iterator object::begin()
  {
    return object::iterator(*this);
  }

  inline object::const_iterator object::begin() const
  {
    return object::const_iterator(*this);
  }

  inline object::const_iterator object::cbegin() const
  {
    return this->begin();
  }

  inline object::iterator object::end()
  {
    return object::iterator();
  }

  inline object::const_iterator object::end() const
  {
    return object::const_iterator();
  }

  inline object::const_iterator object::cend() const
  {
    return this->end();
  }

{% for INT in [INT_TYPES, UINT_TYPES]|chain %}
  inline object::operator {{ INT }}() const
  {
    return cfo::python::{{ CFO_PYTHON_INT_TYPES[INT].cfo }}(*this);
  }
{% endfor %}

  inline object::operator std::string() const
  {
    return cfo::python::str(*this);
  }
} }

namespace std
{
  inline std::string to_string(const cfo::python::object &obj)
  {
    return obj.operator std::string();
  }
}

#endif
