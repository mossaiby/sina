//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test20.cpp
//
// basic test for scm.h classes
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "fem/scm.h"


int main(int argc, char *argv[])
{
  sina::kernel::node_set<3> nodes(8);
  sina::fem::element_set elements(1);
  sina::kernel::dof_set dofs;
  sina::kernel::dynamic_container<std::map<sina::kernel::dof_type_t, sina::kernel::index_t> > nodes_dofs;
  
  sina::kernel::constant_properties nodal_properties(8);
  sina::kernel::constant_properties elemental_properties(1);

  sina::kernel::vector body_force(3);
  
  body_force[0] = 0.00;
  body_force[1] = 1.00;
  body_force[2] = 2.00;

  nodal_properties.add(sina::kernel::properties_type_t::body_force, body_force);

  elemental_properties.add(sina::kernel::properties_type_t::elasticity_modulus, 1000.00);
  elemental_properties.add(sina::kernel::properties_type_t::poission_ratio, 0.30);
  elemental_properties.add(sina::kernel::properties_type_t::density, 1.00);

  nodes[0][0] = 0.00;
  nodes[0][1] = 1.00;
  nodes[0][2] = 1.00;

  nodes[1][0] = 0.00;
  nodes[1][1] = 1.00;
  nodes[1][2] = 1.00;

  nodes[2][0] = 0.00;
  nodes[2][1] = 1.00;
  nodes[2][2] = 1.00;

  nodes[3][0] = 0.00;
  nodes[3][1] = 1.00;
  nodes[3][2] = 1.00;

  nodes[4][0] = 0.00;
  nodes[4][1] = 1.00;
  nodes[4][2] = 1.00;

  nodes[5][0] = 0.00;
  nodes[5][1] = 1.00;
  nodes[5][2] = 1.00;

  nodes[6][0] = 0.00;
  nodes[6][1] = 1.00;
  nodes[6][2] = 1.00;

  nodes[7][0] = 0.00;
  nodes[7][1] = 1.00;
  nodes[7][2] = 1.00;

  for (sina::kernel::index_t i = 0; i < elements.size(); i++)
  {
    elements[i].set(new sina::fem::scm_elasticity_brick<2, 2>(i, nodes, nodal_properties, elemental_properties));
    elements[i]().prepare_quadrature();
  }

  // elements[0]().global_node(0) = 0;  // !!!
  // elements[0]().global_node(1) = 1;
  // elements[0]().global_node(2) = 2;
  // elements[0]().global_node(3) = 3;
  // elements[0]().global_node(4) = 4;
  // elements[0]().global_node(5) = 5;
  // elements[0]().global_node(6) = 6;
  // elements[0]().global_node(7) = 7;

  // sina::fem::determine_nodal_dofs<3> determine_nodal_dofs(nodes, elements, dofs, nodes_dofs);
  // determine_nodal_dofs.execute();

  // for (sina::kernel::index_t i = 0; i < nodes_dofs.size(); i++)
  // {
  //   SINA_ASSERT(nodes_dofs[i][sina::kernel::dof_type_t::displacement_x] == 3 * i + 0, "invalid index");
  //   SINA_ASSERT(nodes_dofs[i][sina::kernel::dof_type_t::displacement_y] == 3 * i + 1, "invalid index");
  //   SINA_ASSERT(nodes_dofs[i][sina::kernel::dof_type_t::displacement_z] == 3 * i + 2, "invalid index");
  // }
  
  // sina::kernel::vector p(3);
  // sina::kernel::matrix d;
  // sina::kernel::matrix j;
  // sina::kernel::matrix ij;
  // sina::kernel::scalar_t dj;
  
  // p[0] = 0.00;
  // p[1] = 0.00;
  // p[2] = 0.00;
  
  // elements[0]().calculate_derivatives(p, d);
  // elements[0]().calculate_jacobian(p, d, j, ij, dj);
  
  // // SINA_ASSERT(dj == 0.125, "invalid jacobian");
  
  // SINA_WATCH(p);
  // SINA_WATCH(j);
  // SINA_WATCH(ij);
  // SINA_WATCH(dj);
  
  // sina::kernel::matrix lhs;
  // sina::kernel::vector rhs;
  
  // elements[0]().calculate_lhs(lhs);
  // elements[0]().calculate_rhs(rhs);
  
  // SINA_WATCH(lhs);
  // SINA_WATCH(rhs);
  
  // sina::kernel::vector u(nodes.size() * 2);
  
  // for (sina::kernel::index_t i = 0; i < u.size(); i++)
  // {
  //   u[i] = i;
  // }
  
  // sina::kernel::vector residual;
  // elements[0]().calculate_residual(lhs, rhs, u, residual);
  
  // SINA_WATCH(residual);
  
  return 0;
}