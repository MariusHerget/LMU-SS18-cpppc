#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
typedef double Type;
typedef typename std::size_t size_type;

typedef struct {
        // size_t can store every possible object -> no memory overflow
        size_type _size;
        size_type _capacity;
        Type * data;
} Stack;


Stack * stack__new();
Stack * stack__copy(Stack * s);
void stack__delete(Stack * s);
Stack * stack__assign(Stack * v, Stack * r);
int stack__equals(Stack * v, Stack * r);
unsigned stack__size(Stack * s);
int stack__empty(Stack * s);
void stack__push(Stack * s, Type e);
Type stack__pop(Stack * s);

#endif //stack_H
