/* carefree-objects
 *
 * MODELED C++ w/Python @<3
 *
 * Copyright (C) 2011-2017 Stefan Zimmermann <user@zimmermann.co>
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

#ifndef __CFO_MODELED_HPP
#define __CFO_MODELED_HPP

#include <carefree-objects/common.hpp>

#include <carefree-objects/managed.hpp>

namespace cfo
{
  template<class T, class ACS>
  class properties;

  template<class T, class V, class ACS>
  class property;

  template<class T, class ACS>
  class const_methods;

  template<class T, class ACS>
  class methods;

  template<class T>
  class model;

  template<class T>
  class modeled :
    public cfo::intern::managed<T, true, true, T, false, cfo::copy<T> >
  {
    template<class OTHER_T>
    friend class modeled;

  private:
    typedef cfo::intern::managed<T, true, true, T, false, cfo::copy<T> >
      _managed;

  public:
    typedef T unmanaged_type;

  public:
    typedef cfo::model<T> model_type;

    static model_type model;

  public:
    class const_accessor :
      public cfo::intern::const_methods<T, true, true, T, cfo::copy<T> >,
      // public cfo::properties<T, const_accessor>,
      public cfo::const_methods<T, const_accessor>
    {
      template<class U, class ACS>
      friend class cfo::const_methods;

    private:
      typedef cfo::intern::const_methods<T, true, true, T, cfo::copy<T> >
        _super;

      using _super::_super;

    public:
      const_accessor(const_accessor &&acs) :
        _super(static_cast<_super&&>(acs))
      {}

    private:
      const_accessor(const const_accessor &);

    public:
      inline const T* operator->() const
      {
        return this->_super::operator->();
      }

    private:
      template<class U>
      static inline const U* ptr
        (const cfo::const_methods<U, const_accessor> &acs)
      {
        return static_cast<const U*>
          (static_cast<const const_accessor*>(&acs)->operator->());
      }

    }; /* modeled<T>::const_accessor */

  public:
    class accessor :
      public cfo::intern::methods
        <T, true, true, T, cfo::copy<T>, const_accessor
         >,
      // public cfo::properties<T, accessor>,
      public cfo::methods<T, accessor>
    {
      template<class U, class ACS>
      friend class cfo::methods;

    private:
      typedef cfo::intern::methods
        <T, true, true, T, cfo::copy<T>, const_accessor>
        _super;

      using _super::_super;

    public:
      accessor(accessor &&acs) :
        _super(static_cast<_super&&>(acs))
      {}

    private:
      accessor(const accessor &);

    public:
      inline T* operator->()
      {
        return this->_super::operator->();
      }

    private:
      template<class U>
      static inline U* ptr(cfo::methods<U, accessor> &acs)
      {
        return static_cast<U*>
          (static_cast<accessor*>(&acs)->operator->());
      }

    }; /* modeled<T>::accessor */

  public:
    class frozen :
      public cfo::intern::managed<T, false, true, T, false, cfo::copy<T> >
    {
    private:
      typedef cfo::intern::managed<T, false, true, T, false, cfo::copy<T> >
        _managed;

    }; /* modeled<T>::frozen */

  private:
    inline modeled(T* unmanaged_ptr) :
      _managed(unmanaged_ptr)
    {}

  public:
    inline modeled(const modeled<T> &manager) :
      _managed(static_cast<const _managed&>(manager))
    {}

    template<class OTHER_T>
    inline modeled(const modeled<OTHER_T> &other_manager) :
      _managed(static_cast<const class modeled<OTHER_T>::_managed&>
                 (other_manager))
    {}

  public:
    inline modeled(const _managed &manager) :
      _managed(manager)
    {}

    template<typename T_, bool EXC_, typename INIT_T_, bool INIT_NULL_,
             typename COPY_
             >
    inline modeled(const cfo::intern::managed
                     <T_, true, EXC_, INIT_T_, INIT_NULL_, COPY_>
                     &other_manager
                   ) :
      _managed(other_manager)
    {}

  public:
    virtual ~modeled()
    {}

  public:
    template<class U>
    class bad_create_cast : public std::bad_cast
    {
    public:
      std::unique_ptr<U> ptr;

    public:
      inline bad_create_cast(const std::bad_cast &e, U *ptr) :
        std::bad_cast(e),
        ptr(ptr)
      {}

    }; /* modeled<T>::bad_create_cast<U> */

    template<class U>
    class bad_const_create_cast : public std::bad_cast
    {
    public:
      std::unique_ptr<const U> ptr;

    public:
      inline bad_const_create_cast(const std::bad_cast &e,
                                   const U *ptr) :
        std::bad_cast(e),
        ptr(ptr)
      {}

    }; /* modeled<T>::bad_const_create_cast<U> */

  public:
    template<class U = T, typename... ARGV>
    static inline modeled<T> create(const ARGV &...args)
    {
      U *ptr = new U(args...);
      // ensure general type compatibility at compile time in DEBUG mode
      assert(static_cast<T*>(ptr));
      try
        {
          return modeled<T>(dynamic_cast<T*>(ptr));
        }
      catch(const std::bad_cast &e)
        {
          throw modeled<T>::bad_create_cast<U>(e, ptr);
        }
      // return modeled<T>(dynamic_cast<T*>(new U(args...)));
    }

  public:
    class const_type :
      public std::shared_ptr<const T>,
      public cfo::const_methods<T, const_type>
    {
    public:
      typedef T unmanaged_type;

    private:
      inline const_type(const T* unmanaged_ptr) :
        std::shared_ptr<const T>(unmanaged_ptr)
      {}

      template<class U = T, typename... ARGV>
      static inline const_type create(const ARGV &...args)
      {
        const U *ptr = new U(args...);
        // ensure general type compatibility at compile time in DEBUG mode
        assert(static_cast<const T*>(ptr));
        try
          {
            return const_type(dynamic_cast<const T*>(ptr));
          }
        catch(const std::bad_cast &e)
          {
            throw cfo::modeled<T>::bad_const_create_cast<U>(e, ptr);
          }
      }

    private:
      template<class U>
      static inline const U* ptr
        (const cfo::const_methods<U, const_type> &acs)
      {
        return static_cast<const U*>
          (static_cast<const const_type*>(&acs)->operator->());
      }
    };

    template<class U = T, typename... ARGV>
    static inline const_type const_create(const ARGV &...args)
    {
      return const_type::template create<U>(args...);
    }

  public:
    inline const_accessor const_access() const
    {
      return const_accessor(*this);
    }

    inline accessor access()
    {
      return accessor(*this);
    }

  }; /* modeled<T> */

  template<class T>
  class model
  {};

  template<class T, class ACS>
  class properties
  {};

  template<class T, class V, class ACS>
  class property
  {
  protected:
    inline const T* operator->() const
    {
      return ACS::ptr(*this);
    }

    inline T* operator->()
    {
      return ACS::ptr(*this);
    }

  public:
    inline operator V() const
    {
      return this->operator()();
    }

  }; /* property<T, V, ACS> */

  template<class T, class ACS>
  class const_methods
  {
  public:
    inline const T* operator->() const
    {
      return ACS::ptr(*this);
    }

  }; /* const_methods<T, ACS> */

  template<class T, class ACS>
  class methods
  {
  public:
    inline T* operator->()
    {
      return ACS::ptr(*this);
    }

  }; /* methods<T, ACS> */

} /* cfo */

#endif /* __CFO_MODELED_HPP */
