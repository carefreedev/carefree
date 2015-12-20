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

#ifndef __CFO_TYPES_NAMED_HPP
#define __CFO_TYPES_NAMED_HPP

#include "./common.hpp"

namespace cfo
{
  /**
   * A simple wrapper template for adding names to values of any type.
   */
  template<typename T>
  class named : public boost::tuple<std::string, T>
  {
  private:
    typedef boost::tuple<std::string, T> _tuple;

  public: //- Types.

    typedef _tuple tuple_type;

    typedef std::string name_type;
    typedef T value_type;

  public: //- Constructors.

    inline named(const std::string &name, const T& value) :
      _tuple(name, value)
    {}

    inline named(const boost::tuple<std::string, T> &tuple) :
      _tuple(tuple)
    {}

    /**
     * Initialize with an empty `name`.
     */
    inline named(const T& value) :
      _tuple(std::string(), value)
    {}

  public: //- `name`/`value` access.

    inline const std::string& name() const
    {
      return this->template get<0>();
    }

    inline std::string& name()
    {
      return this->template get<0>();
    }

    inline const T& value() const
    {
      return this->template get<1>();
    }

    inline T& value()
    {
      return this->template get<1>();
    }

  public: //- Reset `name`/`value`.

    /**
     * @return The named wrapper instance for method chaining.
     */
    inline named<T>& reset(const std::string &name, const T &value)
    {
      this->name() = name;
      this->value() = value;
      return *this;
    }

    /**
     * @return The named wrapper instance for method chaining.
     */
    inline named<T>& reset(const _tuple &tuple)
    {
      this->_tuple::operator=(tuple);
      return *this;
    }

    /**
     * @return The named wrapper instance for method chaining.
     */
    inline named<T>& rename(const std::string &name)
    {
      this->name() = name;
      return *this;
    }

    /**
     * Assign a new `value`.
     *
     * @return The named wrapper instance for method chaining.
     */
    inline named<T>& reset(const T &value)
    {
      this->value() = value;
      return *this;
    }

  public: //- Assignment operators.

    inline named<T>& operator=(const _tuple &tuple)
    {
      this->_tuple::operator=(tuple);
      return *this;
    }

    /**
     * Implicitly assign a new `value`.
     */
    inline named<T>& operator=(const T &value)
    {
      this->template get<1>() = value;
      return *this;
    }

  public: //- Equality operators.

    /**
     * Test equality of both `name` and `value`.
     */
    inline bool operator==(const named<T> &other) const
    {
      return this->name == other.name && this->value == other.value;
    }

    /**
     * Test equality of both `name` and `value`.
     */
    inline bool operator==(const _tuple &tuple) const
    {
      return this->_tuple::operator==(tuple);
    }

    /**
     * Only test equality of `value`.
     */
    inline bool operator==(const T &value) const
    {
      return this->value() == value;
    }

  public: //- Converters for implicit `value` access.

    inline operator const T&() const
    {
      return this->value();
    }

    inline operator T&()
    {
      return this->value();
    }

    inline operator T() const
    {
      return this->value();
    }
  };
}

#endif /*__CFO_TYPES_NAMED_HPP*/
