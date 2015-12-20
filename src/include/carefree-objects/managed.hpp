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

/* the object manager template
 *
 * wraps any normal c++ class
 * to get managed object ref counting and synchronized object member access
 */
#ifndef __CFO_MANAGED_HPP
#define __CFO_MANAGED_HPP

#include "./common.hpp"

#include "./error.hpp"

#include "./basic_manager.hpp"
#include "./methods.hpp"

namespace cfo { namespace intern
{
  template
  <typename T, bool EXC, typename INIT_T, bool INIT_NULL, typename COPY>
  class managed<T, true, EXC, INIT_T, INIT_NULL, COPY> :
    public basic_manager
  {
    friend class cfo::intern::const_accessor<T, EXC, INIT_T, COPY>;
    friend class cfo::intern::accessor<T, EXC, INIT_T, COPY>;

  private:
    T *obj;

  protected:
    inline managed(T *obj) :
      basic_manager(),
      obj(obj)
    {}

  public:
    typedef T unmanaged_type;
    typedef T* unmanaged_ptr_type;
    typedef const T* unmanaged_const_ptr_type;

    typedef managed<T, true, EXC, INIT_T, false, COPY> managed_base;

    typedef cfo::intern::forward<T, true, false, INIT_T, false, COPY>
      forward;

    typedef T cfo_unmanaged_type;
    typedef T* cfo_unmanaged_ptr_type;
    typedef const T* cfo_unmanaged_const_ptr_type;

    typedef INIT_T cfo_unmanaged_init_type;
    typedef INIT_T* cfo_unmanaged_init_ptr_type;
    typedef const INIT_T* cfo_unmanaged_const_init_ptr_type;

    typedef managed<T, true, false, INIT_T, false, COPY> cfo_manager_type;
    typedef cfo::intern::forward<T, true, false, INIT_T, false, COPY>
      cfo_forward_manager_type;

    typedef T managed_type;
    typedef T* managed_ptr_type;
    typedef const T* managed_const_ptr_type;

    typedef managed<T, true, false, INIT_T, false, COPY> manager_type;
    typedef cfo::intern::forward<T, true, false, INIT_T, false, COPY>
      forward_manager_type;

    typedef managed<T, true, true, INIT_T, false, COPY> except;

    typedef managed<T, true, false, INIT_T, true, COPY> null;

    typedef
    typename T::template cfo_managed_const_methods
    <const T, true, EXC, INIT_T, COPY>
    const_accessor;

    typedef typename T::template cfo_managed_methods
    <T, true, EXC, INIT_T, COPY>
    accessor;

    typedef managed
      <basic_manager::vector<T, true, EXC, INIT_T, COPY>, true, EXC>
      vector;

    template<typename KEY, typename... EXTRA>
      using map = managed
      <basic_manager::map
       <KEY, T, true, EXC, managed<T, true, EXC, INIT_T>, EXTRA...>,
       true>;

  private:
    cfo::intern::error _error;

  public:
    inline managed() try :
      basic_manager(),
      obj(INIT_NULL ? NULL : static_cast<T*>(new INIT_T))
    {}
    catch (const std::exception &e)
    {
      if (EXC)
        throw;

      this->_error.reset(e);
    }

    template<typename... A>
    inline managed(A... args) try :
      basic_manager(),
      obj(static_cast<T*>(new INIT_T(args...)))
    {}
    catch (const std::exception &e)
    {
      if (EXC)
        throw;

      this->_error.reset(e);
    }

    // inline managed(const managed<T, true, true> &/*nullmanager*/) :
    //   basic_manager(),
    //   obj(NULL)
    // {}

    inline managed
    (const managed<T, true, EXC, INIT_T, false, COPY> &manager
     ) :
      basic_manager(manager),
      obj(this->cnl ? manager.obj : NULL)
    {}

    template
    <typename T_, bool EXC_, typename INIT_T_, bool INIT_NULL_,
     typename COPY_
     >
    inline managed
    (const managed<T_, true, EXC_, INIT_T_, INIT_NULL_, COPY_> &other
     ) :
      basic_manager(other),
      obj(this->cnl ? static_cast<T*>(other.unmanaged()) : NULL)
    {}

    virtual ~managed()
    {
      this->basic_manager::destroy();
      if (!this->cnl)
        delete this->obj;
    }

  public:
    inline const cfo::intern::error& error_() const
    {
      return this->_error;
    }

  public:
    template<typename ...ARGS>
    inline managed<T, true, EXC, INIT_T, false, COPY> copy(ARGS &...args)
      const;

  public:
    inline const_accessor caccess() const
    {
      return const_accessor(*this);
    }

    inline accessor access()
    {
      return accessor(*this);
    }

  public:
    inline T* unmanaged() const
    {
      return this->obj;
    }

  public:
    inline operator bool() const
    {
      return this->obj;
    }

    inline bool operator!() const
    {
      return !this->obj;
    }
  };

  template
  <typename T, bool EXC, typename INIT_T, bool INIT_NULL, typename COPY>
  template<typename ...ARGS>
  inline
  managed<T, true, EXC, INIT_T, false, COPY>
  managed<T, true, EXC, INIT_T, INIT_NULL, COPY>::copy(ARGS &...args)
    const
  {
    return managed<T, true, EXC, INIT_T, false, COPY>
      (this->obj ? COPY()(*this->obj, args...) : NULL);
  }

  template
  <typename T, bool EXC, typename INIT_T, bool INIT_NULL, typename COPY>
  class managed<T, false, EXC, INIT_T, INIT_NULL, COPY> :
    public T::template cfo_managed_methods<T, false, EXC, INIT_T, COPY>
  {
    friend T;

    template
    <typename T_, bool SYNC, bool EXC_, typename INIT_T_, bool INIT_NULL_,
     typename COPY_
     >
    friend class managed;

    typedef typename T::template cfo_managed_methods
    <T, false, EXC, INIT_T, COPY>
    basic_type;

  protected:
    inline managed(T *obj) :
      basic_type(obj)
    {}

  public:
    typedef managed<T, false, EXC, INIT_T, false, COPY> managed_base;

    typedef cfo::intern::forward<T, false, false, INIT_T, false, COPY>
      forward;

    typedef T unmanaged_type;
    typedef T* unmanaged_ptr_type;
    typedef const T* unmanaged_const_ptr_type;

    typedef T cfo_unmanaged_type;
    typedef T* cfo_unmanaged_ptr_type;
    typedef const T* cfo_unmanaged_const_ptr_type;

    typedef INIT_T cfo_unmanaged_init_type;
    typedef INIT_T* cfo_unmanaged_init_ptr_type;
    typedef const INIT_T* cfo_unmanaged_const_init_ptr_type;

    typedef managed<T, false, false, INIT_T, false, COPY> cfo_manager_type;
    typedef cfo::intern::forward<T, false, false, INIT_T, false, COPY>
      cfo_forward_manager_type;

    typedef T managed_type;
    typedef T* managed_ptr_type;
    typedef const T* managed_const_ptr_type;

    typedef managed<T, false, false, INIT_T, false, COPY> manager_type;
    typedef cfo::intern::forward<T, false, false, INIT_T, false, COPY>
      forward_manager_type;

    typedef managed<T, false, true, INIT_T, false, COPY> except;

    // typedef managed<T, false, false, INIT_T, true, COPY> null;
    class null;

    template<typename INIT_T_>
    using cfo_new_init_type = managed
      <T, false, false, INIT_T_, false, COPY>;

    template<typename INIT_T_>
    class init;

    typedef managed
    <basic_manager::vector
     <T, false, EXC, INIT_T, COPY,
      managed<T, false, EXC, INIT_T, false, COPY>
      >,
     false, EXC
     >
    vector;

    template<typename I, typename... E>
    using map = managed
      <basic_manager::map
       <I, T, false, EXC, managed<T, false, EXC, INIT_T, false>, E...>,
       false>;

  private:
    cfo::intern::error _error;

  public:
    inline managed() :
      // basic_type(INIT_NULL ? NULL : static_cast<T*>(new INIT_T))
      basic_type(NULL)
    {
      if (INIT_NULL)
        return;

      if (EXC)
        {
          this->std::shared_ptr<T>::reset(static_cast<T*>(new INIT_T));
          return;
        }
      try
        {
          this->std::shared_ptr<T>::reset(static_cast<T*>(new INIT_T));
        }
      catch (const std::exception &e)
        {
          this->_error.reset(e);
        }
    }

    template<typename... A>
    inline managed(A... args) :
      // basic_type(static_cast<T*>(new INIT_T(args...)))
      basic_type(NULL)
    {
      if (EXC)
        {
          this->std::shared_ptr<T>::reset
            (static_cast<T*>(new INIT_T(args...)));

          return;
        }
      try
        {
          this->std::shared_ptr<T>::reset
            (static_cast<T*>(new INIT_T(args...)));
        }
      catch (const std::exception &e)
        {
          this->_error.reset(e);
        }
    }

    // inline managed(const managed<T, false, true> &/*nullmanager*/) :
    //   basic_type(NULL)
    // {}

    inline managed
    (const managed<T, false, EXC, INIT_T, false, COPY> &manager
     ) :
      basic_type(manager)
    {}

    template
    <typename T_, bool EXC_, typename INIT_T_, bool INIT_NULL_,
     typename COPY_
     >
    inline managed
    (const managed<T_, false, EXC_, INIT_T_, INIT_NULL_, COPY_> &other
     ) :
      basic_type
      (std::static_pointer_cast<T>
       (static_cast<const std::shared_ptr<T_>&>(other)))
    {}

    inline managed(const null&);

  public:
    inline const cfo::intern::error& error_() const
    {
      return this->_error;
    }

  public:
    inline bool is
    (const managed<T, false, EXC, INIT_T, INIT_NULL, COPY> &other)
      const
    {
      if (!this->unmanaged())
        return !other.unmanaged();

      try
        {
          return this->unmanaged()
            == &dynamic_cast<const T&>(*other.unmanaged());
        }
      catch (const std::bad_cast &)
        {
          return false;
        }
    }

    template<typename MGR>
    inline bool is_() const
    {
      if (!this->unmanaged())
        {
          return false;
        }
      try
        {
          return bool(&dynamic_cast<const typename MGR::unmanaged_type&>
                      (*this->unmanaged()));
        }
      catch (const std::bad_cast &)
        {
          return false;
        }
    }

    template<typename T_>
    inline bool is_managed() const
    {
      if (!this->unmanaged())
        {
          return false;
        }
      try
        {
          return bool(&dynamic_cast<const T_&>(*this->unmanaged()));
        }
      catch (const std::bad_cast &)
        {
          return false;
        }
    }

  public:
    inline std::size_t refcount() const
    {
      return this->use_count();
    }

  public:
    inline bool operator==
    (const managed<T, false, EXC, INIT_T, INIT_NULL, COPY> &other)
      const
    {
      assert(this->std::shared_ptr<T>::get()
             && other.std::shared_ptr<T>::get());

      return this->std::shared_ptr<T>::get()
        == other.std::shared_ptr<T>::get()

        || this->std::shared_ptr<T>::operator*()
        == other.std::shared_ptr<T>::operator*();
    }

    inline bool operator!=
    (const managed<T, false, EXC, INIT_T, INIT_NULL, COPY> &other)
      const
    {
      assert(this->std::shared_ptr<T>::get()
             && other.std::shared_ptr<T>::get());

      return this->std::shared_ptr<T>::get()
        != other.std::shared_ptr<T>::get()

        && this->std::shared_ptr<T>::operator*()
        != other.std::shared_ptr<T>::operator*();
    }

    template
    <typename T_, bool EXC_, typename INIT_T_, bool INIT_NULL_,
     typename COPY_
     >
    inline bool operator==
    (const managed<T_, false, EXC_, INIT_T_, INIT_NULL_, COPY_> &other)
      const
    {
      return this->operator==
        (managed<T, false, EXC, INIT_T, INIT_NULL, COPY>(other));
    }

    template
    <typename T_, bool EXC_, typename INIT_T_, bool INIT_NULL_,
     typename COPY_
     >
    inline bool operator!=
    (const managed<T_, false, EXC_, INIT_T_, INIT_NULL_, COPY_> &other)
      const
    {
      return this->operator!=
        (managed<T, false, EXC, INIT_T, INIT_NULL, COPY>(other));
    }

  public:
    inline T* operator->() const
    {
      assert(this->get());
      return this->get();
    }

  public:
    template<typename ...ARGS>
    inline managed<T, false, EXC, INIT_T, false, COPY> copy(ARGS &...args)
      const;

  public:
    inline except except_() const
    {
      return except(*this);
    }

    inline manager_type noexcept_() const
    {
      return manager_type(*this);
    }

  public:
    inline T* unmanaged() const
    {
      assert(this->get());
      return this->get();
    }
  };

  template
  <typename T, bool EXC, typename INIT_T, bool INIT_NULL, typename COPY>
  template<typename INIT_T_>
  class managed<T, false, EXC, INIT_T, INIT_NULL, COPY>::init :
    public managed<T, false, EXC, INIT_T, false, COPY>
  {
    using cfo_manager_type::cfo_manager_type;

  public:
    typedef init<INIT_T_> cfo_init_manager_type;

  protected:
    inline init(INIT_T_ *ptr) :
      cfo_manager_type(static_cast<T*>(ptr))
    {}

  public:
    inline init() :
      cfo_manager_type(static_cast<T*>(new INIT_T_))
    {}

    template<typename... ARGS>
    inline init(const ARGS &...args) :
      cfo_manager_type(static_cast<T*>(new INIT_T_(args...)))
    {}
  };

  template
  <typename T, bool EXC, typename INIT_T, bool INIT_NULL, typename COPY>
  class managed<T, false, EXC, INIT_T, INIT_NULL, COPY>::null :
    public managed<T, false, EXC, INIT_T, false, COPY>
  {
  public:
    inline null() :
      cfo_manager_type(static_cast<T*>(NULL))
    {}
  };

  template
  <typename T, bool EXC, typename INIT_T, bool INIT_NULL, typename COPY>
  inline managed<T, false, EXC, INIT_T, INIT_NULL, COPY>::managed
  (const null&
   ) :
    managed(static_cast<T*>(NULL))
  {}

  template
  <typename T, bool EXC, typename INIT_T, bool INIT_NULL, typename COPY>
  template<typename ...ARGS>
  inline
  managed<T, false, EXC, INIT_T, false, COPY>
  managed<T, false, EXC, INIT_T, INIT_NULL, COPY>::copy(ARGS &...args)
    const
  {
    return managed<T, false, EXC, INIT_T, false, COPY>
      (this->get() ? COPY()(*this->get(), args...) : NULL);
  }
} }

#endif
