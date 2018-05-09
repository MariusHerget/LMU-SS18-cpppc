#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <sstream>
#include <string>

namespace cpppc {


template <typename VectorType>
class Vector {
private:
// size_t can store every possible object -> no memory overflow
typedef typename std::size_t size_type;
// Iterator
public:
typedef VectorType * VectorIterator;
// Vector
private:
size_type _size;
std::string _name;
VectorType *    _data = nullptr;

public:
Vector(
        const std::string & name,
        size_type size,
        VectorType base_val); // -> Rule of three (populate)
// vector__delete
~Vector();  // -> Rule of three (delete)
Vector(const Vector &other); // -> Rule of three (copy constructor)
// vector__assign / vector__copy
Vector & operator=(const Vector & other); // -> Rule of three (copy assignment)
// vector__equals
bool operator==(const Vector & other);

inline const std::string & name() const {
        return _name;
}
// vector__size
inline size_type size() const {
        return _size;
}
// vector__at
inline VectorType & operator[](int index)  {
        if (index < 0 || static_cast<int>(_size) <= index) {
                throw std::invalid_argument("index out of bounds");
        }
        return _data[index];
}
// vector__at const
inline const VectorType & operator[](int index) const {
        if (index < 0 || static_cast<int>(_size) <= index) {
                throw std::invalid_argument("index out of bounds");
        }
        return _data[index];
}

inline VectorType * data()  {
        return _data;
}

inline const VectorType * data() const {
        return _data;
}
// vector__empty
inline const bool empty() const {
        if (_size == 0) return true;
        else return false;
}
// vector__begin
VectorIterator begin(){
        return &_data[0];
}
// vector__end
const VectorIterator end() const {
        return &_data[(_size)];
}
// vector__push_back
void push_back(VectorType val);
VectorType pop_back();
// vector__reverse
inline void reverse();
}; // Class Vector

#include "vector_impl.h"
} // Namespace cpppc
#endif //VECTOR_H
