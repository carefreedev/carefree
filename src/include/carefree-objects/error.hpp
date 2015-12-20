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

#ifndef __CFO_ERROR_HPP
#define __CFO_ERROR_HPP

#include "./common.hpp"

namespace cfo { namespace intern
{
  class error
  {
    template
    <typename T, bool SYNC, bool EXC, typename INIT_T, bool INIT_NULL,
     typename COPY
     >
    friend class managed;

  private: //--- Exception info storage ---

    std::shared_ptr<std::type_index> _type_ptr; // typeid(exception)
    std::string _what; // exception.what()

  public: //--- Constructors ---
    /**
     * Default constructor means __NO__ error occured.
     *
     * ==> bool(*this) == false
     */
    inline error() :
      _type_ptr(NULL),
      _what()
    {}

    /**
     * Error occured ==> Get exception info from `e`.
     */
    inline error(const std::exception &e) :
      _type_ptr(new std::type_index(typeid(e))),
      _what(e.what())
    {}

  public: //--- Set and clear error information ---
    /**
     * Clear stored exception info ==> __NO__ error occured.
     */
    inline error& reset()
    {
      this->_type_ptr.reset();
      this->_what.clear();
      return *this;
    }
    /**
     * Clear stored exception info ==> __NO__ error occured.
     *
     * - Alternative for `reset()`
     */
    inline error& clear()
    {
      return this->reset();
    }
    /**
     * Get and store exception info from `e` ==> error occured.
     */
    inline error& reset(const std::exception &e)
    {
      this->_type_ptr.reset(new std::type_index(typeid(e)));
      this->_what = e.what();
      return *this;
    }
    /**
     * Get and store exception info from `e` ==> error occured.
     *
     * - Operator variant of `reset(e)`
     */
    inline error& operator=(const std::exception &e)
    {
      return this->reset(e);
    }

  public: //--- Logic conversions ---
    /**
     * Check if an error occured.
     */
    inline operator bool() const
    {
      return bool(this->_type_ptr);
    }
    /**
     * Check if __NO__ error occured.
     */
    inline bool operator!() const
    {
      return !bool(*this);
    }

  public: //--- Get error information ---
    /**
     * Get the stored exception's `std::type_index`.
     *
     * - Throws std::bad_typeid if no exception stored.
     */
    inline const std::type_index& type() const
    {
      if (!this->_type_ptr.get())
        throw std::bad_typeid();

      return *this->_type_ptr;
    }
    /**
     * Check if the stored exception is of type `E`.
     *
     * @return (always `false` if no exception occured)
     */
    template<typename EXC_T>
    inline bool is_() const
    {
      return bool(*this) && *this->_type_ptr == typeid(EXC_T);
    }
    /**
     * Get the stored exception's `what()` message.
     */
    inline const std::string& what() const
    {
      return this->_what;
    }
  };
} }

#endif
