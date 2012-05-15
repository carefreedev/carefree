/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2012 Stefan Zimmermann <zimmermann.code@googlemail.com>
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

/* managed vector for managed objects
 */

#ifndef __CFO_MAP_HPP
#define __CFO_MAP_HPP

#include "basic_manager.hpp"
#include "methods.hpp"

namespace cfo { namespace intern
{
  template<typename I, typename T, bool SYNC, typename M, typename... E>
  class basic_manager::map
    // : private std::map<I, managed<T, SYNC>*, E...>
    : private std::map<I, M*, E...>
  {
  private:
    // typedef managed<T, SYNC> manager_type;
    typedef M manager_type;
    typedef std::map<I, manager_type*, E...> map_type;

    // M nullmanager;

  public:
    // inline map() :
    //   nullmanager(typename managed<T, SYNC>::null())
    // {}

    inline ~map()
    {
      BOOST_FOREACH
        (typename map_type::value_type &value,
         *static_cast<map_type*>(this))

        delete value.second;
    }

    inline std::size_t size() const
    {
      return this->map_type::size();
    }

    inline const M& operator[](const I &index) const
    {
      return *static_cast<M*>(this->map_type::at(index));
    }

    inline M& operator[](const I &index)
    {
      return *static_cast<M*>(this->map_type::operator[](index));
    }

    template<typename... A>
    inline void insert(const I &index, const A &...args)
    {
      this->map_type::insert({ index, new M(args...) });
    }

    template<typename... A>
    inline const M& add(const I &index, const A &...args)
    {
      M *obj = new M(args...);
      this->map_type::insert({ index, obj });
      return *obj;
    }

    cfo_MANAGED_BASIC_CONST_METHODS
    (public:

     inline std::size_t size() const
     {
       return (*this)->size();
     }

     inline const M& operator[](const I &index) const
     {
       return (*this)->operator[](index);
     })

    cfo_MANAGED_BASIC_METHODS
    (public:

     template<typename... A>
     inline void insert(const I &index, const A &...args)
     {
       (*this)->insert(index, args...);
     }

     template<typename... A>
     inline const M& add(const I &index, const A &...args)
     {
       return (*this)->add(index, args...);
     })
  };
} }

#endif
