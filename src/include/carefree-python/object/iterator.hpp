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

#ifndef __CAREFREE_PYTHON_OBJECT_ITERATOR_HPP
#define __CAREFREE_PYTHON_OBJECT_ITERATOR_HPP

#include "../object.hpp"

namespace cfo { namespace python
{
  class object::iterator : public object
  {
  private:
    std::unique_ptr<cfo::python::object> _item_ptr;

  public:
    inline iterator() :
      _item_ptr()
    {}

    inline iterator(const cfo::python::object& obj);

    // inline iterator(const iterator&& iter) :
    //   object(cfo::python::import::iter(obj))
    // {}

  public:
    inline const cfo::python::object& operator*() const
    {
      return *this->_item_ptr;
    }

    iterator& operator++();
    //--> src/python/object/iterator.cpp

  public:
    inline bool operator==(const iterator &iter) const
    {
      return !this->_item_ptr.get() && !iter._item_ptr.get();
    }

    inline bool operator!=(const iterator &iter) const
    {
      return !(*this == iter);
    }
  };
} }

#endif
