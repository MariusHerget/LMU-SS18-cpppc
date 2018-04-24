#ifndef STACK_H
#define STACK_H
typedef double Type;

typedef struct {} Stack;

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
