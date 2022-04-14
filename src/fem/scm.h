//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
// scm.h
//
// scm finite element class
//

#pragma once

// includes, project

#include "sina.h"
#include "utils.h"
#include "fem.h"


namespace sina
{
  namespace fem
  {
    template <sina::kernel::index_t __shape_function_order, sina::kernel::index_t __quadrature_order> class scm_elasticity_brick: public sina::fem::element_template<3, (__shape_function_order + 1) * (__shape_function_order + 1) * (__shape_function_order + 1), 3 * (__shape_function_order + 1) * (__shape_function_order + 1) * (__shape_function_order + 1), sina::kernel::geometry_t::brick, sina::kernel::quadrature_type_t::gauss_lobatto, __quadrature_order>
    {
      public:

      scm_elasticity_brick(sina::kernel::index_t index, sina::kernel::node_set<3> &nodes, sina::kernel::properties &nodal_properties, sina::kernel::properties &elemental_properties): sina::fem::element_template<3, (__shape_function_order + 1) * (__shape_function_order + 1) * (__shape_function_order + 1), 3 * (__shape_function_order + 1) * (__shape_function_order + 1) * (__shape_function_order + 1), sina::kernel::geometry_t::brick, sina::kernel::quadrature_type_t::gauss_lobatto, __quadrature_order>::element_template(index, nodes, nodal_properties, elemental_properties)
      {
        // Empty constructor
      }

      virtual ~scm_elasticity_brick() override
      {
        // Empty destructor
      }

      virtual void calculate_derivatives(const sina::kernel::vector &p, sina::kernel::matrix &d) override
      {
        d.resize(4, this->_node_no);

        sina::kernel::vector s;

        d.get_row(0, s);
        sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, __shape_function_order, sina::kernel::shape_function_derivative_t::derivative_0_0_0>(p, s);

        d.get_row(1, s);
        sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, __shape_function_order, sina::kernel::shape_function_derivative_t::derivative_1_0_0>(p, s);

        d.get_row(2, s);
        sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, __shape_function_order, sina::kernel::shape_function_derivative_t::derivative_0_1_0>(p, s);

        d.get_row(3, s);
        sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, __shape_function_order, sina::kernel::shape_function_derivative_t::derivative_0_0_1>(p, s);
      }

      virtual void calculate_lhs_coefficient(const sina::kernel::vector &p, sina::kernel::matrix &lhs_coefficient, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) override
      {

      }

      virtual void calculate_lhs_coefficient(const sina::kernel::vector &p, sina::kernel::scalar_t &lhs_coefficient, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::lumped_mass) override
      {

      }

      virtual void calculate_lhs_component(const sina::kernel::vector &p, const sina::kernel::matrix &d, const sina::kernel::matrix &j, const sina::kernel::matrix &ij, const sina::kernel::scalar_t dj, sina::kernel::matrix &lhs_component, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) override
      {

      }

      virtual void calculate_lhs_component(const sina::kernel::vector &p, const sina::kernel::matrix &d, const sina::kernel::matrix &j, const sina::kernel::matrix &ij, const sina::kernel::scalar_t dj, sina::kernel::vector &lhs_component, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::lumped_mass) override
      {

      }
      
      virtual void get_nodes_dofs(sina::kernel::dynamic_container<sina::kernel::dynamic_container<sina::kernel::dof_type_t> > &nodes_dofs) override
      {

      }
    };
  }
}