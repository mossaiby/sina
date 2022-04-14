//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// properties.h
//
// properties container class
//

#pragma once

// includes, system

#include <map>

// includes, project

#include "sina.h"
#include "algebra.h"
#include "helpers.h"
#include "container.h"


namespace sina
{
  namespace kernel
  {
    enum class properties_type_t
    {
      // nodal properties
      body_force,

      // elemental properties
      elasticity_modulus, poission_ratio, density,
      thermal_conductivity
    };

    class properties
    {
      public:

      properties(sina::kernel::index_t size): _size(size)
      {
        // Empty constructor
      }

      virtual ~properties()
      {
        // Empty destructor
      }

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::index_t &data) const = 0;

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::scalar_t &data) const = 0;

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::vector &data) const = 0;

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::matrix &data) const = 0;

      const sina::kernel::index_t size() const
      {
        return _size;
      }

      protected:

      sina::kernel::index_t _size;
    };
    
    class constant_properties: public properties
    {
      public:

      constant_properties(sina::kernel::index_t size): properties(size)
      {
        // Empty constructor
      }

      virtual ~constant_properties() override
      {
        // Empty destructor
      }

      void add(const properties_type_t id, sina::kernel::index_t data)
      {
        _data_index[id] = data;
      }

      void add(const properties_type_t id, sina::kernel::scalar_t data)
      {
        _data_scalar[id] = data;
      }

      void add(const properties_type_t id, sina::kernel::vector &data)
      {
        _data_vector[id] = data;
      }

      void add(const properties_type_t id, sina::kernel::matrix &data)
      {
        _data_matrix[id] = data;
      }

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::index_t &data) const override
      {
        SINA_ASSERT((i >= 0) && (i < _size), "invalid index");
        data = _data_index.at(id);
      }

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::scalar_t &data) const override
      {
        SINA_ASSERT((i >= 0) && (i < _size), "invalid index");
        data = _data_scalar.at(id);
      }

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::vector &data) const override
      {
        SINA_ASSERT((i >= 0) && (i < _size), "invalid index");
        data = _data_vector.at(id);
      }

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::matrix &data) const override
      {
        SINA_ASSERT((i >= 0) && (i < _size), "invalid index");
        data = _data_matrix.at(id);
      }

      protected:

      std::map<const properties_type_t, sina::kernel::index_t> _data_index;
      std::map<const properties_type_t, sina::kernel::scalar_t> _data_scalar;
      std::map<const properties_type_t, sina::kernel::reference_wrapper<sina::kernel::vector> > _data_vector;
      std::map<const properties_type_t, sina::kernel::reference_wrapper<sina::kernel::matrix> > _data_matrix;
    };

    class variable_properties: public properties
    {
      public:

      variable_properties(sina::kernel::index_t size): properties(size)
      {
        // Empty constructor
      }

      virtual ~variable_properties() override
      {
        // Empty destructor
      }

      void add(const properties_type_t id, sina::kernel::dynamic_container<sina::kernel::index_t> &data)
      {
        _data_index[id] = data;
      }

      void add(const properties_type_t id, sina::kernel::dynamic_container<sina::kernel::scalar_t> &data)
      {
        _data_scalar[id] = data;
      }

      void add(const properties_type_t id, sina::kernel::dynamic_container<sina::kernel::vector> &data)
      {
        _data_vector[id] = data;
      }

      void add(const properties_type_t id, sina::kernel::dynamic_container<sina::kernel::matrix> &data)
      {
        _data_matrix[id] = data;
      }

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::index_t &data) const override
      {
        SINA_ASSERT((i >= 0) && (i < _size), "invalid index");
        data = _data_index.at(id)()[i];
      }

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::scalar_t &data) const override
      {
        SINA_ASSERT((i >= 0) && (i < _size), "invalid index");
        data = _data_scalar.at(id)()[i];
      }

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::vector &data) const override
      {
        SINA_ASSERT((i >= 0) && (i < _size), "invalid index");
        data = _data_vector.at(id)()[i];
      }

      virtual void get(const properties_type_t id, const sina::kernel::index_t i, sina::kernel::matrix &data) const override
      {
        SINA_ASSERT((i >= 0) && (i < _size), "invalid index");
        data = _data_matrix.at(id)()[i];
      }

      protected:

      std::map<const properties_type_t, sina::kernel::reference_wrapper<sina::kernel::dynamic_container<sina::kernel::index_t> > > _data_index;
      std::map<const properties_type_t, sina::kernel::reference_wrapper<sina::kernel::dynamic_container<sina::kernel::scalar_t> > > _data_scalar;
      std::map<const properties_type_t, sina::kernel::reference_wrapper<sina::kernel::dynamic_container<sina::kernel::vector> > > _data_vector;
      std::map<const properties_type_t, sina::kernel::reference_wrapper<sina::kernel::dynamic_container<sina::kernel::matrix> > > _data_matrix;
    };
  }
}