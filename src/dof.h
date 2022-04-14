//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// dof.h
//
// dof related classes
//

#pragma once

// includes, project

#include "sina.h"
#include "container.h"


namespace sina
{
  namespace kernel
  {
    enum class dof_type_t
    {
      unassigned = -1,

      displacement_x, displacement_y, displacement_z,
      rotation_x, rotation_y, rotation_z,

      heat,

      max_dof_type
    };

    enum class dof_condition_type_t
    {
      none = 0,

      dirichlet, neumann
    };

    class dof
    {
      public:

      dof()
      {
        // Empty constructor
      }

      dof(const sina::kernel::dof_type_t type, const sina::kernel::dof_condition_type_t condition_type, const sina::kernel::scalar_t condition_value): _type(type), _condition_type(condition_type), _condition_value(condition_value)
      {
        // Empty constructor
      }

      ~dof()
      {
        // Empty destructor
      }

      void set(const sina::kernel::dof_type_t type, const sina::kernel::dof_condition_type_t condition_type, const sina::kernel::scalar_t condition_value)
      {
        _type = type;
        _condition_type = condition_type;
        _condition_value = condition_value;
      }

      void type(const sina::kernel::dof_type_t type)
      {
        _type = type;
      }

      void condition_type(const sina::kernel::dof_condition_type_t condition_type)
      {
        _condition_type = condition_type;
      }

      void condition_value(const sina::kernel::scalar_t condition_value)
      {
        _condition_value = condition_value;
      }

      const sina::kernel::dof_type_t type() const
      {
        return _type;
      }

      const sina::kernel::dof_condition_type_t condition_type() const
      {
        return _condition_type;
      }

      const sina::kernel::scalar_t condition_value() const
      {
        return _condition_value;
      }

      protected:

      sina::kernel::dof_type_t _type;
      sina::kernel::dof_condition_type_t _condition_type;
      sina::kernel::scalar_t _condition_value;
    };

    class dof_set: public dynamic_container<dof>
    {
      public:

      dof_set()
      {
        // Empty constructor
      }

      dof_set(const sina::kernel::index_t size): dynamic_container<dof>(size)
      {
        // Empty constructor
      }

      ~dof_set()
      {
        // Empty destructor
      }
    };
  }
}