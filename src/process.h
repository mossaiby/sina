//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// process.h
//
// process class
//

#pragma once

// includes, project

#include "sina.h"


namespace sina
{
  namespace kernel
  {
    class process
    {
      public:

      process()
      {
        // Empty constructor
      }

      virtual ~process()
      {
        // Empty destructor
      }

      virtual void execute() = 0;
    };
  }
}