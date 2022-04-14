//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//                      
// algebra.h
//
// vector and matrix classes
//

#pragma once

// includes, system

#include <algorithm>

// includes, project

#include "sina.h"
#include "utils.h"


namespace sina
{
  namespace kernel
  {
    class vector
    {
      public:
    
      vector(): _size(0), _capacity(0), _data(nullptr), _external_data(false)
      {
        // Empty constructor
      }

      vector(const sina::kernel::index_t size): _size(size), _capacity(size), _data(new sina::kernel::scalar_t[size]()), _external_data(false)
      {
        // Empty constructor
      }

      vector(sina::kernel::scalar_t *data, const sina::kernel::index_t size): _size(size), _capacity(size), _data(data), _external_data(true)
      {
        // Empty constructor
      }

      ~vector()
      {
        if (!_external_data)
        {
          delete[] _data;
        }
      }

      void clear() const
      {
        for (sina::kernel::index_t i = 0; i < _size; i++)
        {
          _data[i] = sina::kernel::scalar_t();
        }
      }

      void swap(sina::kernel::vector &v)
      {
        std::swap(_size, v._size);
        std::swap(_capacity, v._capacity);
        std::swap(_data, v._data);
        std::swap(_external_data, v._external_data);
      }

      sina::kernel::vector &operator=(sina::kernel::vector &v)
      {
        if (!_external_data)
        {
          delete[] _data;
        }
        _size = v._size;
        _capacity = v._capacity;
        _data = v._data;
        _external_data = true;
        return *this;
      }

      sina::kernel::vector &operator=(sina::kernel::vector &&v)
      {
        if (!_external_data)
        {
          delete[] _data;
        }
        _size = v._size;
        _capacity = v._capacity;
        _data = v._data;
        _external_data = v._external_data;
        v._data = nullptr;
        return *this;
      }

      sina::kernel::scalar_t &operator[](const sina::kernel::index_t i) const
      {
        SINA_ASSERT((i >= 0) && (i < _size), "index out of range");
        return _data[i];
      }

      void reserve(const sina::kernel::index_t new_capacity)
      {
        if (!_external_data && new_capacity > _capacity)
        {
          delete[] _data;
          _capacity = new_capacity;
          _data = new sina::kernel::scalar_t[new_capacity]();
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

      sina::kernel::scalar_t *data() const
      {
        return _data;
      }

      const bool empty() const
      {
        return _data == nullptr;
      }

      protected:

      sina::kernel::index_t _size;
      sina::kernel::index_t _capacity;
      sina::kernel::scalar_t *_data;
      bool _external_data;

      friend std::ostream &operator<<(std::ostream &os, const sina::kernel::vector &v)
      {
        os << "[" << v._size << "](";
        for (sina::kernel::index_t i = 0; i < v._size; i++)
        {
          os << v._data[i] << (i != v._size - 1 ? "," : "");
        }
        os << ")";
        return os;
      }
    };

    class matrix
    {
      public:
      
      matrix(): _size1(0), _size2(0), _capacity(0), _data(nullptr), _external_data(false)
      {
        // Empty constructor
      }

      matrix(const sina::kernel::index_t size1, const sina::kernel::index_t size2): _size1(size1), _size2(size2), _capacity(size1 * size2), _data(new sina::kernel::scalar_t[size1 * size2]()), _external_data(false)
      {
        // Empty constructor
      }

      matrix(sina::kernel::scalar_t *data, const sina::kernel::index_t size1, const sina::kernel::index_t size2): _size1(size1), _size2(size2), _capacity(size1 * size2), _data(data), _external_data(true)
      {
        // Empty constructor
      }

      ~matrix()
      {
        if (!_external_data)
        {
          delete[] _data;
        }
      }

      void clear() const
      {
        for (sina::kernel::index_t i = 0; i < _size1 * _size2; i++)
        {
          _data[i] = sina::kernel::scalar_t();
        }
      }

      void swap(sina::kernel::matrix &m)
      {
        std::swap(_size1, m._size1);
        std::swap(_size2, m._size2);
        std::swap(_capacity, m._capacity);
        std::swap(_data, m._data);
        std::swap(_external_data, m._external_data);
      }

      sina::kernel::matrix &operator=(sina::kernel::matrix &m)
      {
        if (!_external_data)
        {
          delete[] _data;
        }
        _size1 = m._size1;
        _size2 = m._size2;
        _capacity = m._capacity;
        _data = m._data;
        _external_data = true;
        return *this;
      }

      sina::kernel::matrix &operator=(sina::kernel::matrix &&m)
      {
        if (!_external_data)
        {
          delete[] _data;
        }
        _size1 = m._size1;
        _size2 = m._size2;
        _capacity = m._capacity;
        _data = m._data;
        _external_data = m._external_data;
        m._data = nullptr;
        return *this;
      }

      sina::kernel::scalar_t &operator()(const sina::kernel::index_t i, const sina::kernel::index_t j) const
      {
        SINA_ASSERT((i >= 0) && (j >= 0) && (i < _size1) && (j < _size2), "index out of range");
        return _data[i * _size2 + j];
      }

      void get_row(sina::kernel::index_t i, sina::kernel::vector &v) const
      {
        v = sina::kernel::vector(&_data[i * _size2], _size2);
      }

      void reserve(const sina::kernel::index_t new_capacity)
      {
        if (!_external_data && new_capacity > _capacity)
        {
          delete[] _data;
          _capacity = new_capacity;
          _data = new sina::kernel::scalar_t[new_capacity]();
        }
      }

      void resize(const sina::kernel::index_t new_size1, const sina::kernel::index_t new_size2)
      {
        reserve(new_size1 * new_size2);
        _size1 = new_size1;
        _size2 = new_size2;
      }

      const sina::kernel::index_t size1() const
      {
        return _size1;
      }

      const sina::kernel::index_t size2() const
      {
        return _size2;
      }

      const sina::kernel::index_t capacity() const
      {
        return _capacity;
      }

      sina::kernel::scalar_t *data() const
      {
        return _data;
      }

      const bool empty() const
      {
        return _data == nullptr;
      }

      protected:
    
      sina::kernel::index_t _size1;
      sina::kernel::index_t _size2;
      sina::kernel::index_t _capacity;
      sina::kernel::scalar_t *_data;
      bool _external_data;

      friend std::ostream &operator<<(std::ostream &os, const sina::kernel::matrix &m)
      {
        os << "[" << m._size1 << "," << m._size2 << "](";
        for (sina::kernel::index_t i = 0; i < m._size1; i++)
        {
          os << "(";
          for (sina::kernel::index_t j = 0; j < m._size2; j++)
          {
            os << m._data[i * m._size2 + j] << (j != m._size2 - 1 ? "," : "");
          }
          os << ")" << (i != m._size1 - 1 ? "," : "");
        }
        os << ")";
        return os;
      }
    };

    class array_3d
    {
      public:

      array_3d(): _size1(0), _size2(0), _capacity(0), _data(nullptr), _external_data(false)
      {
        // Empty constructor
      }

      array_3d(const sina::kernel::index_t size1, const sina::kernel::index_t size2, const sina::kernel::index_t size3): _size1(size1), _size2(size2), _size3(size3), _capacity(size1 * size2 * size3), _data(new sina::kernel::scalar_t[size1 * size2 * size3]()), _external_data(false)
      {
        // Empty constructor
      }

      array_3d(sina::kernel::scalar_t *data, const sina::kernel::index_t size1, const sina::kernel::index_t size2, sina::kernel::index_t size3): _size1(size1), _size2(size2), _size3(size3), _capacity(size1 * size2 * size3), _data(data), _external_data(true)
      {
        // Empty constructor
      }

      ~array_3d()
      {
        if (!_external_data)
        {
          delete[] _data;
        }
      }

      void clear() const
      {
        for (sina::kernel::index_t i = 0; i < _size1 * _size2 * _size3; i++)
        {
          _data[i] = sina::kernel::scalar_t();
        }
      }

      void swap(sina::kernel::array_3d &a)
      {
        std::swap(_size1, a._size1);
        std::swap(_size2, a._size2);
        std::swap(_size3, a._size3);
        std::swap(_capacity, a._capacity);
        std::swap(_data, a._data);
        std::swap(_external_data, a._external_data);
      }

      sina::kernel::array_3d &operator=(sina::kernel::array_3d &a)
      {
        if (!_external_data)
        {
          delete[] _data;
        }
        _size1 = a._size1;
        _size2 = a._size2;
        _size3 = a._size3;
        _capacity = a._capacity;
        _data = a._data;
        _external_data = true;
        return *this;
      }

      sina::kernel::array_3d &operator=(sina::kernel::array_3d &&a)
      {
        if (!_external_data)
        {
          delete[] _data;
        }
        _size1 = a._size1;
        _size2 = a._size2;
        _size3 = a._size3;
        _capacity = a._capacity;
        _data = a._data;
        _external_data = a._external_data;
        a._data = nullptr;
        return *this;
      }

      sina::kernel::scalar_t &operator()(const sina::kernel::index_t i, const sina::kernel::index_t j, const sina::kernel::index_t k) const
      {
        SINA_ASSERT((i >= 0) && (j >= 0) && (k >= 0) && (i < _size1) && (j < _size2) && (k < _size3), "index out of range");
        return _data[i * _size3 * _size2 + j * _size2 + k];
      }

      void get_slice(sina::kernel::index_t i, sina::kernel::matrix &m) const
      {
        m = sina::kernel::matrix(&_data[i * _size3 * _size2], _size2, _size3);
      }

      void reserve(const sina::kernel::index_t new_capacity)
      {
        if (!_external_data && new_capacity > _capacity)
        {
          delete[] _data;
          _capacity = new_capacity;
          _data = new sina::kernel::scalar_t[new_capacity]();
        }
      }

      void resize(const sina::kernel::index_t new_size1, const sina::kernel::index_t new_size2, const sina::kernel::index_t new_size3)
      {
        reserve(new_size1 * new_size2 * new_size3);
        _size1 = new_size1;
        _size2 = new_size2;
        _size3 = new_size3;
      }

      sina::kernel::index_t size1() const
      {
        return _size1;
      }

      sina::kernel::index_t size2() const
      {
        return _size2;
      }

      sina::kernel::index_t size3() const
      {
        return _size3;
      }

      const sina::kernel::index_t capacity() const
      {
        return _capacity;
      }
      
      sina::kernel::scalar_t *data() const
      {
        return _data;
      }

      const bool empty() const
      {
        return _data == nullptr;
      }

      protected:

      sina::kernel::index_t _size1;
      sina::kernel::index_t _size2;
      sina::kernel::index_t _size3;
      sina::kernel::index_t _capacity;
      sina::kernel::scalar_t *_data;
      bool _external_data;

      friend std::ostream &operator<<(std::ostream &os, const sina::kernel::array_3d &a)
      {
        os << "[" << a._size1 << "," << a._size2 << "," << a._size3 << "](";
        for (sina::kernel::index_t i = 0; i < a._size1; i++)
        {
          os << "(";
          for (sina::kernel::index_t j = 0; j < a._size2; j++)
          {
            os << "(";
            for (sina::kernel::index_t k = 0; k < a._size2; k++)
            {
              os << a._data[i * a._size3 * a._size2 + j * a._size2 + k] << (k != a._size3 - 1 ? "," : "");
            }
            os << ")" << (j != a._size2 - 1 ? "," : "");
          }
          os << ")" << (i != a._size1 - 1 ? "," : "");
        }
        os << ")";
        return os;
      }
    };

    void add_amt_n_m(const sina::kernel::scalar_t a, const sina::kernel::matrix &m, const sina::kernel::matrix &n, sina::kernel::matrix &r)
    {
      SINA_ASSERT(m.size1() == n.size1(), "invalid dimension");
      SINA_ASSERT(n.size2() == m.size1(), "invalid dimension");

      r.resize(m.size2(), m.size2());

      for (sina::kernel::index_t i = 0; i < m.size2(); i++)
      {
        for (sina::kernel::index_t j = 0; j < m.size1(); j++)
        {
          for (sina::kernel::index_t k = 0; k < m.size1(); k++)
          {
            for (sina::kernel::index_t l = 0; l < m.size2(); l++)
            {
              r(i, l) += a * m(j, i) * n (j, k) * m (k, l);  // TODO: check if creating a temporary object is faster than this
            }
          }
        }
      }      
    }

    void am_v_bw(const sina::kernel::scalar_t a, const sina::kernel::scalar_t b, const sina::kernel::matrix &m, const sina::kernel::vector &v, const sina::kernel::vector &w, sina::kernel::vector &r)
    {
      SINA_ASSERT(m.size2() == v.size(), "invalid dimension");
      SINA_ASSERT(m.size2() == w.size(), "invalid dimension");

      r.resize(m.size1());
      r.clear();

      for (sina::kernel::index_t i = 0; i < m.size1(); i++)
      {
        for (sina::kernel::index_t j = 0; j < m.size2(); j++)
        {
          r[i] += a * m(i, j) * v[j] + b * w[j];
        }
      }
    }

    void m_sn(const sina::kernel::index_t s, const sina::kernel::matrix &m, const sina::kernel::matrix &n, sina::kernel::matrix &r)
    {
      SINA_ASSERT(m.size2() == (n.size1() - s), "invalid dimension");

      r.resize(m.size1(), n.size2());
      r.clear();

      for (sina::kernel::index_t i = 0; i < m.size1(); i++)
      {
        for (sina::kernel::index_t j = 0; j < m.size2(); j++)
        {
          for (sina::kernel::index_t k = 0; k < n.size2(); k++)
          {
            r(i, k) += m(i, j) * n(j + s, k);
          }
        }
      }
    }

    void add_av(const sina::kernel::scalar_t a, const sina::kernel::vector &v, sina::kernel::vector &r)
    {
      r.resize(v.size());

      for (sina::kernel::index_t i = 0; i < v.size(); i++)
      {
        r[i] += a * v[i];
      }
    }

    void add_amt_v(const sina::kernel::scalar_t a, const sina::kernel::matrix &m, const sina::kernel::vector &v, sina::kernel::vector &r)
    {
      SINA_ASSERT(m.size1() == v.size(), "invalid dimension");
      
      r.resize(m.size2());

      for (sina::kernel::index_t i = 0; i < m.size2(); i++)
      {
        for (sina::kernel::index_t j = 0; j < m.size1(); j++)
        {
          r[i] += a * m(j, i) * v[j];
        }
      }
    }

    void add_av2(const sina::kernel::scalar_t a, const sina::kernel::vector &v, sina::kernel::vector &r)
    {
      r.resize(v.size());

      for (sina::kernel::index_t i = 0; i < v.size(); i++)
      {
        r[i] += a * v[i] * v[i];
      }
    }
  }
}