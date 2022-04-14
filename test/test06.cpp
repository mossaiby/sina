//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test06.cpp
//
// basic test for container.h classes
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "container.h"


int main(int argc, char *argv[])
{
  sina::kernel::dynamic_container<sina::kernel::scalar_t> a(5);

  SINA_ASSERT(a.size() == 5, "invalid size()");
  SINA_ASSERT(a.capacity() == 5, "invalid capacity()");
  
  for (sina::kernel::index_t i = 0; i < a.size(); i++)
  {
    a[i] = i;
  }

  for (sina::kernel::index_t i = 0; i < a.size(); i++)
  {
    SINA_ASSERT(a[i] == i, "invalid value");
  }

  *(a.data()) = 0.00;

  sina::kernel::dynamic_container<sina::kernel::scalar_t> b;

  b.reserve(10);
  b.resize(5);

  SINA_ASSERT(b.size() == 5, "invalid size()");
  SINA_ASSERT(b.capacity() == 10, "invalid capacity()");

  a.swap(b);

  SINA_ASSERT(a.size() == 5, "invalid size()");
  SINA_ASSERT(a.capacity() == 10, "invalid capacity()");

  SINA_ASSERT(b.size() == 5, "invalid size()");
  SINA_ASSERT(b.capacity() == 5, "invalid capacity()");
  
  return 0;
}