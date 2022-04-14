//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// helpers.h
//
// helper classes
//

#pragma once

// includes, system

#include <algorithm>

// includes, project

#include "sina.h"


namespace sina
{
  namespace kernel
  {
    template <typename __data_t> inline __data_t min(__data_t a, __data_t b)
    {
      return std::min(a, b);
    }

    template <typename __data_t> inline __data_t max(__data_t a, __data_t b)
    {
      return std::max(a, b);
    }

    template <typename __data_t> inline __data_t min(__data_t a, __data_t b, __data_t c)
    {
      return std::min(a, std::min(b, c));
    }

    template <typename __data_t> inline __data_t max(__data_t a, __data_t b, __data_t c)
    {
      return std::max(a, std::max(b, c));
    }

    template <typename __data_t> class reference_wrapper
    {
      public:

      reference_wrapper(): _data(nullptr)
      {
        // Empty constructor
      }

      reference_wrapper(__data_t &data): _data(&data)
      {
        // Empty constructor
      }

      reference_wrapper(__data_t *data): _data(data)
      {
        // Empty constructor
      }

      ~reference_wrapper()
      {
        // Empty destructor
      }

      void set(__data_t &data)
      {
        _data = &data;
      }

      void set(__data_t *data)
      {
        _data = data;
      }

      __data_t &operator()() const
      {
        return *_data;
      }

      operator __data_t &() const
      {
        return *_data;
      }

      protected:

      __data_t *_data;
    };
  }
}