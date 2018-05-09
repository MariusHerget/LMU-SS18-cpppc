#include <iterator>

namespace cpppc {
  // list<int32_t, -1>
  template <
    typename ValueT,
    ValueT   default_value = ValueT()>
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
       ValueT      value;
    };
    // list<T>::ListIterator
    class ListIterator {
       typedef //typename
         list<ValueT, default_value>
         list_t;
       typedef typename
         list_t::list_node
         list_node_t;
       typedef typename
         list_t::ListIterator
         self_t;

         // TODO
         // - Iterator traits  (terator tags)
         // - STL iterator concept
         // --> ForwardIterator
    public:
       ListIterator() = delete;

       ListIterator(list_t * lis)
       : _list(lis)
       , _list_node(0)
       { }

       ListIterator(list_node_t * node, list_t * list)
       : _list_node(node)
       ,  _list(list)
       { }

       self_t & operator+(int index) {
               if (index < 0 || static_cast<int>(_list->size()) <= index) {
                       throw std::invalid_argument("index out of bounds");
               }
               self_t it = static_cast<self_t>(*this);
               for (int i=0; it != _list->_end; it++) {
                  if (index == i) break;
                  i++;
               }
               return it;
       }

       self_t & operator++() {
          _list_node = _list_node->next;
          return *this;
       }

       self_t operator++(int) {
          ListIterator old = *this;
          _list_node = _list_node->next;
          return old;
       }

       const ValueT & operator*() const {
         return _list_node->value;
       }

       ValueT & operator*() {
         return _list_node->value;
       }

       bool operator==(self_t & rhs) {
         printf("\n !! DEBUG iterator==\n");
         if (static_cast<self_t>(*this)._list_node != 0 && rhs._list_node != 0)
           if (static_cast<self_t>(*this)._list_node->next != nullptr
                && rhs._list_node->next != nullptr)
               return  (this == &rhs || // identity
                        ( _list == rhs._list
                       && ++static_cast<self_t>(*this) == ++rhs
                       && static_cast<self_t>(*this)._list_node->value == rhs._list_node->value   )
                       );
            else return this->_list_node->value == rhs._list_node->value;
          else  return  true;
       }
       bool operator!=(self_t & rhs) {
         printf("\n !! DEBUG iterator!=\n");
         if (static_cast<self_t>(*this)._list_node != 0 && rhs._list_node != 0)
           if (static_cast<self_t>(*this)._list_node->next != nullptr
                && rhs._list_node->next != nullptr)
               return  !(this == &rhs || // identity
                        ( _list == rhs._list
                       && ++static_cast<self_t>(*this) == ++rhs
                       && static_cast<self_t>(*this)._list_node->value == rhs._list_node->value   )
                       );
            else return !(this->_list_node->value == rhs._list_node->value);
          else  return false;
       }

       bool operator==(const self_t & rhs) const {
         // printf("\n !! DEBUG const iterator==\n");
         self_t itt= static_cast<self_t>(*this);
         self_t itrhs= static_cast<self_t>(rhs);
         return  (this == &rhs || // identity
                   // ( //_list == rhs._list &&
                   //   _sameNodes(rhs) ) ||
                   ( ++itt == ++itrhs  )
                 );
       }

    private:
       list_node_t * _list_node;
       list_t * _list;
       // bool _sameNodes(const self_t & rhs) {
       //   bool same = true;
       //    while(self_t(this->_list_node->next, _list) != _list->_end){
       //      if(!this->_list_node->next().equals(rhs._list_node.next())){
       //        same = false;
       //        break;
       //      }
       //    }
       // }
    }; // CLASS ListIterator

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
  public:
    list()
    : _begin(ListIterator(this))
    , _end(ListIterator(this))
    { }

    list(const self_t & other)             = default;
    self_t & operator=(const self_t & rhs) = default;

    iterator         begin()              { _begin; }
    iterator         end()                { _end; }
    const_reference  begin() const        { _begin; }
    const_reference  end()   const        { _end; }
    size_type        size()  const        {
            printf("\n!!! DEBUG Size() %d / %d\n", _end, _begin);
            return end() - begin();
    }
    bool             empty() const        { return (size()==0); }
    bool operator==(self_t & rhs);
    bool operator==(const self_t & rhs) const;
    value_type & operator[](int index) ;
    // Herget Implementation
    void push_back(const ValueT& val);
    value_type pop_back();

  private:
    // same as = { }
    list_node _head        = { nullptr, default_value };
    list_node _tail        = { nullptr, default_value };

    // self_t * this

    iterator  _begin = ListIterator(& _head, this);
    iterator  _end;
  }; // CLASS list

  #include "list_impl.h"

} // END NAMESPACE cpppc
