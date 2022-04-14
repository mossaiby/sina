//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// sina.h
//
// global definitions for sina
//

#pragma once

// includes, system

#include <cstddef>

// macros

#define SINA_VERSION_MAJOR 0
#define SINA_VERSION_MINOR 0
#define SINA_VERSION_PATCH 0

#define SINA_VERSION (((SINA_VERSION_MAJOR) * 10000) + ((SINA_VERSION_MINOR) * 100) + (SINA_VERSION_PATCH))


namespace sina
{
  namespace kernel
  {
    // type definitions for scalar and index types

    typedef double scalar_t;
    typedef std::size_t index_t;
  }
}