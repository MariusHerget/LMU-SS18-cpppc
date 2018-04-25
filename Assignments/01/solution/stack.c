#include "stack.h"

Stack * stack__new(){
        Stack * s = new Stack();
        s->_size =0;
        s->_capacity = 0;
        s->data = static_cast<Type*>(malloc(sizeof(Type)+1));
        return s;
}
Stack * stack__copy(Stack * s){
        Stack * r = stack__new();
        r->data = static_cast<Type*>(malloc(s->_size*sizeof(Type)));
        r->_size = s->_size;
        r->_capacity = s->_capacity;
        for (int i=0; i<s->_size; i++) {
                r->data[i] = s->data[i];
        }
        return r;
}
void stack__delete(Stack * s){
        free(s);
}
Stack * stack__assign(Stack * s, Stack * r){
        s->_size = r->_size;
        s->_capacity = r->_capacity;
        s->data = r->data;
        return s;
}
int stack__equals(Stack * s, Stack * r){
        if (
                s->_size == r->_size &&
                s->_capacity == r->_capacity &&
                s->data == r->data
                ) {
                return 1;
        }
        else if (
                s->_size == r->_size &&
                s->_capacity == r->_capacity
                ) {
                int f=0;
                for (int i; i<r->_size; i++) {
                        if (r->data[i] != s->data[i]) f=1;
                }
                if (f==0) { return 1;}
                else {return 0;}
        }
        return 0;
}
unsigned stack__size(Stack * s){
        return s->_size;
}
int stack__empty(Stack * s){
        if (s->_size == 0) return 1;
        else return 0;
}
void stack__push(Stack * s, Type e){
        Stack * snew = stack__new();
        snew->_size = s->_size+1;
        snew->_capacity = s->_capacity+sizeof(Type);
        snew->data = static_cast<Type*>(malloc(snew->_capacity+1));
        for (int i=0; i<s->_size; i++) {
                snew->data[i] = s->data[i];
        }
        snew->data[s->_size] = e;
        *s = *snew;
}
Type stack__pop(Stack * s){
        Stack * snew = stack__new();
        if (s->_size > 0) {
                Type ret =  s->data[s->_size-1];
                snew->_size = s->_size-1;
                snew->_capacity = s->_capacity-sizeof(Type);
                snew->data = static_cast<Type*>(malloc(snew->_capacity));
                for (int i=0; i<s->_size-1; i++) {
                        snew->data[i] = s->data[i];
                }
                *s = *snew;
                return ret;
        }
        return 0;
}
Stack * stack__reverse(Stack * s){
        Stack * snew = stack__new();
        for (int i=s->_size-1; i>=0; i--) {
                stack__push(snew, s->data[i]);
        }
        return snew;
}
