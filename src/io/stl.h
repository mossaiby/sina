//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// stl.h
//
// stl file parser class
//

#pragma once

// includes, system

#include <fstream>
#include <string>
#include <cstring>
#include <cstdint>
#include <vector>
#include <algorithm>

// includes, project

#include "sina.h"
#include "utils.h"
#include "container.h"


namespace sina
{
  namespace io
  {
    struct triangle
    {
      sina::kernel::scalar_t points[3][3];
    };

    class stl
    {
      public:

      stl(): _name(nullptr)
      {
        // Empty constructor
      }

      ~stl()
      {
        delete[] _name;
      }

      bool load_ascii(const char *filename)
      {
        std::string buffer;
        std::ifstream f(filename, std::ifstream::in);

        if (!f.is_open())
        {
          return false;
        }

        f >> buffer;  // read "solid"
        SINA_ASSERT(buffer == "solid", "invalid stl header");

        std::getline(f, buffer);  // read model name with the leading space

        delete[] _name;
        _name = new char[buffer.length()]();
        std::strcpy(_name, buffer.c_str() + 1);  // copy and remove the leading space

        std::vector<sina::io::triangle> triangles;

        while (true)
        {
          f >> buffer;
          if (buffer == "endsolid")
          {
            _triangles.resize(triangles.size());
            std::memcpy(_triangles.data(), triangles.data(), triangles.size() * sizeof(triangle));
            return true;
          }

          std::getline(f, buffer);  // drop "facet normal ..." line
          std::getline(f, buffer);  // drop "outer loop" line

          triangle t;

          for (sina::kernel::index_t i = 0; i < 3; i++)
          {
            f >> buffer;  // read "vertex"
            for (sina::kernel::index_t j = 0; j < 3; j++)
            {
              f >> t.points[i][j];
            }
          }
          triangles.push_back(t);

          f >> buffer;  // drop "endloop" line
          SINA_ASSERT(buffer == "endloop", "invalid stl file");
          f >> buffer;  // drop "endfacet" line
          SINA_ASSERT(buffer == "endfacet", "invalid stl file");
        }
      }

      bool load_binary(const char *filename)
      {
        std::ifstream f(filename, std::ifstream::in | std::ifstream::binary);

        if (!f.is_open())
        {
          return false;
        }

        char name[81] = { 0 };
        f.read(name, 80);

        delete[] _name;
        _name = new char[std::strlen(name) + 1]();
        std::strcpy(_name, name);

        std::int32_t triangle_no;
        f.read(reinterpret_cast<char *>(&triangle_no), 4);

        _triangles.resize(triangle_no);

        for (sina::kernel::index_t k = 0; k < triangle_no; k++)
        {
          float normal[3];
          float points[3][3];
          char attributes[2];

          f.read(reinterpret_cast<char *>(normal), 3 * sizeof(float));
          f.read(reinterpret_cast<char *>(points), 3 * 3 * sizeof(float));
          f.read(attributes, sizeof(attributes));

          for (sina::kernel::index_t i = 0; i < 3; i++)
          {
            for (sina::kernel::index_t j = 0; j < 3; j++)
            {
              _triangles[k].points[i][j] = static_cast<sina::kernel::scalar_t>(points[i][j]);
            }
          }
        }

        return true;
      }

      bool load(const char *filename)
      {
        std::ifstream f(filename, std::ifstream::in | std::ifstream::binary);

        if (!f.is_open())
        {
          return false;
        }

        char buffer[7] = { 0 };

        f.read(buffer, 6);
        f.close();

        if (std::string(buffer) == "solid ")
        {
          return load_ascii(filename);
        }

        else
        {
          return load_binary(filename);
        }
      }

      const sina::kernel::dynamic_container<sina::io::triangle> &triangles() const
      {
        return _triangles;
      }

      void calculate_bounding_box()
      {
        for (sina::kernel::index_t i = 0; i < 3; i++)
        {
          _min_point[i] = _triangles[0].points[0][i];
          _max_point[i] = _triangles[0].points[0][i];
        }

        for (sina::kernel::index_t i = 0; i < _triangles.size(); i++)
        {
          for (sina::kernel::index_t j = 0; j < 3; j++)
          {
            for (sina::kernel::index_t k = 0; k < 3; k++)
            {
              _min_point[k] = std::min(_min_point[k], _triangles[i].points[j][k]);
              _max_point[k] = std::max(_max_point[k], _triangles[i].points[j][k]);
            }
          }
        }
      }

      void get_min_point(double min_point[3]) const
      {
        for (sina::kernel::index_t i = 0; i < 3; i++)
        {
          min_point[i] = _min_point[i];
        }
      }

      void get_max_point(double max_point[3]) const
      {
        for (sina::kernel::index_t i = 0; i < 3; i++)
        {
          max_point[i] = _max_point[i];
        }
      }

      protected:

      char *_name;
      sina::kernel::scalar_t _min_point[3];
      sina::kernel::scalar_t _max_point[3];
      sina::kernel::dynamic_container<sina::io::triangle> _triangles;
    };
  }
}