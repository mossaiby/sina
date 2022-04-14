//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test07.cpp
//
// basic test for node.h class
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "node.h"
#include "container.h"


int main(int argc, char *argv[])
{
  typedef sina::kernel::node<3> node_t;
  typedef sina::kernel::node_set<3> node_set_t;

  SINA_ASSERT(sizeof(node_t) == 3 * sizeof(double), "extra bytes in node class");

  node_t node;

  SINA_ASSERT(node.size() == 3, "invalid size()");

  for (sina::kernel::index_t i = 0; i < 3; i++)
  {
    node[i] = i;
  }

  for (sina::kernel::index_t i = 0; i < 3; i++)
  {
    SINA_ASSERT(node[i] == i, "invalid value");
  }

  node_set_t node_set_1(5);

  SINA_ASSERT(node_set_1.size() == 5, "invalid size()");
  SINA_ASSERT(node_set_1.capacity() == 5, "invalid capacity()");

  for (sina::kernel::index_t i = 0; i < node_set_1.size(); i++)
  {
    for (sina::kernel::index_t j = 0; j < node_set_1[i].size(); j++)
    {
      node_set_1[i][j] = i * j;
    }
  }

  for (sina::kernel::index_t i = 0; i < node_set_1.size(); i++)
  {
    for (sina::kernel::index_t j = 0; j < node_set_1[i].size(); j++)
    {
      SINA_ASSERT(node_set_1[i][j] == i * j, "invalid value");
    }
  }

  node_set_t node_set_2;

  node_set_2.reserve(10);
  node_set_2.resize(5);

  SINA_ASSERT(node_set_2.size() == 5, "invalid size()");
  SINA_ASSERT(node_set_2.capacity() == 10, "invalid capacity()");

  node_set_1.swap(node_set_2);

  SINA_ASSERT(node_set_1.size() == 5, "invalid size()");
  SINA_ASSERT(node_set_1.capacity() == 10, "invalid capacity()");

  SINA_ASSERT(node_set_2.size() == 5, "invalid size()");
  SINA_ASSERT(node_set_2.capacity() == 5, "invalid capacity()");

  return 0;
}