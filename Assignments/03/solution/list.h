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
        ListIterator() = delete;

        ListIterator(list_node_t & node)
                : _list_node(&node)
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

        ListIterator & operator++() {
                _list_node = _list_node->next;
                return *this;
        }

        ListIterator operator++(int) {
                iterator old = *this;
                _list_node = _list_node->next;
                return old;
        }

        const ValueT & operator*() const {
                return _list_node->value;
        }

        ListIterator operator=(const ListIterator & rhs){
                if(!(this == &rhs)) {
                        _list_node = rhs._list_node;
                }
                return *this;
        }

        ValueT & operator*() {
                return _list_node->value;
        }

        bool operator==(const self_t & rhs) const {
                return  (this == &rhs ||  // identity
                         ( _list_node == rhs._list_node &&
                           _list_node->value == rhs._list_node->value));
        }

        bool operator!=(self_t & rhs) {
                return !(this == &rhs ||  // identity
                         ( _list_node == rhs._list_node &&
                           _list_node->value == rhs._list_node->value));
        }

        private:
        // list_t * _list = 0;
// list_node_t * _list_node;
        list_node * _node = nullptr
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
        : _begin(iterator(_head))
        , _end(iterator(_head))
{
}

// list<uint32_t>(list<int32_t>()) says 'nouh'
list(const self_t & other)             = default;
self_t & operator=(const self_t & rhs) = default;


public:
iterator         begin()              { return iterator(_head); }
iterator         end()                { return _end; }
const_reference  begin() const        { _begin; }
const_reference  end()   const        { _end; }

size_type        size()  const        {
        printf("\n!!! DEBUG Size() %d / %d\n", _end, _begin);
        return end() - begin();
}
bool             empty() const        { return (size()==0); }
bool operator==(self_t & rhs);
value_type & operator[](int index) ;

// Since I do  not know how to implement push_back I will implemented
// push_front.
void push_front(ValueT value);
ValueT pop_front();

// Like std::list<T>::insert
void insert(iterator & position, ValueT value);


private:
  // list_node * _list_node  = nullptr;
  iterator    _begin      = *this;
  iterator    _end        = iterator(nullptr);


};// END CLASS list
#include "list_impl.h"
} // END namespace
