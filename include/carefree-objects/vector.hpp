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

#ifndef __CFO_VECTOR_HPP
#define __CFO_VECTOR_HPP

#include "basic_manager.hpp"
#include "methods.hpp"

namespace cfo { namespace intern
{
  template<typename T, bool SYNC, bool EXC, typename MGR>
  class basic_manager::vector : private std::vector<MGR*>
  {
  private:
    typedef std::vector<MGR*> _base_vector_type;

  public:
    typedef managed<T, SYNC, EXC> element_manager_type;

    typedef managed<vector<T, SYNC, EXC>, SYNC, EXC> manager_type;

    class iterator;
    class const_iterator;

    inline ~vector()
    {
      for (const MGR *element_ptr
             : static_cast<const _base_vector_type>(*this))

        delete element_ptr;
    }

    inline std::size_t size() const
    {
      return this->_base_vector_type::size();
    }

    inline const MGR& operator[](std::size_t index) const
    {
      return static_cast<MGR&>
        (static_cast<element_manager_type&>
         (*this->_base_vector_type::operator[](index)));
    }

    inline MGR& operator[](std::size_t index)
    {
      return static_cast<MGR&>
        (static_cast<element_manager_type&>
         (*this->_base_vector_type::operator[](index)));
    }

    template<typename... A>
    inline void push_back(const A &...args)
    {
      this->_base_vector_type::push_back
        (static_cast<MGR*>
         (static_cast<element_manager_type*>(new MGR(args...))));
    }

    template<typename... A>
    inline MGR& append(const A &...args)
    {
      MGR *element_ptr =
        static_cast<MGR*>
        (static_cast<element_manager_type*>(new MGR(args...)));

      this->_base_vector_type::push_back(element_ptr);
      return *element_ptr;
    }

#define _cfo_MANAGED_VECTOR_TEMPLATE_ARGS       \
    T, SYNC, EXC, MGR                           \

    cfo_MANAGED_BASIC_CONST_METHODS
    (vector<_cfo_MANAGED_VECTOR_TEMPLATE_ARGS>,

     public:

     typedef MGR value_type;

     typedef const MGR& const_reference;
     typedef const MGR& reference;

     typedef vector<_cfo_MANAGED_VECTOR_TEMPLATE_ARGS>::const_iterator
     const_iterator;

     inline std::size_t size() const
     {
       return (*this)->size();
     }

     inline const MGR& operator[](std::size_t index) const
     noexcept(!cfo_EXC)
     {
       if (cfo_EXC && index >= this->size())
         {
           std::ostringstream what;
           what << "Index out of range: " << index;
           throw std::out_of_range(what.str());
         }

       return (*this)->operator[](index);
     }

     inline const MGR& last() const
     noexcept(!cfo_EXC)
     {
       if (cfo_EXC && !this->size())
         throw std::out_of_range("No last element");

       return (*this)[this->size() - 1];
     }

     inline const_iterator cbegin() const;

     inline const_iterator cend() const;

     inline const_iterator begin() const;

     inline const_iterator end() const;
     )

    cfo_MANAGED_BASIC_METHODS
    (vector<_cfo_MANAGED_VECTOR_TEMPLATE_ARGS>,

     public:

     typedef MGR& reference;

     typedef vector<_cfo_MANAGED_VECTOR_TEMPLATE_ARGS>::iterator iterator;

     template<typename... A>
     inline void push_back(const A &...args)
     {
       (*this)->push_back(args...);
     }

     template<typename... A>
     inline MGR& append(const A &...args)
     {
       return (*this)->append(args...);
     }

     inline MGR& operator[](std::size_t index)
     noexcept(!cfo_EXC)
     {
       if (cfo_EXC && index >= this->size())
         {
           std::ostringstream what;
           what << "Index out of range: " << index;
           throw std::out_of_range(what.str());
         }

       return (*this)->operator[](index);
     }

     inline const MGR& operator[](std::size_t index) const
     {
       return this->const_methods::operator[](index);
     }

     inline MGR& last()
     noexcept(!cfo_EXC)
     {
       if (cfo_EXC && !this->size())
         throw std::out_of_range("No last element");

       return (*this)[this->size() - 1];
     }

     inline const MGR& last() const
     {
       return this->const_methods::last();
     }

     inline const_iterator begin() const;

     inline const_iterator end() const;

     inline iterator begin();

     inline iterator end();
     )
  };

  template<typename T, bool SYNC, bool EXC, typename MGR>
  class basic_manager::vector<T, SYNC, EXC, MGR>::const_iterator :
    private vector<T, SYNC, EXC, MGR>::manager_type
  {
  private:
    std::size_t _index;

  public:
    typedef vector<T, SYNC, EXC, MGR>::manager_type vector_manager_type;

    inline const_iterator
    (const vector_manager_type &vector, const std::size_t index = 0u) :

      vector_manager_type(vector),
      _index(index)
    {}

    inline const_iterator(const const_iterator &other) :
      vector_manager_type(other.const_manager()),
      _index(other._index)
    {}

    inline const_iterator(const_iterator &&other) :
      vector_manager_type(static_cast<vector_manager_type&&>(other)),
      _index(other._index)
    {}

    inline const MGR& operator*()
    {
      return this->vector_manager_type::operator[](this->_index);
    }

    inline std::size_t index()
    {
      return this->_index;
    }

    inline const_iterator& operator++()
    {
      ++this->_index;
      return *this;
    }

    inline bool operator==(const const_iterator &other)
    {
      return this->unmanaged() == other.unmanaged()
        && this->_index == other._index;
    }

    inline bool operator!=(const const_iterator &other)
    {
      return this->unmanaged() != other.unmanaged()
        || this->_index != other._index;
    }
  };


  template<typename T, bool SYNC, bool EXC, typename MGR>
  template<typename cfo_T, bool cfo_SYNC, bool cfo_EXC, typename cfo_BASE>
  inline
  typename basic_manager::vector<T, SYNC, EXC, MGR>::const_iterator
  basic_manager::vector<T, SYNC, EXC, MGR>
  ::_cfo_managed_const_methods<cfo_T, cfo_SYNC, cfo_EXC, cfo_BASE>
  ::cbegin
  ()
    const
  {
    return const_iterator(this->const_manager());
  }

  template<typename T, bool SYNC, bool EXC, typename MGR>
  template<typename cfo_T, bool cfo_SYNC, bool cfo_EXC, typename cfo_BASE>
  inline
  typename basic_manager::vector<T, SYNC, EXC, MGR>::const_iterator
  basic_manager::vector<T, SYNC, EXC, MGR>
  ::_cfo_managed_const_methods<cfo_T, cfo_SYNC, cfo_EXC, cfo_BASE>
  ::cend
  ()
    const
  {
    return const_iterator(this->const_manager(), this->size());
  }
  template<typename T, bool SYNC, bool EXC, typename MGR>
  template<typename cfo_T, bool cfo_SYNC, bool cfo_EXC, typename cfo_BASE>
  inline
  typename basic_manager::vector<T, SYNC, EXC, MGR>::const_iterator
  basic_manager::vector<T, SYNC, EXC, MGR>
  ::_cfo_managed_const_methods<cfo_T, cfo_SYNC, cfo_EXC, cfo_BASE>
  ::begin
  ()
    const
  {
    return const_iterator(this->const_manager());
  }

  template<typename T, bool SYNC, bool EXC, typename MGR>
  template<typename cfo_T, bool cfo_SYNC, bool cfo_EXC, typename cfo_BASE>
  inline
  typename basic_manager::vector<T, SYNC, EXC, MGR>::const_iterator
  basic_manager::vector<T, SYNC, EXC, MGR>
  ::_cfo_managed_const_methods<cfo_T, cfo_SYNC, cfo_EXC, cfo_BASE>
  ::end
  ()
    const
  {
    return const_iterator(this->const_manager(), this->size());
  }

  template<typename T, bool SYNC, bool EXC, typename MGR>
  class basic_manager::vector<T, SYNC, EXC, MGR>::iterator :
    private vector<T, SYNC, EXC, MGR>::manager_type
  {
  private:
    std::size_t _index;

  public:
    typedef vector<T, SYNC, EXC, MGR>::manager_type vector_manager_type;

    inline iterator
    (const vector_manager_type &vector, const std::size_t index = 0u) :

      vector_manager_type(vector),
      _index(index)
    {}

    inline iterator(const iterator &other) :
      vector_manager_type(other.const_manager()),
      _index(other._index)
    {}

    inline iterator(iterator &&other) :
      vector_manager_type(static_cast<vector_manager_type&&>(other)),
      _index(other._index)
    {}

    inline MGR& operator*()
    {
      return this->vector_manager_type::operator[](this->_index);
    }

    inline std::size_t index()
    {
      return this->_index;
    }

    inline iterator& operator++()
    {
      ++this->_index;
      return *this;
    }

    inline bool operator==(const iterator &other)
    {
      return this->unmanaged() == other.unmanaged()
        && this->_index == other._index;
    }

    inline bool operator!=(const iterator &other)
    {
      return this->unmanaged() != other.unmanaged()
        || this->_index != other._index;
    }
  };

  template<typename T, bool SYNC, bool EXC, typename MGR>
  template<typename cfo_T, bool cfo_SYNC, bool cfo_EXC>
  inline
  typename basic_manager::vector<T, SYNC, EXC, MGR>::const_iterator
  basic_manager::vector<T, SYNC, EXC, MGR>
  ::cfo_managed_methods<cfo_T, cfo_SYNC, cfo_EXC>
  ::begin
  ()
    const
  {
    return const_iterator(this->const_manager());
  }

  template<typename T, bool SYNC, bool EXC, typename MGR>
  template<typename cfo_T, bool cfo_SYNC, bool cfo_EXC>
  inline
  typename basic_manager::vector<T, SYNC, EXC, MGR>::const_iterator
  basic_manager::vector<T, SYNC, EXC, MGR>
  ::cfo_managed_methods<cfo_T, cfo_SYNC, cfo_EXC>
  ::end
  ()
    const
  {
    return const_iterator(this->const_manager(), this->size());
  }

  template<typename T, bool SYNC, bool EXC, typename MGR>
  template<typename cfo_T, bool cfo_SYNC, bool cfo_EXC>
  inline
  typename basic_manager::vector<T, SYNC, EXC, MGR>::iterator
  basic_manager::vector<T, SYNC, EXC, MGR>
  ::cfo_managed_methods<cfo_T, cfo_SYNC, cfo_EXC>
  ::begin
  ()
  {
    return iterator(this->const_manager());
  }

  template<typename T, bool SYNC, bool EXC, typename MGR>
  template<typename cfo_T, bool cfo_SYNC, bool cfo_EXC>
  inline
  typename basic_manager::vector<T, SYNC, EXC, MGR>::iterator
  basic_manager::vector<T, SYNC, EXC, MGR>
  ::cfo_managed_methods<cfo_T, cfo_SYNC, cfo_EXC>
  ::end
  ()
  {
    return iterator(this->const_manager(), this->size());
  }
} }

#endif
