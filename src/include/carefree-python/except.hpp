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

#ifndef __CAREFREE_PYTHON_EXCEPT_HPP
#define __CAREFREE_PYTHON_EXCEPT_HPP

#include "common.hpp"

#include "object.hpp"
#include "functions.hpp"

namespace cfo { namespace python
{
  struct raise
  {
    template<typename... ARGS>
    inline raise(PyObject *exc, const ARGS &...args)
    {
      const auto tuple = boost::python::make_tuple(args...);
      PyErr_SetObject(exc, tuple.ptr());
      boost::python::throw_error_already_set();
    }

    template<typename... ARGS>
    inline raise
    (const boost::python::object &exc, const ARGS &...args
     ) :
      raise(exc.ptr(), args...)
    {}

    inline raise();

{% for EXC_NAME in [
     'ValueError',
     'TypeError',
     'LookupError',
     'IndexError',
     ] %}
    template<typename... ARGS>
    static inline void {{ EXC_NAME }}(const ARGS &...args)
    {
      raise(PyExc_{{ EXC_NAME }}, args...);
    }
{% endfor %}
  };

  inline boost::python::tuple exc_info()
  {
    PyObject *exc_type, *exc_value, *traceback;
    PyErr_Fetch(&exc_type, &exc_value, &traceback);

    const auto tuple = boost::python::make_tuple
      (cfo::python::object(exc_type),
       cfo::python::object(exc_value),
       cfo::python::object(traceback));

    //- Take away the initial IncRefs from PyErr_Fetch:
    Py_DecRef(exc_type);
    Py_DecRef(exc_value);
    Py_DecRef(traceback);

    return tuple;
  }

  inline void raise_exc
  (PyObject *exc_type, PyObject *exc_value, PyObject *traceback)
  {
{% for ARG in ['exc_type', 'exc_value', 'traceback'] %}
    if ({{ ARG }} == Py_None)
      {{ ARG }} = NULL;
    else
      //- PyErr_Restore DecRefs all args...
      Py_IncRef({{ ARG }});
{% endfor %}

    PyErr_Restore(exc_type, exc_value, traceback);
    boost::python::throw_error_already_set();
  }

  inline void raise_exc
  (const boost::python::object &exc_type,
   const boost::python::object &exc_value,
   const boost::python::object &traceback)
  {
    raise_exc(exc_type.ptr(), exc_value.ptr(), traceback.ptr());
  }

  inline void raise_exc(const boost::python::tuple &exc_info)
  {
    raise_exc(exc_info[0], exc_info[1], exc_info[2]);
  }

  inline raise::raise()
  {
    raise_exc(exc_info());
  }

  template<typename BASE, typename CATCH = BASE>
  class exception : public BASE, public boost::python::object
  {
    using BASE::BASE;

  public:
    typedef CATCH catch_type;
    typedef boost::python::tuple (*args_translator_type)
      (const catch_type&);

    static boost::python::tuple args(const catch_type &e)
    {
      return boost::python::make_tuple(std::string(e.what()));
    }

    typedef std::string (*args_to_string_type)
      (const boost::python::tuple &args);

  public:
    template
    <args_translator_type ARGS_F = exception<BASE, CATCH>::args,
     args_to_string_type STR_F = args_to_string_type(NULL)
     >
    class class_ : public boost::python::object
    {
    public:
      const boost::python::object __base__;

    private:
      static boost::python::object __str__(const boost::python::object &self)
      {
        assert(STR_F);
        const auto &args = self.attr("args");
        const boost::python::extract<boost::python::tuple> _tuple(args);
        return boost::python::object(STR_F(_tuple()));
      }

      template<std::size_t N>
      static boost::python::object _arg(const boost::python::object &self)
      {
        const auto &args = self.attr("args");
        return args[N];
      }

      template<std::size_t N = 0u>
      inline void _init_arg_properties()
      {}

      template<std::size_t N = 0u, typename... STR>
      inline void _init_arg_properties(const std::string &name, const STR &...names)
      {
        this->attr(name.c_str()) = cfo::python::import::property
          (boost::python::make_function(_arg<N>));

        this->_init_arg_properties<N + 1>(names...);
      }

    public:
      template<typename... STR>
      inline class_
      (const std::string &name, const boost::python::object &base_exc,
       const STR &...argnames
       ) :
        boost::python::object
        (cfo::python::import::type
         (name, boost::python::make_tuple(base_exc),
          boost::python::dict())
         ),
        __base__(base_exc)
      {
        if (STR_F)
          this->attr("__str__") = boost::python::make_function(__str__);

        this->_init_arg_properties<>(argnames...);
      }

      template<typename... STR>
      inline class_
      (const std::string &name, PyObject *base_exc, const STR &...argnames
       ) :
        class_
        (name, boost::python::object(boost::python::borrowed(base_exc)),
         argnames...)
      {}

      inline class_(const class_<ARGS_F, STR_F> &exc) :
        boost::python::object
        (static_cast<const boost::python::object&>(exc)),

        __base__(exc.__base__)
      {}

      inline void operator()(const catch_type &e) const
      {
        PyErr_SetObject
          (this->boost::python::object::ptr(),
           ARGS_F(e).boost::python::tuple::ptr());
      }

      inline class_<ARGS_F, STR_F>& register_()
      {
        boost::python::register_exception_translator<catch_type>(*this);
        return *this;
      }
    };
  };

  class except : protected cfo::python::object
  {
  public:
    inline except(const cfo::python::object &exc_type) :
      cfo::python::object()
    {
      const auto exc_info = cfo::python::exc_info();
      if (cfo::python::is(exc_info[0], exc_type))
        this->cfo::python::object::operator=(exc_info[1]);
    }

  public:
    inline operator bool() const
    {
      return !this->is_none();
    }

    inline bool operator!() const
    {
      return this->is_none();
    }
  };
} }

#endif
