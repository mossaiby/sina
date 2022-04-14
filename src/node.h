//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// node.h
//
// node class
//

#pragma once

// includes, project

#include "sina.h"
#include "container.h"


namespace sina
{
  namespace kernel
  {
    template <sina::kernel::index_t __dimension> class node: public static_container<sina::kernel::scalar_t, __dimension>
    {
      public:

      node()
      {
        // Empty constructor
      }

      ~node()
      {
        // Empty destructor
      }
    };

    template <sina::kernel::index_t __dimension> class node_set: public dynamic_container<node<__dimension> >
    {
      public:

      node_set()
      {
        // Empty constructor
      }

      node_set(const sina::kernel::index_t size): dynamic_container<node<__dimension> >(size)
      {
        // Empty constructor
      }

      ~node_set()
      {
        // Empty destructor
      }
    };
  }
}