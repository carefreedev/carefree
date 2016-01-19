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

#include <carefree-python/import.hpp>
#include <carefree-python/except.hpp>

namespace cfo { namespace python { namespace import
{
  namespace __builtin__
  {
    static boost::python::object _module()
    {
      try
        {
          return boost::python::import("__builtin__");
        }
      catch(const cfo::python::error&)
        {
          const auto except = cfo::python::except();
          if (!except(PyExc_ImportError))
            except.raise();
        }
      return boost::python::import("builtins");
    }

    static cfo::python::static_object module = _module();

    cfo::python::static_object
      object = module.attr("object"),
      type = module.attr("type"),

      property = module.attr("property"),

      bool_ = module.attr("bool"),

      int_ = module.attr("int"),
      float_ = module.attr("float"),
      complex = module.attr("complex"),
      number_types = boost::python::make_tuple(int_, float_, complex),

      bytes = module.attr("bytes"),
      str = module.attr("str"),
      string_types = boost::python::make_tuple(str),

      tuple = module.attr("tuple"),
      list = module.attr("list"),
      list_types = boost::python::make_tuple(list),

      set = module.attr("set"),
      dict = module.attr("dict"),
      dict_types = boost::python::make_tuple(dict),

      hash = module.attr("hash"),
      iter = module.attr("iter"),
      next = module.attr("next"),
      repr = module.attr("repr");
  }

  namespace functools
  {
    static cfo::python::static_object module
    = boost::python::import("functools");

    cfo::python::static_object
      partial = module.attr("partial");
  }

  namespace datetime
  {
    static cfo::python::static_object module
    = boost::python::import("datetime");

    cfo::python::static_object
      timedelta = module.attr("timedelta"),
      tzinfo = module.attr("tzinfo"),
      datetime = module.attr("datetime");
  }

  namespace netaddr
  {
    static cfo::python::static_object module
    = boost::python::import("netaddr");

    cfo::python::static_object
      IPAddress = module.attr("IPAddress"),
      EUI = module.attr("EUI");
  }

  namespace atexit
  {
    static cfo::python::static_object module
      = boost::python::import("atexit");
  }

  static void cleanup()
  {
    __builtin__::module.release();

    __builtin__::object.release();
    __builtin__::type.release();

    __builtin__::property.release();

    __builtin__::bool_.release();

    __builtin__::int_.release();
    __builtin__::float_.release();
    __builtin__::complex.release();
    __builtin__::number_types.release();

    __builtin__::bytes.release();
    __builtin__::str.release();
    __builtin__::string_types.release();

    __builtin__::tuple.release();
    __builtin__::list.release();
    __builtin__::list_types.release();

    __builtin__::set.release();
    __builtin__::dict.release();
    __builtin__::dict_types.release();

    __builtin__::hash.release();
    __builtin__::iter.release();
    __builtin__::next.release();
    __builtin__::repr.release();

    functools::module.release();

    functools::partial.release();

    datetime::module.release();

    datetime::timedelta.release();
    datetime::tzinfo.release();
    datetime::datetime.release();

    netaddr::module.release();

    netaddr::IPAddress.release();
    netaddr::EUI.release();

    atexit::module.release();

    atexit::register_.release();
  }

  namespace atexit
  {
    static boost::python::object _register()
    {
      boost::python::object register_ = atexit::module.attr("register");
      register_(boost::python::make_function(&import::cleanup));
      return register_;
    }

    cfo::python::static_object register_ = _register();
  }
} } }
