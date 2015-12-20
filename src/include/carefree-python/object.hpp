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
  public:
    typedef object value_type; //- needed for iteration

    class iterator; //--> ./object/iterator.hpp
    typedef iterator const_iterator;

  public: //- inherit base class constructors
    using boost::python::object::object;

  public: //------------------------------------------------------------------
    //                                             Default and copy contructor

    inline object() :
      boost::python::object()
    {}

    inline object(const cfo::python::object &obj) :
      boost::python::object(static_cast<const boost::python::object&>(obj))
    {}

  public: //------------------------------------------------------------------
    //                                    Construct from boost::python::object

    inline object(const boost::python::object &obj) :
      boost::python::object(obj)
    {}

    inline object(boost::python::object &&obj) :
      boost::python::object(obj)
    {}

    inline object(const boost::python::api::object_item &obj) :
      boost::python::object(obj)
    {}

    inline object(const boost::python::api::const_object_item &obj) :
      boost::python::object(obj)
    {}

  public: //------------------------------------------------------------------
    //                             Construct from Python C API Object pointers

    inline object(PyObject *obj) :
      boost::python::object
        (obj ? boost::python::object(boost::python::borrowed(obj))
         : boost::python::object())
    {}

  public: //------------------------------------------------------------------
    //                                      Construct from cfo::byte/character

    inline object(const cfo::byte &byte) :
      boost::python::object(int(byte.value))
    {}

    inline object(const cfo::character &chr) :
      boost::python::object(std::wstring(&chr.value, 1u))
    {}

    inline object(const cfo::bytes &bytes) :
      boost::python::object
        (reinterpret_cast<const char*>(bytes.unmanaged()->data()))
    {}

  public: //------------------------------------------------------------------
    //                                             Construct from IP addresses

    inline object(const cfo::ip::v4::address &addr) :
      boost::python::object
      (cfo::python::import::netaddr::IPAddress(std::uint32_t(addr)))
    {}

    inline object(const cfo::ip::v6::address &addr) :
      boost::python::object
      (cfo::python::import::netaddr::IPAddress(std::string(addr)))
    {}

  public: //------------------------------------------------------------------
    //                                                    Assignment operators

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

  public: //------------------------------------------------------------------
    //                               Implicit boost::python::object converters

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

  public: //------------------------------------------------------------------
    //                                                             Type checks
    //--> src/python/object/check.cpp

    bool is_instance(PyObject *py_type) const;

    inline bool is_instance(const cfo::python::object &py_type) const
    {
      return this->is_instance(py_type.ptr());
    }

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

    inline bool is_{{ TYPE }}() const
    {
      return this->is_instance(import::{{ IMPORT }}.ptr());
    }

  {% endfor %}

  public: //------------------------------------------------------------------
    //         Additional conversion operators using cfo::python::* converters

    //--> ./object.inl (not directly included in this header)

{% for INT in [INT_TYPES, UINT_TYPES]|chain %}
    inline operator {{ INT }}() const;
{% endfor %}

    inline operator std::string() const;

  public: //------------------------------------------------------------------
    //--> ./object.inl                                       Iteration methods

    inline iterator begin();

    inline const_iterator begin() const;
    inline const_iterator cbegin() const;

    inline iterator end();

    inline const_iterator end() const;
    inline const_iterator cend() const;

  }; /* class object */
} } /* namespace cfo::python */

#include "./object/iterator.hpp"

#endif /* __CAREFREE_PYTHON_OBJECT_HPP */
