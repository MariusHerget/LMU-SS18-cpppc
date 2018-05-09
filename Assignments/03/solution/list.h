#ifndef CPPPC__A03__LIST_H__INCLUDED
#define CPPPC__A03__LIST_H__INCLUDED
#include <iterator>

namespace cpppc {


// list<int32_t, -1>
template <
        typename ValueT,
        ValueT default_value = ValueT()>
class list {
    typedef list<ValueT, default_value> self_t;
    typedef typename std::size_t size_type;
    public:
    // list<T>::iterator

    struct list_node {
            list_node * next;
            ValueT value;
    };

    class iterator {
          typedef typename
                  list<ValueT, default_value>
                  list_t;
          typedef typename
                  list_t::list_node
                  list_node_t;
          typedef typename
                  list_t::iterator
                  self_t;

          typedef typename difference_type ...;
          typedef typename
                  ValueT
                  value_type;
          typedef typename
                  value_type *
                  pointer;
          typedef typename
                  value_type &
                  reference;
          typedef typename
                  std::forward_iterator_tag
                  iterator_category;

          public:
          iterator() = delete;


          iterator(const list_t & list)
                  : _list(list)
          {
          }

          iterator & operator++() {
                  _list_node = _list_node->next;
                  return *this;
          }

          iterator operator++(int) {
                  iterator old = *this;
                  _list_node = _list_node->next;
                  return old;
          }

          const ValueT & operator*() const {
                  return _list_node->value;
          }

          ValueT & operator*() {
                  return _list_node->value;
          }

          bool operator==(const self_t & rhs) {
                  return  (this == &rhs ||  // identity
                           ( _list == rhs._list
                             // && ..
                           )
                           );
          }

          private:
          list_node_t * _list_node;
          list_t _list;
    };

    public:
    list()
            : _begin(iterator(*this))
            , _end(iterator(*this))
    {
    }

    // list<uint32_t>(list<int32_t>()) says 'nouh'
    list(const self_t & other)             = default;
    self_t & operator=(const self_t & rhs) = default;
    bool operator==(const self_t & rhs) {
            return  (this == &rhs ||  // identity
                     ( _begin == rhs._begin
                       && _end == rhs._end
                        // TODO
                     )
                     );
    }
    // list<int> l;
    // l_begin = l.begin();
    // ++l_begin;
    iterator begin()  {
            return _begin;
    }
    // list<T> l;
    // *l.end();
    iterator end()    {
            return _end;
    }

    inline const bool empty() const {
            if (_begin == _end) return true;
            else return false;
    }
    inline size_type size() const {
            return _end-_begin;
    }

    // vector__at
    inline ValueT & operator[](int index)  {
            if (index < 0 || static_cast<int>(this.size()) <= index) {
                    throw std::invalid_argument("index out of bounds");
            }
            for(int i=0; _begin != _end; ++i) {
              if (i == index) {
                return &_begin;
              }
              ++_begin;
            }
            throw std::invalid_argument("index could not be found");
            return default_value;
    }
    inline const ValueT & operator[](int index) const {
            if (index < 0 || static_cast<int>(this.size()) <= index) {
                    throw std::invalid_argument("index out of bounds");
            }
            for(int i=0; _begin != _end; ++i) {
              if (i == index) {
                return &_begin;
              }
              ++_begin;
            }
            throw std::invalid_argument("index could not be found");
            return default_value;
    }

    void push_back(ValueT val);
    ValueT pop_back();

    private:
    // same as = { }
    list_node _head        = { nullptr, default_value };
    static list_node _tail = { nullptr, default_value };

    // self_t * this

    iterator _begin = *this;
    iterator _end;
  };

  #include "list_impl.h"
}

#endif // CPPPC__A03__LIST_H__INCLUDED
