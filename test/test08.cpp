//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test08.cpp
//
// basic test for dof.h classes
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "dof.h"


int main(int argc, char *argv[])
{
  sina::kernel::dof dof(sina::kernel::dof_type_t::displacement_x, sina::kernel::dof_condition_type_t::dirichlet, 0.00);
  sina::kernel::dof_set dof_set(3);

  dof_set[0].type(sina::kernel::dof_type_t::displacement_x);
  dof_set[1].type(sina::kernel::dof_type_t::displacement_y);
  dof_set[2].type(sina::kernel::dof_type_t::displacement_z);

  dof_set[0].condition_type(sina::kernel::dof_condition_type_t::neumann);
  dof_set[1].condition_type(sina::kernel::dof_condition_type_t::neumann);
  dof_set[2].condition_type(sina::kernel::dof_condition_type_t::neumann);

  dof_set[0].condition_value(0.00);
  dof_set[1].condition_value(1.00);
  dof_set[2].condition_value(2.00);

  SINA_ASSERT(dof_set.size() == 3, "invalid size()");

  SINA_ASSERT(dof_set[0].type() == sina::kernel::dof_type_t::displacement_x, "invalid type()");
  SINA_ASSERT(dof_set[1].type() == sina::kernel::dof_type_t::displacement_y, "invalid type()");
  SINA_ASSERT(dof_set[2].type() == sina::kernel::dof_type_t::displacement_z, "invalid type()");

  SINA_ASSERT(dof_set[0].condition_type() == sina::kernel::dof_condition_type_t::neumann, "invalid condition_type()");
  SINA_ASSERT(dof_set[1].condition_type() == sina::kernel::dof_condition_type_t::neumann, "invalid condition_type()");
  SINA_ASSERT(dof_set[2].condition_type() == sina::kernel::dof_condition_type_t::neumann, "invalid condition_type()");

  SINA_ASSERT(dof_set[0].condition_value() == 0.00, "invalid condition_value()");
  SINA_ASSERT(dof_set[1].condition_value() == 1.00, "invalid condition_value()");
  SINA_ASSERT(dof_set[2].condition_value() == 2.00, "invalid condition_value()");

  return 0;
}