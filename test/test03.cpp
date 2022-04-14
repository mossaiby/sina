//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test03.cpp
//
// basic test for algebra.h class, vector
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "algebra.h"


int main(int argc, char *argv[])
{
  sina::kernel::vector a(5);

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

  sina::kernel::vector b;

  b.reserve(10);
  b.resize(5);

  SINA_ASSERT(b.size() == 5, "invalid size()");
  SINA_ASSERT(b.capacity() == 10, "invalid capacity()");

  a.swap(b);
  b.clear();

  SINA_ASSERT(a.size() == 5, "invalid size()");
  SINA_ASSERT(a.capacity() == 10, "invalid capacity()");

  SINA_ASSERT(b.size() == 5, "invalid size()");
  SINA_ASSERT(b.capacity() == 5, "invalid capacity()");

  return 0;
}