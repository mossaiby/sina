//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test19.cpp
//
// basic test for geometry
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "fem/geometry.h"


int main(int argc, char *argv[])
{
  sina::kernel::vector p_1(1);
  sina::kernel::vector p_2(2);
  sina::kernel::vector p_3(3);

  sina::kernel::vector s;

  s.reserve(21 * 21 * 21);

  p_1[0] = 1.00;

  sina::kernel::geometry::get<sina::kernel::geometry_t::bar, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_0>(p_1, s); 
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::bar, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_0>(p_1, s); 
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::bar, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_1>(p_1, s); 
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::bar, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_1>(p_1, s); 
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::bar, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_2>(p_1, s); 
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::bar, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_2>(p_1, s); 
  SINA_WATCH(s);

  p_2[0] = 1.00;
  p_2[1] = 1.00;

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_0_0>(p_2, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_1_0>(p_2, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_0_1>(p_2, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_2_0>(p_2, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_1_1>(p_2, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_0_2>(p_2, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_0_0>(p_2, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_1_0>(p_2, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_0_1>(p_2, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_2_0>(p_2, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_1_1>(p_2, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_0_2>(p_2, s);
  SINA_WATCH(s);

  p_3[0] = 1.00;
  p_3[1] = 1.00;
  p_3[2] = 1.00;

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_0_0_0>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_1_0_0>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_0_1_0>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_0_0_1>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_2_0_0>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_0_2_0>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_0_0_2>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_0_1_1>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_1_0_1>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_uniform, 20, sina::kernel::shape_function_derivative_t::derivative_1_1_0>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_0_0_0>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_1_0_0>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_0_1_0>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_0_0_1>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_2_0_0>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_0_2_0>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_0_0_2>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_0_1_1>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_1_0_1>(p_3, s);
  SINA_WATCH(s);

  sina::kernel::geometry::get<sina::kernel::geometry_t::brick, sina::kernel::shape_function_t::lagrange_gll, 20, sina::kernel::shape_function_derivative_t::derivative_1_1_0>(p_3, s);
  SINA_WATCH(s);

  return 0;
}