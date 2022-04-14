//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test02.cpp
//
// basic test for utils.h macros
//

// includes, project

#include "sina.h"
#include "utils.h"


int main(int argc, char *argv[])
{
  sina::utils::logo();

  SINA_COUT << "Find me at function " << SINA_DEBUG_POINT << SINA_ENDL;

  SINA_WATCH(argc);
  SINA_WATCH(SINA_LINE);
  SINA_WARNING("argc is " << argc);
  SINA_CHECK(argc > 1, "argc should be > 1");

  return 0;
}