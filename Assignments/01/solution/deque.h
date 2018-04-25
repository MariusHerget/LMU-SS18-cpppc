#ifndef DEQUE_H
#define DEQUE_H
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
typedef int Type;
typedef typename std::size_t size_type;

typedef struct {
        size_type _size;
        size_type _capacity;
        Type * data;
} Deque;

Deque * deque__new();
Deque * deque__copy(Deque * d);
void deque__delete(Deque * d);
Deque * deque__assign(Deque * d, Deque * r);
int deque__equals(Deque * d, Deque * r);
unsigned deque__size(Deque * d);
int deque__empty(Deque * d);
Type deque__push_back(Deque * d, Type e);
Type deque__pop_back(Deque * d);
Type deque__push_front(Deque * d, Type e);
Type deque__pop_front(Deque * d);

Deque * deque__reverse(Deque * d);

#endif //DEQUE_H
