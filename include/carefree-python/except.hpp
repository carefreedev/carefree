/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2013 Stefan Zimmermann <zimmermann.code@googlemail.com>
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

namespace cfo { namespace python
{
  template<typename BASE, typename CATCH = BASE>
  class exception : public BASE, public boost::python::object
  {
  public:
    typedef CATCH catch_type;
    typedef boost::python::tuple (*args_translator_type)
    (const catch_type&);

    using BASE::BASE;

    static boost::python::tuple args(const catch_type &e)
    {
      return boost::python::make_tuple(std::string(e.what()));
    }

    template<args_translator_type ARGS = args>
    class class_ : public boost::python::object
    {
    public:
      const boost::python::object __base__;

      inline class_
      (const std::string &name, const boost::python::object &base_exc) :

        boost::python::object
        (cfo::python::import::type
         (name, boost::python::make_tuple(base_exc),
          boost::python::dict())),

        __base__(base_exc)
      {}

      inline class_(const std::string &name, const PyObject *base_exc) :
        class_(name, boost::python::borrowed(base_exc))
      {}

      inline class_(const class_<ARGS> &exc) :
        boost::python::object
        (static_cast<const boost::python::object&>(exc)),

        __base__(exc.__base__)
      {}

      inline void operator()(const catch_type &e) const
      {
        PyErr_SetObject
          (this->boost::python::object::ptr(),
           ARGS(e).boost::python::tuple::ptr());
      }

      inline void register_()
      {
        boost::python::register_exception_translator<catch_type>(*this);
      }
    };
  };
} }

#endif
