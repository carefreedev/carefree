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

#ifndef __CFO_TOOLS_IP_V4_ADDRESS_HPP
#define __CFO_TOOLS_IP_V4_ADDRESS_HPP

#include <carefree-types/common.hpp>

#include "../address.hpp"

namespace cfo { namespace ip
{
  namespace v4
{
  namespace _address
  {
    typedef ip::base::address
      <boost::asio::ip::address_v4, std::uint8_t, 4u>
      base;
  }
  class address : public _address::base
  {
  public:
    //   class invalid_string_value : std::invalid_argument
    //   {
    //   public:
    //     inline invalid_string_value(const std::string &value) :
    //       std::invalid_argument(value)
    //     {}
    //   };

  public:
    class except;

  protected:
    template<typename ARRAY>
    inline std::uint32_t _address_from_array(const ARRAY &numbers)
    {
      //- (Just numbers[#] results in "zero-size array" error)
      return (std::uint32_t(std::uint8_t(numbers.operator[](0u))) << 24)
        + (std::uint32_t(std::uint8_t(numbers.operator[](1u))) << 16)
        + (std::uint32_t(std::uint8_t(numbers.operator[](2u))) << 8)
        + std::uint32_t(std::uint8_t(numbers.operator[](3u)));
    }

  protected:
    template<typename INT>
    inline std::uint32_t _address
    (const stz::const_array_ptr<INT> &numbers)
    {
      return this->_address_from_array(numbers);
    }

    inline std::uint32_t _address
    (const std::string &numbers,
     bool &return_error = ip::base::_address::no_return_error)
    {
      if (numbers.length() == 4u)
        return this->_address
          (stz::const_array_ptr<std::string::value_type>
           (numbers.c_str(), 4u));

      boost::system::error_code error;
      boost::asio::ip::address_v4 address
        (boost::asio::ip::address_v4::from_string(numbers, error));

      return_error = bool(error);
      return (!error) ? std::uint32_t(address.to_ulong()) : 0;
    }

    template<std::size_t N>
    inline std::uint32_t _address()
    {
      return 0;
    }

    inline std::uint32_t _address()
    {
      return 0;
    }

    template<std::size_t N, typename... INTS>
    inline std::uint32_t _address
    (const std::uint8_t number, const INTS &...numbers)
    {
      return (std::uint32_t(number) << ((3 - N) * 8))
        + (sizeof...(numbers) ? this->_address<N + 1>(numbers...) : 0u);
    }

  public:
    template<typename... INTS>
    inline address(const INTS &...numbers) :
      ip::v4::_address::base
      ((sizeof...(INTS) == 4) ? this->_address<0>(numbers...) : 0u)
    {}

    template<typename INT>
    inline address(const stz::const_array_ptr<INT> &numbers) :
      ip::v4::_address::base
      ((numbers.size() == 4) ? this->_address(numbers) : 0u)
    {}

    inline address
    (const std::string &numbers,
     bool &error = ip::base::_address::no_return_error
     ) :
      ip::v4::_address::base(this->_address(numbers, error))
    {}

    inline address
    (const char *numbers,
     bool &error = ip::base::_address::no_return_error
     ) :
      address(std::string(numbers), error)
    {}

    inline address(const std::uint32_t bytes) :
      ip::v4::_address::base(bytes)
    {}

    inline address(const address &address) :
      ip::v4::_address::base
      (static_cast<const ip::v4::_address::base&>(address))
    {}

    inline address(address &&address) :
      ip::v4::_address::base
      (static_cast<ip::v4::_address::base&&>(address))
    {}

    inline address(const boost::asio::ip::address_v4 &address) :
      ip::v4::_address::base(address)
    {}

    inline address(const boost::asio::ip::address &address) :
      ip::v4::_address::base
      (address.is_v4() ? address.to_v4().to_ulong() : 0u)
    {}

  public:
    inline operator std::uint32_t() const
    {
      return std::uint32_t(this->to_ulong());
    }
  };

  class address::except : public address
  {
    using address::address;

  public:
    inline except(const std::string &numbers) :
      address()
    {
      bool error = false;
      const std::uint32_t bytes = this->_address(numbers, error);
      if (error)
        throw std::invalid_argument(numbers);

      static_cast<boost::asio::ip::address_v4&>(*this)
        = boost::asio::ip::address_v4(bytes);
    }

    inline except(const char *numbers) :
      except(std::string(numbers))
    {}

  public:
    inline std::uint8_t operator[](const std::size_t index) const
    {
      if (index >= 4u)
        throw std::out_of_range(std::to_string(index));

      return this->address::operator[](index);
    }

  public:
    static void _test();
  };
}
} }

#include "./address.inl"

#endif
