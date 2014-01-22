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

#ifndef __CAREFREE_PYTHON_OBJECT_HPP
#define __CAREFREE_PYTHON_OBJECT_HPP

#include "./common.hpp"

namespace cfo { namespace python
{
  /**
   * A wrapper for `boost::python::object`.
   *
   * - Provides additional constructors and conversion operators.
   */
  class object : public boost::python::object
  {
    using boost::python::object::object;

  public: //- Default and copy contructor.

    inline object() :
      boost::python::object()
    {}

    inline object(const cfo::python::object &obj) :
      boost::python::object(static_cast<const boost::python::object&>(obj))
    {}

  public: //- Construct from boost::python::object.

    inline object(const boost::python::object &obj) :
      boost::python::object(obj)
    {}

    inline object(boost::python::object &&obj) :
      boost::python::object(obj)
    {}

    inline object(const boost::python::api::const_object_item &obj) :
      boost::python::object(obj)
    {}

  public: //- Construct from Python C API Object pointers.

    inline object(PyObject *obj) :
      boost::python::object
      (obj ? boost::python::object(boost::python::borrowed(obj))
       : boost::python::object())
    {}

  public: //- Construct from byte/character.

    inline object(const cfo::byte &byte) :
      boost::python::object(int(byte.value))
    {}

    inline object(const cfo::character &chr) :
      boost::python::object(std::wstring(&chr.value, 1u))
    {}

  public: //-Construct from IP addresses.

    inline object(const cfo::ip::v4::address &addr) :
      boost::python::object
      (cfo::python::import::netaddr::IPAddress(std::uint32_t(addr)))
    {}

    inline object(const cfo::ip::v6::address &addr) :
      boost::python::object
      (cfo::python::import::netaddr::IPAddress(std::string(addr)))
    {}

  public: //- Assignment operators.

    using boost::python::object::operator=;

    inline object& operator=(const cfo::python::object &obj)
    {
      this->boost::python::object::operator=(obj);
      return *this;
    }

    inline object& operator=
    (const boost::python::api::const_object_item &obj)
    {
      this->boost::python::object::operator=(obj);
      return *this;
    }

  public: //- Implicit boost::python::object converters.

    inline operator const boost::python::object&() const
    {
      return static_cast<const boost::python::object&>(*this);
    }

    inline operator boost::python::object&()
    {
      return static_cast<boost::python::object&>(*this);
    }

    inline operator boost::python::object() const
    {
      return static_cast<const boost::python::object&>(*this);
    }

  public: //- Additional conversion operators using cfo::python::* converters.
    // (#include "object.inl").

{% for INT in [INT_TYPES, UINT_TYPES]|chain %}
    inline operator {{ INT }}() const;
{% endfor %}

    inline operator std::string() const;

  }; /* class object */
} } /* namespace cfo::python */

#endif /* __CAREFREE_PYTHON_OBJECT_HPP */
