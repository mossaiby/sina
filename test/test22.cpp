//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// test22.cpp
//
// basic test voxelizer class
//

// includes, project

#include "sina.h"
#include "utils.h"
#include "io/stl.h"
#include "io/voxelizer.h"


#include <string>

int main(int argc, char *argv[])
{
  sina::utils::openmp();

  sina::io::stl model;
  model.load("car.stl");

  SINA_COUT << model.triangles().size() << " triangles." << SINA_ENDL;

  sina::io::voxel_array voxels;
  sina::io::voxelizer::voxelize(model, voxels, 64, 0.025);

  SINA_PRECISION(SINA_COUT, 2);
  SINA_COUT << 
    voxels.size1() << "x" << voxels.size2() << "x" << voxels.size3() << 
    " (" << voxels.size1() * voxels.size2() * voxels.size3() << ") voxels, " << voxels.filled() << " filled (" << SINA_FIXED <<
    static_cast<sina::kernel::scalar_t>(voxels.filled() * 100) / static_cast<sina::kernel::scalar_t>(voxels.size1() * voxels.size2() * voxels.size3()) <<
    "%)" << SINA_ENDL;

  SINA_COUT << "Writing VTK images..." << SINA_ENDL;
  voxels.write_vtk_image("out.vtk");
  voxels.write_vti_image("out.vti");

  return 0;
}