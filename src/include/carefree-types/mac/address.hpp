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

#ifndef __CFO_TOOLS_MAC_ADDRESS_HPP
#define __CFO_TOOLS_MAC_ADDRESS_HPP

#include <carefree-types/common.hpp>

namespace cfo { namespace mac
{
  class address : public std::array<std::uint8_t, 6u>
  {
  public:
    typedef std::array<std::uint8_t, 6u> array_type;

  private:
    typedef boost::char_separator<std::string::value_type> _separator_type;
    typedef boost::tokenizer<_separator_type> _tokenizer_type;

    void _address
    (const std::string &address, const char *separators, bool &error);

    void _address(const std::string &address, bool &error);

  public: //------------------------------------------------------------------
    //                                                            Constructors

    inline address() :
      array_type()
    {}

    inline address
    (const std::uint8_t byte0,
     const std::uint8_t byte1,
     const std::uint8_t byte2,
     const std::uint8_t byte3,
     const std::uint8_t byte4,
     const std::uint8_t byte5) :

      array_type({ { byte0, byte1, byte2, byte3, byte4, byte5 } })
    {}

    template<typename INT>
    inline address(const std::array<INT, 6u> &bytes) :
      array_type
      ({ { bytes[0u], bytes[1u], bytes[2u],
            bytes[3u], bytes[4u], bytes[5u] } })
    {}

    template<typename INT>
    inline address(const stz::const_array_ptr<INT> &bytes, bool &error);
    //--> ./address.inl

    template<typename INT>
    inline address(const stz::array_ptr<INT> &bytes, bool &error) :
      address(stz::const_array_ptr<INT>(bytes), error)
    {}

    template<typename INT>
    inline address(const std::vector<INT> &bytes, bool &error) :
      address(stz::const_array_ptr<INT>(bytes), error)
    {}

    template
    <typename INT0,
     typename INT1,
     typename INT2,
     typename INT3,
     typename INT4,
     typename INT5
     >
    inline address
    (const boost::tuple<INT0, INT1, INT2, INT3, INT4, INT5> &bytes) :

      array_type
      ({ { bytes.template get<0>(),
           bytes.template get<1>(),
           bytes.template get<2>(),
           bytes.template get<3>(),
           bytes.template get<4>(),
           bytes.template get<5>() } })
    {}

    inline address(const std::string &str, bool &error) :
      array_type()
    {
      this->_address(str, error);
    }

    inline address(const char *str, bool &error):
      address(std::string(str), error)
    {}

    inline address(const mac::address &address) :
      array_type(static_cast<const array_type&>(address))
    {}

  public: //------------------------------------------------------------------
    //                                                        Logic operations

    inline operator bool() const
    {
      for (const std::uint8_t &byte : *this)
        if (byte)
          return true;

      return false;
    }

    inline bool operator!() const
    {
      return !bool(*this);
    }

    inline bool operator==(const mac::address &address) const
    {
      return !std::memcmp(this->data(), address.data(), 6u);
    }

    inline bool operator<(const mac::address &address) const
    {
      return std::memcmp(this->data(), address.data(), 6u) < 0;
    }

    inline bool operator>(const mac::address &address) const
    {
      return std::memcmp(this->data(), address.data(), 6u) > 0;
    }

  public: //------------------------------------------------------------------
    //                                                             Conversions

    inline operator const std::uint8_t*() const
    {
      return this->data();
    }

    std::string to_string() const;
    //--> src/types/mac/address/convert.cpp

    inline operator std::string() const
    {
      return this->to_string();
    }
  };
} }

#include "./address.inl"

inline std::ostream& operator<<
(std::ostream &out, const cfo::mac::address &mac)
{
  out << mac.to_string();
  return out;
}

#endif /*__CFO_TOOLS_MAC_ADDRESS_HPP*/
