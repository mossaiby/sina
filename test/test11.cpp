//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test11.cpp
//
// basic test for geometry classes
//

// includes, project

#include "sina.h"
#include "fem/geometry.h"


int main(int argc, char *argv[])
{
  SINA_COUT << SINA_FIXED;

  sina::kernel::matrix points;
  sina::kernel::vector weights;

  SINA_COUT << "Gauss-Legendre:" << SINA_ENDL;
  sina::kernel::quadrature::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::quadrature_type_t::gauss_legendre, 4>(points, weights);
  
  for (sina::kernel::index_t i = 0; i < points.size1(); i++)
  {
    SINA_COUT << "[" << weights[i] << "]  ";
    for (sina::kernel::index_t j = 0; j < points.size2(); j++)
    {
      SINA_COUT << (points(i, j) > 0 ? "+" : "") << points(i, j) << (j == points.size2() - 1 ? "" : ", ");
    }
    SINA_COUT << SINA_ENDL;
  }

  SINA_COUT << SINA_ENDL;

  SINA_COUT << "Gauss-Lobatto:" << SINA_ENDL;
  sina::kernel::quadrature::get<sina::kernel::geometry_t::quadrilateral, sina::kernel::quadrature_type_t::gauss_lobatto, 4>(points, weights);

  for (sina::kernel::index_t i = 0; i < points.size1(); i++)
  {
    SINA_COUT << "[" << weights[i] << "]  ";
    for (sina::kernel::index_t j = 0; j < points.size2(); j++)
    {
      SINA_COUT << (points(i, j) > 0 ? "+" : "") << points(i, j) << (j == points.size2() - 1 ? "" : ", ");
    }
    SINA_COUT << SINA_ENDL;
  }

  return 0;
}