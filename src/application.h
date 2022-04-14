//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//                      
// application.h
//
// application class
//

#pragma once

// includes, project

#include "sina.h"


namespace sina
{
  namespace kernel
  {
    class application
    {
      public:

      application()
      {
        // Empty constructor
      }

      virtual ~application()
      {
        // Empty destructor
      }

      virtual void initialize() = 0;

      virtual void run() = 0;

      virtual void finalize() = 0;
    };
  }
}