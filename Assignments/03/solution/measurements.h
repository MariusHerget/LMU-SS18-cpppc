#ifndef CPPPC__A03__MEASUREMENTS_H__INCLUDED
#define CPPPC__A03__MEASUREMENTS_H__INCLUDED

#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

namespace cpppc {

template <typename T>
class Measurements
{
typedef typename                std::size_t            size_type;
typedef Measurements<T>                                   self_t;
typedef T                                                value_t;

typedef       T &                                      reference;
typedef const T &                                const_reference;
typedef typename std::vector<T>::iterator               iterator;
typedef typename std::vector<T>::const_iterator   const_iterator;

public:
  Measurements() = default;
  ~Measurements() = default;

  iterator begin()  {
          return _values.begin();
  }
  iterator end()    {
          return _values.end();
  }
  size_type size() const {
    return _values.size();
  }
  bool empty() const {
    return _values.empty();
  }

  void clear () {
    _values.clear();
  }

  T front() {
    return _values.front();
  }
  T back () {
    return _values.back();
  }
  // Read & Write
  T& operator[] (const int index) {
    return _values[index];
  }
  bool operator==(const Measurements & other) {
    return (_values == other.vals());
  }
  bool operator==(const Measurements & other) const {
    return (_values == other.vals());
  }

  void insert (T val) {
    _values.push_back(val);
  }
  void insert (iterator it1, iterator it2) {
    _values.insert(end(), it1, it2);
  }

  const std::vector<T> vals() const {
    return _values;
  }

T median() const;
double mean() const;
double variance() const;
double sigma() const;
// Durchdeligieren auf std::vector

private:
std::vector<T> _values;
size_type _size;
};

#include "measurements_impl.h"
} // namespace cpppc

#endif // CPPPC__A03__MEASUREMENTS_H__INCLUDED
