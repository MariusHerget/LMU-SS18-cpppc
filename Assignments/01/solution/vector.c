#include "vector.h"

Vector *  vector__new(){
        Vector * v = new Vector();
        // Init data with one element to avoid SegmentationFault
        v->data = static_cast<Type*>(malloc(sizeof(Type)+1));
        v->_size = 0;
        v->_capacity = 0;
        return v;
}
Vector * vector__copy(Vector * v){
        Vector * r = vector__new();
        r->data = static_cast<Type*>(malloc(v->_size*sizeof(Type)));
        r->_size = v->_size;
        r->_capacity = v->_capacity;
        // strncpy(r->data, v->data, sizeof(Type)*v->_size);
        for (int i=0; i<v->_size; i++) {
                r->data[i] = v->data[i];
                // printf("\t\t\t\t\t\t\tDEBUG Copy: %d - %d\n",v->data[i],r->data[i]);
        }
        return r;
}
void vector__delete(Vector * v){
        // printf("\n #################TEST\t%d",v->_size);
        // SegmentationFault when trying to free pointer --> TODO: DEBUG
        // for(int i=0; i< v->_size; i++) {
        //         free(v->data[i]);
        // }
        // free(v->data);
        free(v);
}
Vector * vector__assign(Vector * v, Vector * r) {
        v->_size = r->_size;
        v->_capacity = r->_capacity;
        v->data = r->data;
        return v;
}
int vector__equals(Vector * v, Vector * r){
        if (
                v->_size == r->_size &&
                v->_capacity == r->_capacity &&
                v->data == r->data
                ) {
                return 1;
        }
        else if (
                v->_size == r->_size &&
                v->_capacity == r->_capacity
                ) {
                int f=0;
                for (int i; i<r->_size; i++) {
                        if (r->data[i] != v->data[i]) f=1;
                }
                if (f==0) { return 1;}
                else {return 0;}
        }
        return 0;
}
unsigned vector__size(Vector * v){
        return v->_size;
}
int vector__empty(Vector * v){
        if (v->_size == 0) return 1;
        else return 0;
}
VectorIterator vector__begin(Vector * v){
        return v->data;
}
VectorIterator vector__end(Vector * v){
        return v->data + v->_size;
}
void vector__push_back(Vector * v, Type e){
        Vector * vnew = vector__new();
        vnew->_size = v->_size+1;
        vnew->_capacity = v->_capacity+sizeof(Type);
        vnew->data = static_cast<Type*>(malloc(vnew->_capacity+1));
        for (int i=0; i<v->_size; i++) {
                vnew->data[i] = v->data[i];
        }
        vnew->data[v->_size] = e;
        *v = *vnew;
}
void vector__push_front(Vector * v, Type e){
        Vector * vnew = vector__new();
        vnew->_size = v->_size+1;
        vnew->_capacity = v->_capacity+sizeof(Type);
        vnew->data = static_cast<Type*>(malloc(vnew->_capacity+1));
        vnew->data[0] = e;
        for (int i=0; i<v->_size; i++) {
                vnew->data[i+1] = v->data[i];
        }
        *v = *vnew;
        // printf("\t\t\t\t\t\t\tDEBUG push_front: ");
        // for (int i=0; i<v->_size; i++)  {
        //         printf("%d - ",v->data[i]);
        // }
        // printf("\n");
}
Type vector__pop_back(Vector * v){
        Vector * vnew = vector__new();
        // printf("\t\t\t\t\t\t\tDEBUG pop_front: %d\n", v->_size);
        if (v->_size > 0) {
                Type ret =  v->data[v->_size-1];
                vnew->_size = v->_size-1;
                vnew->_capacity = v->_capacity-sizeof(Type);
                vnew->data = static_cast<Type*>(malloc(vnew->_capacity));
                for (int i=0; i<v->_size-1; i++) {
                        vnew->data[i] = v->data[i];
                }
                // printf("\t\t\t\t\t\t\tDEBUG pop_front ret: %d - %d\n", ret, v->data[0]);
                *v = *vnew;
                return ret;
        }
        return 0;
}
Type vector__pop_front(Vector * v){
        Vector * vnew = vector__new();
        if (v->_size > 0) {
                Type ret =  v->data[0];
                vnew->_size = v->_size-1;
                vnew->_capacity = v->_capacity-sizeof(Type);
                vnew->data = static_cast<Type*>(malloc(vnew->_capacity));
                for (int i=1; i<v->_size; i++) {
                        vnew->data[i-1] = v->data[i];
                }
                *v = *vnew;
                return ret;
        }
        return 0;
}
Type vector__at(Vector * v, int o){
        if (o >= v->_size) {
                printf("\t\t\t\t\t\t\tERROR: %d\n",v->data[o]);
                return 0;
        }
        // printf("\t\t\t\t\t\t\tDEBUG: %d\n",v->data[o]);
        return v->data[o];
}
