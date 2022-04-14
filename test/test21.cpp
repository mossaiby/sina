//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test21.cpp
//
// basic test for stl class
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "io/stl.h"


int main(int argc, char *argv[])
{
  sina::io::stl humanoid;
  SINA_ASSERT(humanoid.load("../misc/stl/humanoid.stl"), "could not load stl file");  // sample ascii stl file
  SINA_COUT << "humanoid: " << humanoid.triangles().size() << " triangles." << SINA_ENDL;

  sina::io::stl cube;
  SINA_ASSERT(cube.load("../misc/stl/cube.stl"), "could not load stl file");  // sample binary stl file
  SINA_COUT << "cube: " << cube.triangles().size() << " triangles." << SINA_ENDL;
  
  sina::io::stl sphere;
  SINA_ASSERT(sphere.load("../misc/stl/sphere.stl"), "could not load stl file");  // sample ascii stl file
  SINA_COUT << "sphere: " << sphere.triangles().size() << " triangles." << SINA_ENDL;

  sina::io::stl sphericon;
  SINA_ASSERT(sphericon.load("../misc/stl/sphericon.stl"), "could not load stl file");  // sample ascii stl file
  SINA_COUT << "sphericon: " << sphericon.triangles().size() << " triangles." << SINA_ENDL;

  sina::io::stl car;
  SINA_ASSERT(car.load("../misc/stl/car.stl"), "could not load stl file");  // big binary stl file
  SINA_COUT << "car: " << car.triangles().size() << " triangles." << SINA_ENDL;

  return 0;
}