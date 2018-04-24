#include "deque.h"

Deque * deque__new(){
        Deque * d = new Deque();
        d->_size = 0;
        d->data = static_cast<Type*>(malloc(sizeof(Type)+1));
        d->_capacity = 0;
        return d;
}
Deque * deque__copy(Deque * d){
        Deque * r = deque__new();
        r->data = static_cast<Type*>(malloc(d->_size*sizeof(Type)));
        r->_size = d->_size;
        r->_capacity = d->_capacity;
        for (int i=0; i<d->_size; i++) {
                r->data[i] = d->data[i];
        }
        return r;
}
void deque__delete(Deque * d){
        free(d);
}
Deque * deque__assign(Deque * d, Deque * r){
        d->_size = r->_size;
        d->_capacity = r->_capacity;
        d->data = r->data;
        return d;
}
int deque__equals(Deque * d, Deque * r){
        if (
                d->_size == r->_size &&
                d->_capacity == r->_capacity &&
                d->data == r->data
                ) {
                return 1;
        }
        else if (
                d->_size == r->_size &&
                d->_capacity == r->_capacity
                ) {
                int f=0;
                for (int i; i<r->_size; i++) {
                        if (r->data[i] != d->data[i]) f=1;
                }
                if (f==0) { return 1;}
                else {return 0;}
        }
        return 0;
}
unsigned deque__size(Deque * d){
        return d->_size;
}
int deque__empty(Deque * d){
        if (d->_size == 0) return 1;
        else return 0;
}
Type deque__push_back(Deque * d, Type e){
        Deque * dnew = new Deque();
        dnew->_size = d->_size+1;
        dnew->_capacity = d->_capacity+sizeof(Type);
        dnew->data = static_cast<Type*>(malloc(dnew->_capacity+1));
        for (int i=0; i<d->_size; i++) {
                dnew->data[i] = d->data[i];
        }
        dnew->data[d->_size] = e;
        *d = *dnew;
        return e;
}
Type deque__push_front(Deque * d, Type e){
        Deque * dnew = new Deque();
        dnew->_size = d->_size+1;
        dnew->_capacity = d->_capacity+sizeof(Type);
        dnew->data = static_cast<Type*>(malloc(dnew->_capacity+1));
        dnew->data[0] = e;
        for (int i=0; i<d->_size; i++) {
                dnew->data[i+1] = d->data[i];
        }

        *d = *dnew;
        return dnew->data[0];
}
Type deque__pop_back(Deque * d){
        Deque * dnew = new Deque();
        if (d->_size > 0) {
                Type ret =  d->data[d->_size-1];
                dnew->_size = d->_size-1;
                dnew->_capacity = d->_capacity-sizeof(Type);
                dnew->data = static_cast<Type*>(malloc(dnew->_capacity));
                for (int i=0; i<d->_size-1; i++) {
                        dnew->data[i] = d->data[i];
                }
                // printf("\t\t\t\t\t\t\tDEBUG pop_front ret: %d - %d\n", ret, d->data[0]);
                *d = *dnew;
                return ret;
        }
        printf("\t\t\t\t\t\tERROR DEQUE TOO SMALL");
        return 0;
}
Type deque__pop_front(Deque * d){
        Deque * dnew = new Deque();
        if (d->_size > 0) {
                Type ret =  d->data[0];
                dnew->_size = d->_size-1;
                dnew->_capacity = d->_capacity-sizeof(Type);
                dnew->data = static_cast<Type*>(malloc(dnew->_capacity));
                for (int i=1; i<d->_size; i++) {
                        dnew->data[i-1] = d->data[i];
                }
                *d = *dnew;
                return ret;
        }
        printf("\t\t\t\t\t\tERROR DEQUE TOO SMALL");
        return 0;
}
