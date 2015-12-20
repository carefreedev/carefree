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

#ifndef __CFO_TYPES_C_ARRAY_HPP
#define __CFO_TYPES_C_ARRAY_HPP

#include "./common.hpp"

namespace cfo
{
  template<typename T>
  class c_array : public stz::array_ptr<T>
  {
    using stz::array_ptr<T>::array_ptr;

  protected:
    template<typename SUPER>
    class _except;

  public:
    typedef class _except<c_array<T> > except;

  public:
    using stz::array_ptr<T>::get;

    // inline T* get(std::size_t &size)
    // {
    //   size = this->size;
    //   return this->get();
    // }

    // inline const T* get(std::size_t &size) const
    // {
    //   size = this->size;
    //   return this->get();
    // }

{% for INT in [INT_TYPES, UINT_TYPES]|chain %}
    inline T* get({{ INT }} &size)
    {
      size = static_cast<{{ INT }}>(this->size());
      return this->get();
    }

    inline const T* get({{ INT }} &size) const
    {
      size = static_cast<{{ INT }}>(this->size());
      return this->get();
    }
{% endfor %}
  };

  template<typename T>
  template<typename SUPER>
  class c_array<T>::_except : public SUPER
  {
    using SUPER::SUPER;

  public:
    inline _except(T *values, const std::size_t size) :
      SUPER(values, size)
    {
      if (!values && size)
        throw std::invalid_argument
          ("NULL values with size " + std::to_string(size));
    }

  public:
    using SUPER::get;

{% for INT in [INT_TYPES, UINT_TYPES]|chain %}
    inline T* get({{ INT }} &size)
    {
      if (this->size() > {{ INT.max }}u)
        throw std::overflow_error
          ("Assigning array size to {{ INT }}: "
           + std::to_string(this->size()));

      size = static_cast<{{ INT }}>(this->size());
      return this->get();
    }

    inline const T* get({{ INT }} &size) const
    {
      if (this->size() > {{ INT.max }}u)
        throw std::overflow_error
          ("Assigning array size to {{ INT }}: "
           + std::to_string(this->size()));

      size = static_cast<{{ INT }}>(this->size());
      return this->get();
    }
{% endfor %}
  };

  template<typename T>
  class const_c_array : public stz::const_array_ptr<T>
  {
    using stz::const_array_ptr<T>::const_array_ptr;

  protected:
    template<typename SUPER>
    class _except;

  public:
    typedef class _except<const_c_array<T> > except;

  public:
    using stz::const_array_ptr<T>::get;

    // inline const T* get(std::size_t &size) const
    // {
    //   size = this->size;
    //   return this->get();
    // }

{% for INT in [INT_TYPES, UINT_TYPES]|chain %}
    inline const T* get({{ INT }} &size) const
    {
      size = static_cast<{{ INT }}>(this->size());
      return this->get();
    }
{% endfor %}
  };

  template<typename T>
  template<typename SUPER>
  class const_c_array<T>::_except : public SUPER
  {
    using SUPER::SUPER;

  public:
    inline _except(const T *values, const std::size_t size) :
      SUPER(values, size)
    {
      if (!values && size)
        throw std::invalid_argument
          ("NULL values with size " + std::to_string(size));
    }

  public:
    using SUPER::get;

{% for INT in [INT_TYPES, UINT_TYPES]|chain %}
    inline const T* get({{ INT }} &size) const
    {
      if (this->size() > {{ INT.max }}u)
        throw std::overflow_error
          ("Assigning array size to {{ INT }}: "
           + std::to_string(this->size()));

      size = static_cast<{{ INT }}>(this->size());
      return this->get();
    }
{% endfor %}
  };
}

#endif
