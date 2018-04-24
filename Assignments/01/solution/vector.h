#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
typedef int Type;
typedef typename std::size_t size_type;

typedef struct {
  // size_t can store every possible object -> no memory overflow
  size_type _size;
  size_type _capacity;
  Type* data;
} Vector;

typedef Type * VectorIterator;

Vector * vector__new();
Vector * vector__copy(Vector * v);
void vector__delete(Vector * v);
Vector * vector__assign(Vector * v, Vector * r);
int vector__equals(Vector * v, Vector * r);
unsigned vector__size(Vector * v);
int vector__empty(Vector * v);
VectorIterator vector__begin(Vector * v);
VectorIterator vector__end(Vector * v);
void vector__push_back(Vector * v, Type e);
Type vector__pop_back(Vector * v);
void vector__push_front(Vector * v, Type e);
Type vector__pop_front(Vector * v);
Type vector__at(Vector * v, int o);

#endif //VECTOR_H
