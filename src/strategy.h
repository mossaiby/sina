//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//                      
// strategy.h
//
// strategy class
//

#pragma once

// includes, project

#include "sina.h"


namespace sina
{
  namespace kernel
  {
    class strategy
    {
      public:

      strategy()
      {
        // Empty constructor
      }

      virtual ~strategy()
      {
        // Empty destructor
      }

      virtual void solve() = 0;
    };
  }
}