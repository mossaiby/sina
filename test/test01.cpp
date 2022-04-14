//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test01.cpp
//
// basic test for utils.h macros
//

// includes, project

#include "sina.h"
#include "utils.h"


template <typename __X, typename __Y> class A
{
  public:

  template <typename __Z> static void f()
  {
    SINA_COUT << "from A::f():" << SINA_ENDL
      << SINA_FUNCTION << " at " << SINA_FILE << ":" << SINA_LINE << SINA_ENDL;
  }
};

int main(int argc, char *argv[])
{
  SINA_COUT << "from main():" << SINA_ENDL
    << SINA_FUNCTION << SINA_ENDL
    << "Compiled on " << SINA_DATE << ", " << SINA_TIME << SINA_ENDL;

  A<int, float>::f<bool>();

  return 0;
}