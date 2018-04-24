#ifndef DEQUE_H
#define DEQUE_H
typedef int Type;
typedef typename std::size_t size_type;

typedef struct {

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

#endif //VECTOR_H
