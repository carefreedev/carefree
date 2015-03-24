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

#include <carefree-python/object/iterator.hpp>

namespace cfo { namespace python
{
  {% for TYPE, IMPORT in [
       ('bool', 'bool_'),
       ('integer', 'int_'),
       ('float', 'float_'),
       ('complex', 'complex'),
       ('number', 'number_types'),
       ('bytes', 'bytes'),
       ('string', 'string_types'),
       ('tuple', 'tuple'),
       ('list', 'list_types'),
       ('set', 'set'),
       ('dict', 'dict_types'),
       ] %}

  bool object::is_{{ TYPE }}() const
  {
    const int status = PyObject_IsInstance
      (this->ptr(), import::{{ IMPORT }}.ptr());

    if (status != -1)
      return bool(status);

    throw boost::python::error_already_set();
  }

  {% endfor %}
} }
