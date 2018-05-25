#include <iterator>

namespace cpppc {

// template<typename ValueT, ValueT default_value> class list;
template <
        typename ValueT,
        ValueT default_value = ValueT()>
class list {
typedef
        list<ValueT, default_value>
        self_t;
typedef typename
        std::size_t
        size_type;
public:

struct list_node {
        list_node * next;
        ValueT value;
};

class ListIterator {
typedef typename
        //list<ValueT, default_value>
        list::self_t
        list_t;
typedef typename
        list_t::list_node
        list_node_t;
typedef typename
        list_t::ListIterator
        self_t;
public:
using iterator_category = std::forward_iterator_tag;
using value_type = ValueT;
using difference_type = std::ptrdiff_t;
using pointer = value_type *;
using reference = value_type &;

ListIterator() = delete;

ListIterator(list_node_t * node)
        : _node(node)
{
}

self_t & operator+(int index) {
        self_t it = static_cast<self_t>(*this);
        for (int i=0; i <= index; it++) {
                if (index == i) break;
                i++;
        }
        return it;
}

self_t & operator++() {
        _node = _node->next;
        return *this;
}

self_t operator++(int) {
        iterator old = *this;
        _node = _node->next;
        return old;
}

const ValueT & operator*() const {
        return _node->value;
}

self_t operator=(const self_t & rhs){
        if(!(this == &rhs)) {
                _node = rhs._node;
        }
        return *this;
}

ValueT & operator*() {
        return _node->value;
}

bool operator==(const self_t & rhs) const {
        return  (this == &rhs ||                // identity
                 ( _node == rhs._node));
}

bool operator!=(const self_t rhs) const {
        return !(*this == rhs);
}

private:
list_node_t * _node;
}; // END CLASS iterator

public:
typedef
        ValueT
        value_type;
typedef
        ListIterator
        iterator;
typedef
        const ListIterator
        const_iterator;
typedef
        value_type &
        reference;
typedef
        const value_type &
        const_reference;
list()
{
        // printf("\n!!!DEBUG called default constructor\n");
}

// copy
list(const self_t & other)             = default;
// assignment
self_t & operator=(const self_t & other) {
        // printf("\n!!!DEBUG called assign operator\n");
        if (this != &other)
        {
                // Free the existing resource.
                while (!empty()) {pop_front();}

                // Copy all nodes
                // _head = nullptr;
                int size=other.size();
                for (int i=size; i>0; i--) {
                        push_front(other[i-1]);
                }
        }
        return *this;
};
self_t & operator=(self_t && other) {
        // printf("\n!!!DEBUG called Move-Assignment operator %lu\n",other._size);
        if (this != &other)  {
                // Clean up own list
                while (!empty()) {pop_front();}
                // Steal others data
                _head = other._head;
                _size = other._size;
                // Prepare Other for destructor
                other._head = nullptr;
                other._size = 0;
        }
        return *this;

};
// destructor
~list() = default;
// MOVE
list(self_t&& other)
        : _head(other._head)
        , _size(other._size)
{
        // printf("\n!!!DEBUG called Move constructor %lu\n\n", other._size);
        other._head = NULL;
        other._size = 0;
}


public:
iterator         begin()              {
        return iterator(_head);
}
iterator         end()                {
        return iterator(NULL);
}
const_iterator  begin() const {
        return iterator(_head);
}
const_iterator  end()   const {
        return iterator(NULL);
}

size_type        size()  const {
        return _size;
}
bool             empty() const {
        return (size()==0);
}
bool operator==(self_t & rhs);
ValueT & operator[](const int index);
const ValueT & operator[](const int index) const;

// Since I do  not know how to implement push_back I will implemented
// push_front.
void push_front(ValueT value);
ValueT pop_front();
const ValueT & front() const {
        return _head->value;
}

// Like std::list<T>::insert
void insert(iterator & position, ValueT value);


private:
list_node * _head = NULL;    // = &_tail;
size_t _size = 0;


};// END CLASS list
#include "list_impl.h"
} // END namespace
