//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// voxelizer.h
//
// voxelizer class
//

#pragma once

// includes, system

#include <cstdint>

// includes, project

#include "sina.h"
#include "helpers.h"


namespace sina
{
  namespace io
  {
    class voxel_array
    {
      public:

      voxel_array(): _size1(0), _size2(0), _size3(0), _filled(0), _data(nullptr)
      {
        // Empty constructor
      }

      voxel_array(const sina::kernel::index_t size1, const sina::kernel::index_t size2, const sina::kernel::index_t size3): _size1(size1), _size2(size2), _size3(size3), _filled(0), _data(new std::uint8_t[size1 * size2 * size3]())
      {
        // Empty constructor
      }

      ~voxel_array()
      {
        delete[] _data;
      }

      std::uint8_t &operator()(const sina::kernel::index_t i, const sina::kernel::index_t j, const sina::kernel::index_t k) const
      {
        SINA_ASSERT(i >= 0 && i < _size1 && j >= 0 && j < _size2 && k >= 0 && k < _size3, "invalid index");
        return _data[(k * _size2 + j) * _size1 + i];
      }

      void resize(const sina::kernel::index_t new_size1, const sina::kernel::index_t new_size2, const sina::kernel::index_t new_size3)
      {
        delete[] _data;
        _data = new std::uint8_t[new_size1 * new_size2 * new_size3]();
        _size1 = new_size1;
        _size2 = new_size2;
        _size3 = new_size3;
      }

      const sina::kernel::index_t size1() const
      {
        return _size1;
      }

      const sina::kernel::index_t size2() const
      {
        return _size2;
      }

      const sina::kernel::index_t size3() const
      {
        return _size3;
      }

      const sina::kernel::index_t filled() const
      {
        return _filled;
      }

      const std::uint8_t *data() const
      {
        return _data;
      }

      void write_vtk_image(const char *filename) const
      {
        const std::uint8_t lookup_table[2 * 4] = { 
          0, 0, 0, 0, 
          255, 255, 255, 255
        };

        std::ofstream of(filename);

        of << "# vtk DataFile Version 2.0" << std::endl;
        of << "Flag data" << std::endl;
        of << "BINARY" << std::endl << std::endl;
        of << "DATASET STRUCTURED_POINTS" << std::endl;
        of << "DIMENSIONS " << _size1 << " " << _size2 << " " << _size3 << std::endl;
        of << "ORIGIN " << 0 << " " << 0 << " " << 0 << std::endl;
        of << "SPACING " << 1 << " " << 1 << " " << 1 << std::endl << std::endl;
        of << "POINT_DATA " << _size1 * _size2 * _size3 << std::endl;
        of << "COLOR_SCALARS flag 1" << std::endl;

        of.write(reinterpret_cast<const char *>(_data), _size1 * _size2 * _size3);

        of << "LOOKUP_TABLE Color 2" << std::endl;
        of.write(reinterpret_cast<const char *>(lookup_table), sizeof(lookup_table));
      }

      void write_vti_image(const char *filename) const
      {
        const std::uint8_t lookup_table[2 * 4] = { 
          0, 0, 0, 0, 
          255, 255, 255, 255
        };

        std::ofstream of(filename);

        of << "<?xml version=\"1.0\"?>" << std::endl;
        of << "<VTKFile type=\"ImageData\" version=\"0.1\" byte_order=\"LittleEndian\" header_type=\"UInt64\">" << std::endl;
        of << "<ImageData WholeExtent=\"1 " << _size1 << " 1 " << _size2 << " 1 " << _size3 << "\" Origin=\"0 0 0\" Spacing=\"1 1 1\">" << std::endl;
        of << "<Piece Extent=\"1 " << _size1 << " 1 " << _size2 << " 1 " << _size3 << "\">" << std::endl;
        of << "<PointData>" << std::endl;
        of << "<DataArray Name=\"flag\" NumberOfComponents=\"1\" Format=\"Ascii\" type=\"UInt8\">" << std::endl;

        for (std::uint64_t i = 0; i < _size1 * _size2 * _size3; i++)
        {
          of << (_data[i] == 0 ? "0 " : "1 ");
        }

        of << std::endl;

        of << "</DataArray>" << std::endl;
        of << "</PointData>" << std::endl;
        of << "</Piece>" << std::endl;
        of << "</ImageData>" << std::endl;
        of << "</VTKFile>" << std::endl;
      }

      friend class voxelizer;

      protected:

      sina::kernel::index_t _size1;
      sina::kernel::index_t _size2;
      sina::kernel::index_t _size3;
      sina::kernel::index_t _filled;
      std::uint8_t *_data;
    };

    class voxelizer
    {
      static constexpr int64_t fp_pow_1 = 16;  // TODO: What should this be?
      static constexpr int64_t fp_pow_2 = 12;  // TODO: What should this be?

      static constexpr std::uint8_t inside = 1;

      static constexpr std::uint8_t inside_x = 2;
      static constexpr std::uint8_t inside_y = 4;
      static constexpr std::uint8_t inside_z = 8;

      static constexpr std::uint8_t along_x = 16;
      static constexpr std::uint8_t along_y = 32;
      static constexpr std::uint8_t along_z = 64;

      typedef int64_t vector_2[2];
      typedef int64_t vector_3[3];


      static inline const bool zero(const vector_2 &v)
      {
        return v[0] == 0 && v[1] == 0;
      }

      class swizzle_xyz
      {
        public:

        static inline void forward(const vector_3 &v, vector_3 &r)
        { 
          r[0] = v[0];
          r[1] = v[1];
          r[2] = v[2];
        }
        
        static inline void backward(const vector_3 &v, vector_3 &r)
        {
          r[0] = v[0];
          r[1] = v[1];
          r[2] = v[2];
        }

        static constexpr std::uint8_t along = along_z;
      };

      class swizzle_zxy
      {
        public:
        
        static inline void forward(const vector_3 &v, vector_3 &r)
        {
          r[0] = v[2];
          r[1] = v[0];
          r[2] = v[1];
        }

        static inline void backward(const vector_3 &v, vector_3 &r)
        {
          r[0] = v[1];
          r[1] = v[2];
          r[2] = v[0];
        }

        static constexpr std::uint8_t along = along_y;
      };

      class swizzle_yzx
      {
        public:
        
        static inline void forward(const vector_3& v, vector_3 &r)
        {
          r[0] = v[1];
          r[1] = v[2];
          r[2] = v[0];
        }

        static inline void backward(const vector_3& v, vector_3 &r)
        {
          r[0] = v[2];
          r[1] = v[0];
          r[2] = v[1];
        }
        
        static constexpr std::uint8_t along = along_x;
      };

      static inline const bool in_triangle(int64_t i, int64_t j, const vector_3 &p0, const vector_3 &p1, const vector_3 &p2, int64_t &_depth)
      {
        const vector_2 delta_p0 = { i - p0[0], j - p0[1] };
        const vector_2 delta_p1 = { i - p1[0], j - p1[1] };
        const vector_2 delta_p2 = { i - p2[0], j - p2[1] };

        const vector_2 delta10 = { p1[0] - p0[0], p1[1] - p0[1] };
        const vector_2 delta21 = { p2[0] - p1[0], p2[1] - p1[1] };
        const vector_2 delta02 = { p0[0] - p2[0], p0[1] - p2[1] };

        const int64_t c0 = delta_p0[0] * delta10[1] - delta_p0[1] * delta10[0];
        const int64_t c1 = delta_p1[0] * delta21[1] - delta_p1[1] * delta21[0];
        const int64_t c2 = delta_p2[0] * delta02[1] - delta_p2[1] * delta02[0];

        const bool inside = (c0 <= 0 && c1 <= 0 && c2 <= 0) || (c0 >= 0 && c1 >= 0 && c2 >= 0);

        if (inside)
        {
          const int64_t area = c0 + c1 + c2;

          const int64_t b0 = (c1 << fp_pow_2) / area;
          const int64_t b1 = (c2 << fp_pow_2) / area;
          const int64_t b2 = (1 << fp_pow_2) - b0 - b1;

          _depth = (b0 * p0[2] + b1 * p1[2] + b2 * p2[2]) >> fp_pow_2;
        }

        return inside;
      }

      template <class __swizzler> static inline void rasterize(const vector_3 &p0, const vector_3 &p1, const vector_3 &p2, const voxel_array &voxels)
      {
        vector_3 t0;
        vector_3 t1;
        vector_3 t2;

        __swizzler::forward(p0, t0);
        __swizzler::forward(p1, t1);
        __swizzler::forward(p2, t2);

        // check if triangle is valid

        const vector_2 delta10 = { t1[0] - t0[0], t1[1] - t0[1] };
        const vector_2 delta21 = { t2[0] - t1[0], t2[1] - t1[1] };
        const vector_2 delta02 = { t0[0] - t2[0], t0[1] - t2[1] };
        
        if (zero(delta10) || zero(delta21) || zero(delta02) || delta02[0] * delta10[1] - delta02[1] * delta10[0] == 0)
        {
          return;
        }
        
        const int64_t min0 = sina::kernel::min(t0[0] >> fp_pow_1, t1[0] >> fp_pow_1, t2[0] >> fp_pow_1);
        const int64_t min1 = sina::kernel::min(t0[1] >> fp_pow_1, t1[1] >> fp_pow_1, t2[1] >> fp_pow_1);
        const int64_t max0 = sina::kernel::max(t0[0] >> fp_pow_1, t1[0] >> fp_pow_1, t2[0] >> fp_pow_1);
        const int64_t max1 = sina::kernel::max(t0[1] >> fp_pow_1, t1[1] >> fp_pow_1, t2[1] >> fp_pow_1);
        
        for (int64_t j = min1; j <= max1; j++)
        {
          for (int64_t i = min0; i <= max0; i++)
          {
            int64_t depth;
          
            if (in_triangle((i << fp_pow_1) + (1 << (fp_pow_1 - 1)), (j << fp_pow_1) + (1 << (fp_pow_1 - 1)), t0, t1, t2, depth))
            {
              vector_3 vx;
              __swizzler::backward({ i, j, depth >> fp_pow_1 }, vx);
              voxels(vx[0], vx[1], vx[2]) ^= __swizzler::along;
            }
          }
        }
      }

      static inline void fill(voxel_array &voxels)
      {
        // along x

        #pragma omp parallel for
        for (sina::kernel::index_t k = 0; k < voxels.size3(); k++)
        {
          for (sina::kernel::index_t j = 0; j < voxels.size2(); j++)
          {
            bool inside = false;
            
            for (sina::kernel::index_t i = 0; i < voxels.size1(); i++)
            {
              std::uint8_t &v = voxels(i, j, k);

              if (v & along_x)
              {
                inside = !inside;
              }

              if (inside)
              {
                v |= inside_x;
              }
            }
          }
        }

        // along y

        #pragma omp parallel for
        for (sina::kernel::index_t k = 0; k < voxels.size3(); k++)
        {
          for (sina::kernel::index_t j = 0; j < voxels.size1(); j++)
          {
            bool inside = false;
          
            for (sina::kernel::index_t i = 0; i < voxels.size2(); i++)
            {
              std::uint8_t &v = voxels(j, i, k);

              if (v & along_y)
              {
                inside = !inside;
              }

              if (inside)
              {
                v |= inside_y;
              }
            }
          }
        }

        // along z

        #pragma omp parallel for
        for (sina::kernel::index_t k = 0; k < voxels.size2(); k++)
        {
          for (sina::kernel::index_t j = 0; j < voxels.size1(); j++)
          {
            bool inside = false;
          
            for (sina::kernel::index_t i = 0; i < voxels.size3(); i++)
            {
              std::uint8_t &v = voxels(j, k, i);

              if (v & along_z)
              {
                inside = !inside;
              }

              if (inside)
              {
                v |= inside_z;
              }
            }
          }
        }

        // voting

        sina::kernel::index_t &filled = voxels._filled;
        filled = 0;

        #pragma omp parallel for reduction(+: filled)
        for (sina::kernel::index_t k = 0; k < voxels.size3(); k++)
        {
          for (sina::kernel::index_t j = 0; j < voxels.size2(); j++)
          {
            for (sina::kernel::index_t i = 0; i < voxels.size1(); i++)
            {
              std::uint8_t &v = voxels(i, j, k);
              std::uint8_t votes = ((v & inside_x) ? 1 : 0) + ((v & inside_y) ? 1 : 0) + ((v & inside_z) ? 1 : 0);
              if (v = votes > 1 ? inside : 0)
              {
                filled++;
              }
            }
          }
        }
      }

      public:

      static void voxelize(sina::io::stl &model, voxel_array &voxels, const int64_t max_resolution, const double scale_change)
      {
        model.calculate_bounding_box();

        double min_point[3];
        double max_point[3];

        model.get_min_point(min_point);
        model.get_max_point(max_point);

        for (sina::kernel::index_t i = 0; i < 3; i++)
        {
          const double w = max_point[i] - min_point[i];
          min_point[i] -= w * scale_change;
          max_point[i] += w * scale_change;
        }

        const double extent_x = max_point[0] - min_point[0];
        const double extent_y = max_point[1] - min_point[1];
        const double extent_z = max_point[2] - min_point[2];

        const double extent_max = sina::kernel::max(extent_x, extent_y, extent_z);

        const sina::kernel::index_t size_x = static_cast<sina::kernel::index_t>(max_resolution * extent_x / extent_max);
        const sina::kernel::index_t size_y = static_cast<sina::kernel::index_t>(max_resolution * extent_y / extent_max);
        const sina::kernel::index_t size_z = static_cast<sina::kernel::index_t>(max_resolution * extent_z / extent_max);

        voxels.resize(size_x, size_y, size_z);

        const int64_t box_scale = (1 << fp_pow_1) * max_resolution;
        const double factor = box_scale / extent_max;

        #pragma omp parallel for
        for (sina::kernel::index_t i = 0; i < model.triangles().size(); i++)
        {
          vector_3 p0 = { static_cast<std::int64_t>((model.triangles()[i].points[0][0] - min_point[0]) * factor), static_cast<std::int64_t>((model.triangles()[i].points[0][1] - min_point[1]) * factor), static_cast<std::int64_t>((model.triangles()[i].points[0][2] - min_point[2]) * factor) };
          vector_3 p1 = { static_cast<std::int64_t>((model.triangles()[i].points[1][0] - min_point[0]) * factor), static_cast<std::int64_t>((model.triangles()[i].points[1][1] - min_point[1]) * factor), static_cast<std::int64_t>((model.triangles()[i].points[1][2] - min_point[2]) * factor) };
          vector_3 p2 = { static_cast<std::int64_t>((model.triangles()[i].points[2][0] - min_point[0]) * factor), static_cast<std::int64_t>((model.triangles()[i].points[2][1] - min_point[1]) * factor), static_cast<std::int64_t>((model.triangles()[i].points[2][2] - min_point[2]) * factor) };

          for (sina::kernel::index_t j = 0; j < 3; j++)
          {
            p0[j] = sina::kernel::max(0L, sina::kernel::min(p0[j], box_scale - 1));
            p1[j] = sina::kernel::max(0L, sina::kernel::min(p1[j], box_scale - 1));
            p2[j] = sina::kernel::max(0L, sina::kernel::min(p2[j], box_scale - 1));
          }
          
          rasterize<swizzle_xyz>(p0, p1, p2, voxels); // xy view
          rasterize<swizzle_yzx>(p0, p1, p2, voxels); // yz view
          rasterize<swizzle_zxy>(p0, p1, p2, voxels); // zx view
        }

        fill(voxels);
      }
    };
  }
}