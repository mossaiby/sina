//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test13.cpp
//
// basic test for fem.h class
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "fem/fem.h"
#include "fem/geometry.h"


class q4_linear: public sina::fem::element_template<2, 4, 8, sina::kernel::geometry_t::quadrilateral, sina::kernel::quadrature_type_t::gauss_legendre, 2>
{
  public:

  q4_linear(sina::kernel::index_t index, sina::kernel::node_set<2> &nodes, sina::kernel::properties &nodal_properties, sina::kernel::properties &elemental_properties): sina::fem::element_template<2, 4, 8, sina::kernel::geometry_t::quadrilateral, sina::kernel::quadrature_type_t::gauss_legendre, 2>(index, nodes, nodal_properties, elemental_properties)
  {
    sina::kernel::scalar_t E;
    sina::kernel::scalar_t Nu;
    
    _elemental_properties.get(sina::kernel::properties_type_t::elasticity_modulus, _index, E);
    _elemental_properties.get(sina::kernel::properties_type_t::poission_ratio, _index, Nu);

    const sina::kernel::scalar_t D1 = E / ((1.00 + Nu) * (1.00 - 2.00 * Nu)) * (1.00 - Nu);
    const sina::kernel::scalar_t D2 = E / ((1.00 + Nu) * (1.00 - 2.00 * Nu)) * Nu;
    const sina::kernel::scalar_t D3 = E / ((1.00 + Nu) * (1.00 - 2.00 * Nu)) * ((1.00 - 2.00 * Nu) / 2.00);

    _lhs_coefficient_matrix.resize(3, 3);
    _lhs_coefficient_matrix.clear();

    _lhs_coefficient_matrix(0, 0) = D1;
    _lhs_coefficient_matrix(1, 1) = D1;
    _lhs_coefficient_matrix(0, 1) = D2;
    _lhs_coefficient_matrix(1, 0) = D2;
    _lhs_coefficient_matrix(2, 2) = D3;

    _elemental_properties.get(sina::kernel::properties_type_t::density, _index, _lhs_coefficient_scalar);
  }

  virtual ~q4_linear() override
  {
    // Empty destructor
  }

  virtual void calculate_derivatives(const sina::kernel::vector &p, sina::kernel::matrix &d) override
  {
    d.resize(3, 4);

    d(0, 0) = 0.25 * (1.00 - p[0]) * (1.00 - p[1]);
    d(0, 1) = 0.25 * (1.00 + p[0]) * (1.00 - p[1]);
    d(0, 2) = 0.25 * (1.00 + p[0]) * (1.00 + p[1]);
    d(0, 3) = 0.25 * (1.00 - p[0]) * (1.00 + p[1]);

    d(1, 0) = -0.25 * (1.00 - p[1]);
    d(1, 1) = +0.25 * (1.00 - p[1]);
    d(1, 2) = +0.25 * (1.00 + p[1]);
    d(1, 3) = -0.25 * (1.00 + p[1]);

    d(2, 0) = -0.25 * (1.00 - p[0]);
    d(2, 1) = -0.25 * (1.00 + p[0]);
    d(2, 2) = +0.25 * (1.00 + p[0]);
    d(2, 3) = +0.25 * (1.00 - p[0]);
  }

  virtual void calculate_lhs_coefficient(const sina::kernel::vector &p, sina::kernel::matrix &lhs_coefficient, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) override
  {
    lhs_coefficient = _lhs_coefficient_matrix;
  }

  virtual void calculate_lhs_coefficient(const sina::kernel::vector &p, sina::kernel::scalar_t &lhs_coefficient, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::lumped_mass) override
  {
    lhs_coefficient = 1.00;
  }

  virtual void calculate_lhs_component(const sina::kernel::vector &p, const sina::kernel::matrix &d, const sina::kernel::matrix &j, const sina::kernel::matrix &ij, const sina::kernel::scalar_t dj, sina::kernel::matrix &lhs_component, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) override
  {
    if (lhs_type == sina::fem::lhs_type_t::mass)
    {
      lhs_component.resize(2, _dof_no);
      lhs_component.clear();

      for (sina::kernel::index_t i = 0; i < _node_no; i++)
      {
        lhs_component(0, 2 * i + 0) = lhs_component(1, 2 * i + 1) = d(0, i);
      }
    }

    else
    {
      sina::kernel::matrix dxy;

      sina::kernel::m_sn(1, ij, d, dxy);

      lhs_component.resize(3, _dof_no);
      lhs_component.clear();

      for (sina::kernel::index_t i = 0; i < _node_no; i++)
      {
        lhs_component(0, 2 * i + 0) = lhs_component(2, 2 * i + 1) = dxy(0, i);
        lhs_component(1, 2 * i + 1) = lhs_component(2, 2 * i + 0) = dxy(1, i);
      }
    }
  }

  virtual void calculate_lhs_component(const sina::kernel::vector &p, const sina::kernel::matrix &d, const sina::kernel::matrix &j, const sina::kernel::matrix &ij, const sina::kernel::scalar_t dj, sina::kernel::vector &lhs_component, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) override
  {
    lhs_component.resize(_dof_no);
    for (sina::kernel::index_t i = 0; i < _node_no; i++)
    {
      for (sina::kernel::index_t j = 0; j < 2; j++)
      {
        lhs_component[i * 2 + j] = d(0, i);
      }
    }
  }

  virtual void get_nodes_dofs(sina::kernel::dynamic_container<sina::kernel::dynamic_container<sina::kernel::dof_type_t> > &nodes_dofs) override
  {
    nodes_dofs.resize(_node_no);
    
    for (sina::kernel::index_t i = 0; i < _node_no; i++)
    {
      nodes_dofs[i].resize(2);
      for (sina::kernel::index_t j = 0; j < 2; j++)
      {
        nodes_dofs[i][0] = sina::kernel::dof_type_t::displacement_x;
        nodes_dofs[i][1] = sina::kernel::dof_type_t::displacement_y;
      }
    }
  }

  protected:

  sina::kernel::matrix _lhs_coefficient_matrix;
  sina::kernel::scalar_t _lhs_coefficient_scalar;
};

int main(int argc, char *argv[])
{
  sina::kernel::node_set<2> nodes(6);
  sina::fem::element_set elements(2);
  sina::kernel::dof_set dofs;
  sina::kernel::dynamic_container<std::map<sina::kernel::dof_type_t, sina::kernel::index_t> > nodes_dofs;
  
  sina::kernel::constant_properties nodal_properties(6);
  sina::kernel::constant_properties elemental_properties(2);

  sina::kernel::vector body_force(2);
  
  body_force[0] = 0.00;
  body_force[1] = 1.00;

  nodal_properties.add(sina::kernel::properties_type_t::body_force, body_force);

  elemental_properties.add(sina::kernel::properties_type_t::elasticity_modulus, 1000.00);
  elemental_properties.add(sina::kernel::properties_type_t::poission_ratio, 0.30);
  elemental_properties.add(sina::kernel::properties_type_t::density, 1.00);

  nodes[0][0] = 0.00;
  nodes[0][1] = 1.00;

  nodes[1][0] = 1.00;
  nodes[1][1] = 1.00;

  nodes[2][0] = 2.00;
  nodes[2][1] = 1.00;

  nodes[3][0] = 0.00;
  nodes[3][1] = 0.00;

  nodes[4][0] = 1.00;
  nodes[4][1] = 0.00;

  nodes[5][0] = 2.00;
  nodes[5][1] = 0.00;


  for (sina::kernel::index_t i = 0; i < elements.size(); i++)
  {
    elements[i].set(new q4_linear(i, nodes, nodal_properties, elemental_properties));
    elements[i]().prepare_quadrature();
  }

  elements[0]().global_node(0) = 3;
  elements[0]().global_node(1) = 4;
  elements[0]().global_node(2) = 1;
  elements[0]().global_node(3) = 0;

  elements[1]().global_node(0) = 4;
  elements[1]().global_node(1) = 5;
  elements[1]().global_node(2) = 2;
  elements[1]().global_node(3) = 1;

  sina::fem::determine_nodal_dofs<2> determine_nodal_dofs(nodes, elements, dofs, nodes_dofs);
  determine_nodal_dofs.execute();

  for (sina::kernel::index_t i = 0; i < nodes_dofs.size(); i++)
  {
    SINA_ASSERT(nodes_dofs[i][sina::kernel::dof_type_t::displacement_x] == 2 * i + 0, "invalid index");
    SINA_ASSERT(nodes_dofs[i][sina::kernel::dof_type_t::displacement_y] == 2 * i + 1, "invalid index");
  }

  sina::kernel::vector p(2);
  sina::kernel::matrix d;
  sina::kernel::matrix j;
  sina::kernel::matrix ij;
  sina::kernel::scalar_t dj;

  p[0] = 0.00;
  p[1] = 0.00;

  elements[0]().calculate_derivatives(p, d);
  elements[0]().calculate_jacobian(p, d, j, ij, dj);

  SINA_ASSERT(dj == 0.25, "invalid jacobian");

  SINA_WATCH(p);
  SINA_WATCH(j);
  SINA_WATCH(ij);
  SINA_WATCH(dj);

  sina::kernel::matrix lhs;
  sina::kernel::vector rhs;

  elements[0]().calculate_lhs(lhs);
  elements[0]().calculate_rhs(rhs);
  SINA_WATCH(lhs);
  SINA_WATCH(rhs);

  sina::kernel::vector u(nodes.size() * 2);

  for (sina::kernel::index_t i = 0; i < u.size(); i++)
  {
    u[i] = i;
  }

  sina::kernel::vector residual;
  elements[0]().calculate_residual(lhs, rhs, u, residual);

  SINA_WATCH(residual);

  return 0;
}