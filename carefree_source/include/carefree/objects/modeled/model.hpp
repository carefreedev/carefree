/*
 * CareFREE_objects :: MODELED C++ w/Python @<3
 *
 * Copyright (C) 2011-2017 Stefan Zimmermann <user@zimmermann.co>
 *
 * CareFREE_objects is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CareFREE_objects is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CareFREE_objects.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CAREFREE_OBJECTS_MODELED_MODEL_HPP
#define __CAREFREE_OBJECTS_MODELED_MODEL_HPP

#include "../modeled.hpp"

namespace cfo
{

  template<typename T>
  class modeled<T>::model
  {

    template<typename V = void>
    struct data;

    template<>
    struct data<void>
    {
      const std::string name;
    };

    template<typename V>
    struct data : public data<>
    {};

  private:
    std::vector<data<>*> _data;

  private:
    static model& _instance()
    {
      static model instance;
      return instance;
    }

  public:
    class add;

    class remove;

  }; /* class modeled<T>::model */

} /* namespace cfo */

#endif /* __CAREFREE_OBJECTS_MODELED_MODEL_HPP */
