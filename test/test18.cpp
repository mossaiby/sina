//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test18.cpp
//
// basic test for timer class
//

// includes, system

#include <cmath>

// includes, project

#include "sina.h"
#include "utils.h"


int main(int argc, char *argv[])
{
  sina::utils::openmp();

  const sina::kernel::index_t iterations = 100000000;

  sina::kernel::scalar_t s_serial = 0.00;

  SINA_TIC(_loop_serial, "loop (serial)");

  for (sina::kernel::index_t i = 1; i < iterations; i++)
  {
    s_serial += 1.00 / (static_cast<sina::kernel::scalar_t>(i) * static_cast<sina::kernel::scalar_t>(i));
  }  

  SINA_TOC(_loop_serial);


  sina::kernel::scalar_t s_parallel = 0.00;

  SINA_TIC(_loop_parallel, "loop (parallel)");

  #pragma omp parallel for reduction(+: s_parallel)
  for (sina::kernel::index_t i = 1; i < iterations; i++)
  {
    s_parallel += 1.00 / (static_cast<sina::kernel::scalar_t>(i) * static_cast<sina::kernel::scalar_t>(i));
  }  

  SINA_TOC(_loop_parallel);


  SINA_PRECISION(SINA_COUT, 16);

  SINA_COUT << "Serial: " << std::sqrt(6 * s_serial) << SINA_ENDL;
  SINA_COUT << "Parallel: " << std::sqrt(6 * s_parallel) << SINA_ENDL;

  SINA_COUT << "Difference: " << std::abs(std::sqrt(6 * s_serial) - std::sqrt(6 * s_parallel)) << SINA_ENDL;
  
  SINA_PRECISION(SINA_COUT, 3);

  SINA_COUT << "Speed up: " << SINA_TIMER_LAST(_loop_serial) / SINA_TIMER_LAST(_loop_parallel) << SINA_ENDL;

  return 0;
}