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

#ifndef __CAREFREE_PYTHON_OBJECT_HPP
#define __CAREFREE_PYTHON_OBJECT_HPP

#include "./common.hpp"

namespace cfo { namespace python
{
  class object : public boost::python::object
  {
    using boost::python::object::object;

  public:
    inline object(PyObject *obj) :
      boost::python::object
      (obj ? boost::python::object(boost::python::borrowed(obj))
       : boost::python::object())
    {}

    inline object(const cfo::byte &byte) :
      boost::python::object(int(byte.value))
    {}

    inline object(const cfo::character &chr) :
      boost::python::object(std::wstring(&chr.value, 1u))
    {}

    inline object(const cfo::ip::v4::address &addr) :
      boost::python::object
      (cfo::python::import::netaddr::IPAddress(std::uint32_t(addr)))
    {}

    inline object(const cfo::ip::v6::address &addr) :
      boost::python::object
      (cfo::python::import::netaddr::IPAddress(std::string(addr)))
    {}
  };
} }

#endif
