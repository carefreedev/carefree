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

#include <carefree-python/except.hpp>

namespace cfo { namespace python
{
  object::iterator& object::iterator::operator++()
  {
    try
      {
        const auto &self = static_cast<boost::python::object&>(*this);
        //- next() raises StopIteration after last item:
        const auto item = cfo::python::import::next(self);
        this->_item_ptr.reset(new cfo::python::object(item));
      }
    catch (const cfo::python::error&)
      {
        const auto except = cfo::python::except();
        if (!except(PyExc_StopIteration))
          //- Just reraise any unexpected Exception:
          except.raise();

        this->_item_ptr.reset(); //==> *this == object.end()
      }
    return *this;
  }
} }
