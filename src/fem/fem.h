//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// fem.h
//
// fem related classes
//

#pragma once

// includes, system

#include <map>

// includes, project

#include "sina.h"
#include "algebra.h"
#include "node.h"
#include "dof.h"
#include "properties.h"
#include "helpers.h"
#include "process.h"
#include "utils.h"
#include "fem/geometry.h"


namespace sina
{
  namespace fem
  {
    enum class lhs_type_t
    {
      stiffness, mass, lumped_mass
    };

    class element
    {
      public:

      element()
      {
        // Empty constructor
      }

      virtual ~element()
      {
        // Empty destructor
      }

      virtual void prepare_quadrature() = 0;

      virtual void calculate_derivatives(const sina::kernel::vector &p, sina::kernel::matrix &d) = 0;

      virtual void calculate_jacobian(const sina::kernel::vector &p, const sina::kernel::matrix &d, sina::kernel::matrix &j, sina::kernel::matrix &ij, sina::kernel::scalar_t &dj) = 0;

      virtual void calculate_lhs(sina::kernel::matrix &lhs, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) = 0;

      virtual void calculate_lhs(sina::kernel::vector &lhs, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::lumped_mass) = 0;

      virtual void calculate_rhs(sina::kernel::vector &rhs) = 0;

      virtual void calculate_residual(const sina::kernel::matrix &lhs, const sina::kernel::vector &rhs, const sina::kernel::vector &global_u, sina::kernel::vector &residual) = 0;
      
      virtual void calculate_residual(const sina::kernel::vector &global_u, sina::kernel::vector &residual, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) = 0;

      virtual const sina::kernel::index_t dimension() const = 0;

      virtual const sina::kernel::index_t node_no() const = 0;

      virtual const sina::kernel::index_t dof_no() const = 0;
      
      virtual const sina::kernel::quadrature_type_t quadrature_type() const = 0;

      virtual const sina::kernel::geometry_t geometry() const = 0;

      virtual const sina::kernel::index_t quadrature_order() const = 0;

      virtual sina::kernel::index_t &global_node(const sina::kernel::index_t node) = 0;

      virtual sina::kernel::index_t &global_dof(const sina::kernel::index_t dof) = 0;

      virtual void get_nodes_dofs(sina::kernel::dynamic_container<sina::kernel::dynamic_container<sina::kernel::dof_type_t> > &nodes_dofs) = 0;
    };

    template <sina::kernel::index_t __dimension> class element_base: public sina::fem::element
    {
      public:

      element_base(const sina::kernel::index_t index, const sina::kernel::node_set<__dimension> &nodes, const sina::kernel::properties &nodal_properties, const sina::kernel::properties &elemental_properties): _index(index), _nodes(nodes), _nodal_properties(nodal_properties), _elemental_properties(elemental_properties)
      {
        // Empty constructor
      }

      ~element_base()
      {
        // Empty destructor
      }

      virtual void calculate_jacobian(const sina::kernel::vector &p, const sina::kernel::matrix &d, sina::kernel::matrix &j, sina::kernel::matrix &ij, sina::kernel::scalar_t &dj) override;

      virtual const sina::kernel::index_t dimension() const override
      {
        return _dimension;
      }

      protected:

      static const sina::kernel::index_t _dimension = __dimension;

      const sina::kernel::index_t _index;
      const sina::kernel::properties &_nodal_properties;
      const sina::kernel::properties &_elemental_properties;
      const sina::kernel::node_set<__dimension> &_nodes;
    };

    template <> void element_base<1>::calculate_jacobian(const sina::kernel::vector &p, const sina::kernel::matrix &d, sina::kernel::matrix &j, sina::kernel::matrix &ij, sina::kernel::scalar_t &dj)
    {
      j.resize(1, 1);
      ij.resize(1, 1);

      j.clear();
      for (sina::kernel::index_t i = 0; i < node_no(); i++)
      {
        j(0, 0) += d(1, i) * _nodes[global_node(i)][0];
      }       

      dj = j(0, 0);
      ij(0, 0) = static_cast<sina::kernel::scalar_t>(1) / dj;
    }

    template <> void element_base<2>::calculate_jacobian(const sina::kernel::vector &p, const sina::kernel::matrix &d, sina::kernel::matrix &j, sina::kernel::matrix &ij, sina::kernel::scalar_t &dj)
    {
      j.resize(2, 2);
      ij.resize(2, 2);

      j.clear();
      for (sina::kernel::index_t i = 0; i < node_no(); i++)
      {
        j(0, 0) += d(1, i) * _nodes[global_node(i)][0];
        j(0, 1) += d(1, i) * _nodes[global_node(i)][1];

        j(1, 0) += d(2, i) * _nodes[global_node(i)][0];
        j(1, 1) += d(2, i) * _nodes[global_node(i)][1];          
      }       

      dj = j(0, 0) * j(1, 1) - j(0, 1) * j(1, 0);
      sina::kernel::scalar_t idj = static_cast<sina::kernel::scalar_t>(1) / dj;

      ij(0, 0) = +idj * j(1, 1);
      ij(0, 1) = -idj * j(0, 1);
      ij(1, 0) = -idj * j(1, 0);
      ij(1, 1) = +idj * j(0, 0);
    }

    template <> void element_base<3>::calculate_jacobian(const sina::kernel::vector &p, const sina::kernel::matrix &d, sina::kernel::matrix &j, sina::kernel::matrix &ij, sina::kernel::scalar_t &dj)
    {
      j.resize(3, 3);
      ij.resize(3, 3);

      j.clear();
      for (sina::kernel::index_t i = 0; i < node_no(); i++)
      {
        j(0, 0) += d(1, i) * _nodes[global_node(i)][0];
        j(0, 1) += d(1, i) * _nodes[global_node(i)][1];
        j(0, 2) += d(1, i) * _nodes[global_node(i)][2];

        j(1, 0) += d(2, i) * _nodes[global_node(i)][0];
        j(1, 1) += d(2, i) * _nodes[global_node(i)][1];          
        j(1, 2) += d(2, i) * _nodes[global_node(i)][2];          

        j(2, 0) += d(3, i) * _nodes[global_node(i)][0];
        j(2, 1) += d(3, i) * _nodes[global_node(i)][1];          
        j(2, 2) += d(3, i) * _nodes[global_node(i)][2];          
      }       

      dj = j(0, 0) * j(1, 1) * j(2, 2) + j(0, 1) * j(1, 2) * j(2, 0) + j(0, 2) * j(1, 0) * j(2, 1) -j(0, 0) * j(1, 2) * j(2, 1) -j(0, 1) * j(1, 0) * j(2, 2) - j(0, 2) * j(1, 1) * j(2, 0);
      sina::kernel::scalar_t idj = static_cast<sina::kernel::scalar_t>(1) / dj;

      ij(0, 0) = +idj * (j(1, 1) * j(2, 2) - j(1, 2) * j(2, 1));
      ij(0, 1) = +idj * (j(0, 2) * j(2, 1) - j(0, 1) * j(2, 2));
      ij(0, 2) = +idj * (j(0, 1) * j(1, 2) - j(0, 2) * j(1, 1));

      ij(1, 0) = +idj * (j(1, 2) * j(2, 0) - j(1, 0) * j(2, 2));
      ij(1, 1) = +idj * (j(0, 0) * j(2, 2) - j(0, 2) * j(2, 0));
      ij(1, 2) = +idj * (j(0, 2) * j(1, 0) - j(0, 0) * j(1, 2));

      ij(2, 0) = +idj * (j(1, 0) * j(2, 1) - j(1, 1) * j(2, 0));
      ij(2, 1) = +idj * (j(0, 1) * j(2, 0) - j(0, 0) * j(2, 1));
      ij(2, 2) = +idj * (j(0, 0) * j(1, 1) - j(0, 1) * j(1, 0));
    }

    template <sina::kernel::index_t __dimension, sina::kernel::index_t __node_no, sina::kernel::index_t __dof_no, sina::kernel::geometry_t __geometry, sina::kernel::quadrature_type_t __quadrature_type, sina::kernel::index_t __quadrature_order> class element_template: public sina::fem::element_base<__dimension>
    {
      public:

      element_template(const sina::kernel::index_t index, const sina::kernel::node_set<__dimension> &nodes, const sina::kernel::properties &nodal_properties, const sina::kernel::properties &elemental_properties): element_base<__dimension>(index, nodes, nodal_properties, elemental_properties), _global_nodes(_node_no), _global_dofs(_dof_no)
      {
        // Empty constructor
      }

      virtual ~element_template() override
      {
        // Empty destructor
      }

      virtual void prepare_quadrature() override
      {
        sina::kernel::quadrature::get<_geometry, _quadrature_type, _quadrature_order>(_quadrature_points, _quadrature_weights);
      }

      virtual void calculate_lhs_coefficient(const sina::kernel::vector &p, sina::kernel::matrix &lhs_coefficient, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) = 0;

      virtual void calculate_lhs_coefficient(const sina::kernel::vector &p, sina::kernel::scalar_t &lhs_coefficient, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::lumped_mass) = 0;

      virtual void calculate_lhs_component(const sina::kernel::vector &p, const sina::kernel::matrix &d, const sina::kernel::matrix &j, const sina::kernel::matrix &ij, const sina::kernel::scalar_t dj, sina::kernel::matrix &lhs_component, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) = 0;

      virtual void calculate_lhs_component(const sina::kernel::vector &p, const sina::kernel::matrix &d, const sina::kernel::matrix &j, const sina::kernel::matrix &ij, const sina::kernel::scalar_t dj, sina::kernel::vector &lhs_component, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::lumped_mass) = 0;

      virtual void calculate_lhs(sina::kernel::matrix &lhs, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) override
      {
        lhs.resize(_dof_no, _dof_no);
        lhs.clear();

        for (sina::kernel::index_t i = 0; i < _quadrature_weights.size(); i++)
        {
          _quadrature_points.get_row(i, _scratch_p);
          calculate_lhs_coefficient(_scratch_p, _scratch_lhs_coefficient_matrix, lhs_type);
          this->calculate_derivatives(_scratch_p, _scratch_d);
          this->calculate_jacobian(_scratch_p, _scratch_d, _scratch_j, _scratch_ij, _scratch_dj);
          calculate_lhs_component(_scratch_p, _scratch_d, _scratch_j, _scratch_ij, _scratch_dj, _scratch_lhs_component_matrix, lhs_type);
          sina::kernel::add_amt_n_m(_quadrature_weights[i] * _scratch_dj, _scratch_lhs_component_matrix, _scratch_lhs_coefficient_matrix, lhs);
        }
      }

      virtual void calculate_lhs(sina::kernel::vector &lhs, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::lumped_mass) override
      {
        lhs.resize(_dof_no);
        lhs.clear();

        for (sina::kernel::index_t i = 0; i < _quadrature_weights.size(); i++)
        {
          _quadrature_points.get_row(i, _scratch_p);
          calculate_lhs_coefficient(_scratch_p, _scratch_lhs_coefficient_scalar, lhs_type);
          this->calculate_derivatives(_scratch_p, _scratch_d);
          this->calculate_jacobian(_scratch_p, _scratch_d, _scratch_j, _scratch_ij, _scratch_dj);
          calculate_lhs_component(_scratch_p, _scratch_d, _scratch_j, _scratch_ij, _scratch_dj, _scratch_lhs_component_vector, lhs_type);
          sina::kernel::add_av2(_quadrature_weights[i] * _scratch_lhs_coefficient_scalar * _scratch_dj, _scratch_lhs_component_vector, lhs);
        }
      }

      virtual void calculate_rhs(sina::kernel::vector &rhs) override
      {
        rhs.resize(_dof_no);
        rhs.clear();  

        _scratch_body_force.resize(_dof_no);

        for (sina::kernel::index_t i = 0; i < _quadrature_weights.size(); i++)
        {
          _quadrature_points.get_row(i, _scratch_p);
          this->calculate_derivatives(_scratch_p, _scratch_d);
          this->calculate_jacobian(_scratch_p, _scratch_d, _scratch_j, _scratch_ij, _scratch_dj);
          calculate_lhs_component(_scratch_p, _scratch_d, _scratch_j, _scratch_ij, _scratch_dj, _scratch_lhs_component_matrix, sina::fem::lhs_type_t::mass);
        
          _scratch_body_force.clear();
          for (sina::kernel::index_t j = 0; j < _node_no; j++)
          {
            this->_nodal_properties.get(sina::kernel::properties_type_t::body_force, _global_nodes[j], _scratch_body_force_node);
            sina::kernel::add_av(_scratch_d(0, j), _scratch_body_force_node, _scratch_body_force);
          }

          sina::kernel::add_amt_v(_quadrature_weights[i] * _scratch_dj, _scratch_lhs_component_matrix, _scratch_body_force, rhs);
        }
        // TODO: how to define and integrate traction properly?
      }

      virtual void calculate_residual(const sina::kernel::matrix &lhs, const sina::kernel::vector &rhs, const sina::kernel::vector &global_u, sina::kernel::vector &residual) override
      {
        sina::kernel::vector u(_dof_no);
        residual.resize(_dof_no);

        for (sina::kernel::index_t i = 0; i < _dof_no; i++)
        {
          u[i] = global_u[global_dof(i)];
        }

        sina::kernel::am_v_bw(1.00, -1.00, lhs, u, rhs, residual);
      }

      virtual void calculate_residual(const sina::kernel::vector &global_u, sina::kernel::vector &residual, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) override
      {
        calculate_lhs(_scratch_lhs, lhs_type);
        calculate_rhs(_scratch_rhs);

        calculate_residual(_scratch_lhs, _scratch_rhs, global_u, residual);
      }

      virtual const sina::kernel::index_t node_no() const override
      {
        return _node_no;
      }

      virtual const sina::kernel::index_t dof_no() const override
      {
        return _dof_no;
      }

      virtual const sina::kernel::quadrature_type_t quadrature_type() const override
      {
        return _quadrature_type;
      }

      virtual const sina::kernel::geometry_t geometry() const override
      {
        return _geometry;
      }

      virtual const sina::kernel::index_t quadrature_order() const override
      {
        return _quadrature_order;
      }

      virtual sina::kernel::index_t &global_node(const sina::kernel::index_t i) override
      {
        return _global_nodes[i];
      } 

      virtual sina::kernel::index_t &global_dof(const sina::kernel::index_t i) override
      {
        return _global_dofs[i];
      }

      static const sina::kernel::index_t _node_no = __node_no;
      static const sina::kernel::index_t _dof_no = __dof_no;

      static const sina::kernel::quadrature_type_t _quadrature_type = __quadrature_type;
      static const sina::kernel::geometry_t _geometry = __geometry;
      static const sina::kernel::index_t _quadrature_order = __quadrature_order;

      protected:

      sina::kernel::dynamic_container<sina::kernel::index_t> _global_nodes;
      sina::kernel::dynamic_container<sina::kernel::index_t> _global_dofs;

      sina::kernel::matrix _quadrature_points;
      sina::kernel::vector _quadrature_weights;

      // variables used to do elemental calculations; defined here to avoid memory reallocations

      sina::kernel::vector _scratch_p;
      sina::kernel::matrix _scratch_lhs_component_matrix;
      sina::kernel::matrix _scratch_lhs_coefficient_matrix;
      sina::kernel::vector _scratch_lhs_component_vector;
      sina::kernel::scalar_t _scratch_lhs_coefficient_scalar;
      sina::kernel::matrix _scratch_d;
      sina::kernel::matrix _scratch_j;
      sina::kernel::matrix _scratch_ij;
      sina::kernel::matrix _scratch_lhs;
      sina::kernel::vector _scratch_rhs;
      sina::kernel::vector _scratch_body_force;
      sina::kernel::vector _scratch_body_force_node;
      sina::kernel::scalar_t _scratch_dj;
    };

    class element_set: public sina::kernel::dynamic_container<sina::kernel::reference_wrapper<sina::fem::element> >
    {
      public:
      
      element_set(): sina::kernel::dynamic_container<sina::kernel::reference_wrapper<sina::fem::element> >()
      {
        // Empty constructor
      }

      element_set(const sina::kernel::index_t size): sina::kernel::dynamic_container<sina::kernel::reference_wrapper<sina::fem::element> >(size)
      {
        // Empty constructor
      }

      ~element_set()
      {
        for (sina::kernel::index_t i = 0; i < _size; i++)
        {
          delete &_data[i]();
        }
      }
    };

    template <sina::kernel::index_t __dimension> class determine_nodal_dofs: public sina::kernel::process
    {
      public:

      determine_nodal_dofs(const sina::kernel::node_set<__dimension> &nodes, const sina::fem::element_set &elements, sina::kernel::dof_set &dofs, sina::kernel::dynamic_container<std::map<sina::kernel::dof_type_t, sina::kernel::index_t> > &nodes_dofs): _nodes(nodes), _elements(elements), _dofs(dofs), _nodes_dofs(nodes_dofs)
      {
        // Empty constructor
      }

      virtual ~determine_nodal_dofs() override
      {
        // Empty destructor
      }

      virtual void execute() override
      {
        sina::kernel::dynamic_container<sina::kernel::dynamic_container<sina::kernel::dof_type_t> > element_nodes_dofs;
        _nodes_dofs.resize(_nodes.size());

        for (sina::kernel::index_t i = 0; i < _elements.size(); i++)
        {
          _elements[i]().get_nodes_dofs(element_nodes_dofs);
          for (sina::kernel::index_t j = 0; j < element_nodes_dofs.size(); j++)
          {
            for (sina::kernel::index_t k = 0; k < element_nodes_dofs[j].size(); k++)
            {
              _nodes_dofs[_elements[i]().global_node(j)][element_nodes_dofs[j][k]] = -1;
            }
          }
        }

        sina::kernel::index_t dof_no = 0;
        for (sina::kernel::index_t i = 0; i < _nodes_dofs.size(); i++)
        {
          dof_no += _nodes_dofs[i].size();
        }

        _dofs.resize(dof_no);

        sina::kernel::index_t current_dof = 0;
        for (sina::kernel::index_t i = 0; i < _nodes_dofs.size(); i++)
        {
          for (std::map<sina::kernel::dof_type_t, sina::kernel::index_t>::iterator j = _nodes_dofs[i].begin(); j != _nodes_dofs[i].end(); j++)
          {
            _dofs[current_dof].type(j->first);
            j->second = current_dof;
            current_dof++;
          }
        }

        for (sina::kernel::index_t i = 0; i < _elements.size(); i++)
        {
          sina::kernel::index_t element_dof = 0;
          _elements[i]().get_nodes_dofs(element_nodes_dofs);
          for (sina::kernel::index_t j = 0; j < element_nodes_dofs.size(); j++)
          {
            for (sina::kernel::index_t k = 0; k < element_nodes_dofs[j].size(); k++)
            {
              _elements[i]().global_dof(element_dof) = _nodes_dofs[_elements[i]().global_node(j)].at(element_nodes_dofs[j][k]);
              element_dof++;
            }
          }
        }
      }

      protected:

      const sina::kernel::node_set<__dimension> &_nodes;
      const sina::fem::element_set &_elements;
      sina::kernel::dof_set &_dofs;
      sina::kernel::dynamic_container<std::map<sina::kernel::dof_type_t, sina::kernel::index_t> > &_nodes_dofs;
    };
  }
}