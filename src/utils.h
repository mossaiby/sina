//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// utils.h
//
// utility classes and functions
//

#pragma once

// includes, system

#include <iostream>
#include <cstdlib>
#ifdef _MSC_VER
  #define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <Windows.h>
#else
	#include <sys/time.h>
#endif

#ifdef _OPENMP
  #include <omp.h>
#endif

// includes, project

#include "sina.h"

// macros

#define SINA_COUT std::cout
#define SINA_CERR std::cerr
#define SINA_ENDL std::endl

#define SINA_PRECISION(s, n) s.precision(n)
#define SINA_FIXED std::fixed
#define SINA_SCIENTIFIC std::scientific
#define SINA_DEFAULT(s) s.unsetf(std::ios_base::floatfield)

#define SINA_XSTR(s) SINA_STR(s)
#define SINA_STR(s) #s

#define SINA_XCONCAT(x, y) x ## y
#define SINA_CONCAT(x, y) SINA_XCONCAT(x, y)

#define SINA_FILE __FILE__
#define SINA_LINE __LINE__

#define SINA_DATE __DATE__
#define SINA_TIME __TIME__

// MSVC does not support __PRETTY_FUNCTION__, we use __FUNCSIG__ instead

#ifdef _MSC_VER
  #define SINA_FUNCTION __FUNCSIG__
#else
  #define SINA_FUNCTION __PRETTY_FUNCTION__
#endif

#define SINA_DEBUG_POINT SINA_FUNCTION << " in " << SINA_FILE << ":" << SINA_LINE

#define SINA_WARNING(message) { std::cerr << "warning: " << SINA_DEBUG_POINT << ": " << message << std::endl; }
#define SINA_ERROR(message) { std::cerr << "error: " << SINA_DEBUG_POINT << ": " << message << std::endl; abort(); }
#define SINA_NOT_IMPLEMENTED() { std::cerr << "error: " << SINA_DEBUG_POINT << ": not implemented" << std::endl; abort(); }

#define SINA_TIMER_IDENTIFIER(identifier) SINA_CONCAT(timer, identifier)
#define SINA_TIMER_LAST(identifier) SINA_TIMER_IDENTIFIER(identifier).last()
#define SINA_TIC(identifier, name) sina::utils::timer SINA_TIMER_IDENTIFIER(identifier)(name); SINA_TIMER_IDENTIFIER(identifier).tic()
#define SINA_TOC(identifier) std::cout << (SINA_TIMER_IDENTIFIER(identifier).name() ? SINA_TIMER_IDENTIFIER(identifier).name() : "time") << ": " << SINA_TIMER_IDENTIFIER(identifier).toc() << "s" << std::endl

// useful debugging macros

#ifdef NDEBUG
  #define SINA_DEBUG_STRING(message)
  #define SINA_WATCH(x)

  #define SINA_CHECK(condition, message)
  #define SINA_ASSERT(condition, message)

  #define SINA_CHECKPOINT()
#else
  #define SINA_DEBUG_STRING(message) { std::cerr << "debug: " << message << std::endl; }
  #define SINA_WATCH(x) { std::cout << #x << ": " << x << std::endl; }

  #define SINA_CHECK(condition, message) { if (!(condition)) { SINA_WARNING("check failed: " << message); } }
  #define SINA_ASSERT(condition, message) { if (!(condition)) { SINA_ERROR("assertion failed: " << message); } }

  #define SINA_CHECKPOINT() { std::cout << SINA_FUNCTION << ":" << std::endl; }
#endif


namespace sina
{
  namespace utils
  {
    class timer
    {
      public:

      timer(): _name(nullptr), _last()
      {
        // Empty constructor
      }

      timer(const char *name): _name(name), _last()
      {
        // Empty constructor
      }

      ~timer()
      {
        // Empty destructor
      }

      void tic()
      {
      #ifdef _MSC_VER
        QueryPerformanceCounter(&start);
      #else
        clock_gettime(CLOCK_MONOTONIC, &start);
      #endif
      }

      sina::kernel::scalar_t toc()
      {
      #ifdef _MSC_VER
        LARGE_INTEGER stop;
        LARGE_INTEGER frequency;

        QueryPerformanceCounter(&stop);
        QueryPerformanceFrequency(&frequency);
        return _last = static_cast<sina::kernel::scalar_t>(stop.QuadPart - start.QuadPart) / static_cast<sina::kernel::scalar_t>(frequency.QuadPart);
      #else
        struct timespec stop;

        clock_gettime(CLOCK_MONOTONIC, &stop);
        return _last = static_cast<sina::kernel::scalar_t>((stop.tv_sec - start.tv_sec) * 1000000000LL + (stop.tv_nsec - start.tv_nsec)) * 1.00e-9;
      #endif
      }

      sina::kernel::scalar_t last() const
      {
        return _last;
      }

      const char *name() const
      {
        return _name;
      }

      protected:
      
      const char *_name;
      sina::kernel::scalar_t _last;

      #ifdef _MSC_VER
        LARGE_INTEGER start;
      #else
        struct timespec start;
      #endif
    };

    void logo()
    {
      SINA_COUT <<
        "        _             " << SINA_ENDL <<
        "    ___(_)_ __   __ _ " << SINA_ENDL <<
        "   / __| | '_ \\ / _` |    simple and intuitive numerical analysis" << SINA_ENDL <<
        "   \\__ \\ | | | | (_| |    Farshid Mossaiby, University of Isfahan" << SINA_ENDL <<
        "   |___/_|_| |_|\\__,_|    (c) copyright 2020, all rights reserved" << SINA_ENDL <<
        SINA_ENDL <<
        "   version: " << SINA_VERSION_MAJOR << "." << SINA_VERSION_MINOR << "." << SINA_VERSION_PATCH << SINA_ENDL <<
        SINA_ENDL;
    }

    void openmp()
    {
      #ifdef _OPENMP
        SINA_COUT << "OpenMP enabled, no. of threads: " << omp_get_num_procs() << SINA_ENDL;
      #else
        SINA_COUT << "OpenMP disabled." << SINA_ENDL;
      #endif
    }
  }
}