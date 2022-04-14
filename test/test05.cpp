//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test05.cpp
//
// basic test for container.h classes
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "container.h"


int main(int argc, char *argv[])
{
  sina::kernel::static_container<sina::kernel::scalar_t, 3> a;

  SINA_ASSERT(a.size() == 3, "invalid size()");
  
  for (sina::kernel::index_t i = 0; i < a.size(); i++)
  {
    a[i] = i;
  }

  for (sina::kernel::index_t i = 0; i < a.size(); i++)
  {
    SINA_ASSERT(a[i] == i, "invalid value");
  }

  *(a.data()) = 0.00;

  return 0;
}