/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2016 Stefan Zimmermann <zimmermann.code@gmail.com>
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

#ifndef __CAREFREE_PYTHON_STATIC_OBJECT_HPP
#define __CAREFREE_PYTHON_STATIC_OBJECT_HPP

#include "./common.hpp"

#include "./object.hpp"

namespace cfo { namespace python
{
  namespace _static_object
  {
    typedef std::unique_ptr<cfo::python::object> super;
  }
  class static_object : private _static_object::super
  {
  private:
    typedef _static_object::super _super;

  public:
    inline static_object() :
      _super()
    {}

    template<typename O>
    inline static_object(const O &py_obj) :
      _super(new cfo::python::object(py_obj))
    {}

  public:
    inline bool is_null()
    {
      return !this->get();
    }

  public:
    template<typename O>
    inline static_object& operator=(const O &py_obj)
    {
      this->_super::reset(new cfo::python::object(py_obj));
      return *this;
    }

  public:
    inline void release()
    {
      delete this->_super::release();
    }

  protected:
    inline const cfo::python::object* operator->() const
    {
      return this->_super::get();
    }

    inline cfo::python::object* operator->()
    {
      return this->_super::get();
    }

  public:
    inline operator const cfo::python::object&() const
    {
      return *this->_super::get();
    }

    inline operator const boost::python::object&() const
    {
      return static_cast<const boost::python::object&>
        (*this->_super::get());
    }

  public:
    inline PyObject* ptr() const
    {
      return (*this)->ptr();
    }

  public:
    inline operator PyObject*() const
    {
      return (*this)->ptr();
    }

  public:
    inline
    boost::python::api::const_object_attribute
    attr(const std::string &name)
      const
    {
      return (*this)->attr(name.c_str());
    }

    inline
    boost::python::api::const_object_attribute attr(const char *name)
      const
    {
      return (*this)->attr(name);
    }

    inline
    boost::python::api::object_attribute attr(const std::string &name)
    {
      return (*this)->attr(name.c_str());
    }

    inline
    boost::python::api::object_attribute attr(const char *name)
    {
      return (*this)->attr(name);
    }

  public:
    template<typename... ARGS>
    inline boost::python::object operator()(const ARGS &...args)
      const
    {
      return (*this)->operator()(args...);
    }
  };
} }

namespace boost { namespace python { namespace api
{
  template<>
  inline PyObject* object_base_initializer<cfo::python::static_object>
    (const cfo::python::static_object &py_obj)
  {
    return py_obj.ptr();
  }
} } }

#endif /* __CAREFREE_PYTHON_STATIC_OBJECT_HPP */
