//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// container.h
//
// static and dynamic container classes
//

#pragma once

// includes, project

#include "sina.h"
#include "utils.h"


namespace sina
{
  namespace kernel
  {
    template <typename __data_t, sina::kernel::index_t __size> class static_container
    {
      public:

      static_container()
      {
        // Empty constructor
      }

      ~static_container()
      {
        // Empty destructor
      }

      __data_t &operator[](const sina::kernel::index_t i)
      {
        SINA_ASSERT((i >= 0) && (i < __size), "index out of range");
        return _data[i];
      }

      const sina::kernel::index_t size() const
      {
        return __size;
      }

      __data_t *data()
      {
        return _data;
      }

      protected:

      __data_t _data[__size];
    };

    template <typename __data_t> class dynamic_container
    {
      public:

      dynamic_container(): _size(0), _capacity(0), _data(nullptr)
      {
        // Empty constructor
      }

      dynamic_container(const sina::kernel::index_t size): _size(size), _capacity(size)
      {
        _data = new __data_t[size]();
      }

      ~dynamic_container()
      {
        delete[] _data;
      }

      void swap(dynamic_container<__data_t> &c)
      {
        std::swap(_size, c._size);
        std::swap(_capacity, c._capacity);
        std::swap(_data, c._data);
      }

      __data_t &operator[](const sina::kernel::index_t i) const
      {
        SINA_ASSERT((i >= 0) && (i < _size), "index out of range");
        return _data[i];
      }

      void reserve(const sina::kernel::index_t new_capacity)
      {
        if (new_capacity > _capacity)
        {
          delete[] _data;
          _capacity = new_capacity;
          _data = new __data_t[new_capacity]();
        }
      }

      void resize(const sina::kernel::index_t new_size)
      {
        reserve(new_size);
        _size = new_size;
      }

      const sina::kernel::index_t size() const
      {
        return _size;
      }

      const sina::kernel::index_t capacity() const
      {
        return _capacity;
      }

      __data_t *data() const
      {
        return _data;
      }

      protected:

      sina::kernel::index_t _size;
      sina::kernel::index_t _capacity;
      __data_t *_data;      
    };
  }
}