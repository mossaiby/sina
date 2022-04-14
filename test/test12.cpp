//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test12.cpp
//
// basic test for properties.h class
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "properties.h"


int main(int argc, char *argv[])
{
  sina::kernel::variable_properties properties(5);

  sina::kernel::dynamic_container<sina::kernel::scalar_t> E(5);
  sina::kernel::dynamic_container<sina::kernel::scalar_t> Nu(5);

  for (sina::kernel::index_t i = 0; i < properties.size(); i++)
  {
    E[i] = i;
    Nu[i] = i;
  }

  properties.add(sina::kernel::properties_type_t::elasticity_modulus, E);
  properties.add(sina::kernel::properties_type_t::poission_ratio, Nu);

  for (sina::kernel::index_t i = 0; i < properties.size(); i++)
  {
    sina::kernel::scalar_t e;
    sina::kernel::scalar_t nu;

    properties.get(sina::kernel::properties_type_t::elasticity_modulus, i, e);
    properties.get(sina::kernel::properties_type_t::poission_ratio, i, nu);
    
    SINA_ASSERT(e == i, "invalid value");
    SINA_ASSERT(nu == i, "invalid value");
  }

  return 0;
}