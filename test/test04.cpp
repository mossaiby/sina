//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test04.cpp
//
// basic test for algebra.h class, matrix
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "algebra.h"


int main(int argc, char *argv[])
{
  sina::kernel::matrix a(5, 5);

  SINA_ASSERT(a.size1() == 5, "invalid size1()");
  SINA_ASSERT(a.size2() == 5, "invalid size2()");
  SINA_ASSERT(a.capacity() == 5 * 5, "invalid capacity()");

  for (sina::kernel::index_t i = 0; i < a.size1(); i++)
  {
    for (sina::kernel::index_t j = 0; j < a.size2(); j++)
    {
      a(i, j) = i * j;
    }
  }

  for (sina::kernel::index_t i = 0; i < a.size1(); i++)
  {
    for (sina::kernel::index_t j = 0; j < a.size2(); j++)
    {
      SINA_ASSERT(a(i, j) == i * j, "invalid value");
    }
  }

  *(a.data()) = 0.00;

  sina::kernel::matrix b;

  b.reserve(10 * 10);
  b.resize(5, 5);

  SINA_ASSERT(b.size1() == 5, "invalid size1()");
  SINA_ASSERT(b.size2() == 5, "invalid size2()");
  SINA_ASSERT(b.capacity() == 10 * 10, "invalid capacity()");

  a.swap(b);
  b.clear();

  SINA_ASSERT(a.size1() == 5, "invalid size1()");
  SINA_ASSERT(a.size2() == 5, "invalid size2()");
  SINA_ASSERT(a.capacity() == 10 * 10, "invalid capacity()");

  SINA_ASSERT(b.size1() == 5, "invalid size1()");
  SINA_ASSERT(b.size2() == 5, "invalid size2()");
  SINA_ASSERT(b.capacity() == 5 * 5, "invalid capacity()");

  return 0;
}