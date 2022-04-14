//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test09.cpp
//
// basic test for fem.h classes
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
    // Empty constructor
  }

  virtual ~q4_linear() override
  {
    // Empty destructor
  }

  virtual void calculate_derivatives(const sina::kernel::vector &p, sina::kernel::matrix &d) override
  {
    // Empty method just for testing
  }

  virtual void calculate_lhs_coefficient(const sina::kernel::vector &p, sina::kernel::matrix &lhs_coefficient, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) override
  {
    // Empty method just for testing
  }

  virtual void calculate_lhs_coefficient(const sina::kernel::vector &p, sina::kernel::scalar_t &lhs_coefficient, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::lumped_mass) override
  {
    // Empty method just for testing
  }

  virtual void calculate_lhs_component(const sina::kernel::vector &p, const sina::kernel::matrix &d, const sina::kernel::matrix &j, const sina::kernel::matrix &ij, const sina::kernel::scalar_t dj, sina::kernel::matrix &lhs_component, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) override
  {
    // Empty method just for testing
  }

  virtual void calculate_lhs_component(const sina::kernel::vector &p, const sina::kernel::matrix &d, const sina::kernel::matrix &j, const sina::kernel::matrix &ij, const sina::kernel::scalar_t dj, sina::kernel::vector &lhs_component, const sina::fem::lhs_type_t lhs_type = sina::fem::lhs_type_t::stiffness) override
  {
    // Empty method just for testing
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
};

int main(int argc, char *argv[])
{
  sina::kernel::node_set<2> nodes(6);
  sina::kernel::constant_properties nodal_properties(6);
  sina::kernel::constant_properties elemental_properties(1);

  q4_linear element(0, nodes, nodal_properties, elemental_properties);

  for (sina::kernel::index_t i = 0; i < element.node_no(); i++)
  {
    element.global_node(i) = i;
  }

  for (sina::kernel::index_t i = 0; i < element.dof_no(); i++)
  {
    element.global_dof(i) = i;
  }

  SINA_ASSERT(element.dimension() == 2, "invalid dimension()");
  SINA_ASSERT(element.node_no() == 4, "invalid node_no()");
  SINA_ASSERT(element.dof_no() == 8, "invalid dof_no()");

  for (sina::kernel::index_t i = 0; i < element.node_no(); i++)
  {
    SINA_ASSERT(element.global_node(i) == i, "invalid global_node()");
  }

  for (sina::kernel::index_t i = 0; i < element.dof_no(); i++)
  {
    SINA_ASSERT(element.global_dof(i) == i, "invalid global_dof()");
  }

  return 0;
}