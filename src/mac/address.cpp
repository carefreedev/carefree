/* carefree-objects
 *
 * a thread-safe object manager extension for c++
 *
 * Copyright (C) 2011-2014 Stefan Zimmermann <zimmermann.code@gmail.com>
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

#include <carefree-types/mac.hpp>

namespace cfo { namespace mac
{
  void address::_address
  (const std::string &address, const char *separators, bool &error)
  {
    std::size_t n = 0u;
    int byte;
    _tokenizer_type tokens(address, _separator_type(separators));
    for (const std::string &hexbyte : tokens)
      {
        if (n >= 6u)
          {
            error = true;
            return;
          }
        std::istringstream in(hexbyte);
        if (!(in >> std::hex >> byte).eof())
          {
            error = true;
            return;
          }
        (*this)[n++] = byte;
      }
    error = false;
  }

  void address::_address(const std::string &address, bool &error)
  {
    error = false;
    if (address.length() == 6)
      {
        std::memcpy(&(*this)[0u], &address[0u], 6u);
        return;
      }
    for (const char &c : address)
      {
        if (c == ':')
          {
            this->_address(address, ":", error);
            return;
          }

        if (c == '-')
          {
            this->_address(address, "-", error);
            return;
          }
      }
    error = true;
  }
} }
