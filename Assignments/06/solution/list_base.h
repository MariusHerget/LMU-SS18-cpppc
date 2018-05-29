#include <iterator>

namespace cpppc {
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
      using list_node_t = list_node;

      template <class Derived>
      class ForwardIteratorBase {
private:
	  using derived_t = Derived;
	  using self_t = ForwardIteratorBase <Derived>;
	  derived_t & derived() {
	      return static_cast<derived_t &>(*this);
	      }
	  constexpr const derived_t & derived() const {
	      return static_cast<const derived_t &>(*this);
	      }
public:
	  using iterator_category = std::forward_iterator_tag;
	  using value_type = ValueT;
	  using difference_type = std::ptrdiff_t;
	  using pointer = value_type *;
	  using reference = value_type &;

protected: // evtl protected
	  ForwardIteratorBase() = default;
public:
	  self_t & operator+(int index) {
	      auto it = self_t(*this);
	      for (int i=0; i <= index; it++) {
		  if (index == i) break;
		  i++;
		  }
	      return *this;
	      }
	  self_t & operator++() {
	      derived().increment(1);
	      return *this;
	      }
	  self_t operator++(int) {
	      auto old = *this;
	      derived().increment(1);
	      return old;
	      }
	  const ValueT & operator*() const {
	      return derived().dereference();
	      }
	  ValueT & operator*() {
	      return derived().dereference();
	      }
	  bool operator!=(const self_t rhs) const {
	      return !(*this == rhs);
	      }
	  bool operator==(const self_t & rhs) const {
	      return  (this == &rhs);
	      }
	  };



      // template <class T>
      class ListIterator
	      : public ForwardIteratorBase<ListIterator>
	  {
	  using list_t = typename list::self_t;
	  using list_node_t = list::list_node_t;
	  using self_t = ListIterator;
	  using base_t = ForwardIteratorBase<ListIterator>;
	  using value_type = ValueT;

public:
	  ListIterator() = delete;
	  ListIterator(list_node_t * node)
	      : _node(node)
	      // , ForwardIteratorBase(0)
	      {
	      }
	  ~ListIterator() = default;
	  // Copy
	  ListIterator(self_t & rhs) = default;
	  // // Move
	  ListIterator(self_t && rhs) = default;
	  // Assignment
	  self_t & operator=(const self_t &rhs) = default;
	  // Move-Assignment
	  self_t & operator=(self_t &&rhs) = default;


	  value_type &  dereference() {
	      return _node->value;
	      }
	  void increment(int offset) {
	      for (int i=0; i < offset; i++)
		  _node = _node->next;
	      }
	  bool operator==(const self_t & rhs) const {
	      return (base_t::operator==(rhs) ||
	              ( _node == rhs._node));
	      }
// void decrement(int offset) { increment(-offset); }

private:
	  list_node_t * _node = nullptr;
	  };



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
	  return iterator {_head};
	  }
      iterator         end()                {
	  return iterator {nullptr};
	  }
      const_iterator  begin() const {
	  return iterator {_head};
	  }
      const_iterator  end()   const {
	  return iterator {nullptr};
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
      list_node_t * _head = NULL; // = &_tail;
      size_t _size = 0;


      };// END CLASS list
#include "list_impl_base.h"
  } // END namespace
