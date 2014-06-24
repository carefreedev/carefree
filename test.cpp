#include <carefree-objects.hpp>

#include <carefree-types.hpp>

class base
{
public:
  const std::string name;

  inline base(const std::string &name = "base") :
    name(name)
  {}

  virtual void _()
  {}

  cfo_MANAGED_BASIC_CONST_METHODS
  (base,

   public:

   inline const std::string& name() const
   {
     return (*this)->name;
   })

  cfo_MANAGED_BASIC_METHODS(base, )
};

class object : public base
{
public:
  inline object(const std::string &name = "object") :
    base(name)
  {
    if (name == "error")
      throw std::invalid_argument(name);
  }

  cfo_MANAGED_CONST_METHODS(object, base, )
  cfo_MANAGED_METHODS(object, base, )
};

typedef cfo::managed<base, false> Base;
typedef cfo::managed<object, false> Object;

int main(int, char**)
{
  cfo::character::_test();

  cfo::ip::v6::address::_test();

  {
    Base b;
    assert(!b.error_());

    assert(b.name() == "base");
    assert(b.is(b));
    assert(b.is_<Base>());
    assert(b.is_managed<base>());
    assert(!b.is_<Object>());
    assert(!b.is_managed<object>());
  }

  {
    Base b("name");
    assert(!b.error_());

    assert(b.name() == "name");
    assert(b.is(b));
    assert(b.is_<Base>());
    assert(b.is_managed<base>());
    assert(!b.is_<Object>());
    assert(!b.is_managed<object>());
  }

  {
    Object obj("bla");
    assert(!obj.error_());

    assert(obj.name() == "bla");
    assert(obj.is(obj));
    assert(obj.is_<Object>());
    assert(obj.is_managed<object>());
    assert(obj.is_<Base>());
    assert(obj.is_managed<base>());

    Base b = obj;
    assert(!b.error_());

    assert(obj.is(b));

    assert(b.name() == "bla");
    assert(b.is(b));
    assert(b.is(obj));
    assert(b.is_<Base>());
    assert(b.is_managed<base>());
    assert(b.is_<Object>());
    assert(b.is_managed<object>());
  }

  {
    Object obj("error");
    assert(obj.error_());
    assert(obj.error_().what() == "error");
    assert(obj.error_().is_<std::invalid_argument>());
    assert(obj.error_().type() == typeid(std::invalid_argument));
  }

  {
    bool thrown = false;
    try
      {
        Object::except obj("error");
      }
    catch (const std::invalid_argument &e)
      {
        thrown = true;
        assert(e.what() == std::string("error"));
      }
    assert(thrown);
  }

  return 0;
}
