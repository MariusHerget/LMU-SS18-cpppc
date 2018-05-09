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

    // template <
    //         typename ValueT,
    //         ValueT default_value = ValueT()>
    class iterator {
        private:
        typedef           //typename
                cpppc::list<ValueT, default_value>
                list_t;
        typedef typename
                list_t::list_node
                list_node_t;
        typedef typename
                list_t::iterator
                self_t;

        public:
        typedef
                int
                difference_type;
        typedef           //typename
                ValueT
                value_type;
        typedef           // typename
                value_type *
                pointer;
        typedef           //typename
                value_type &
                reference;
        typedef typename
                std::forward_iterator_tag
                iterator_category;

        public:
        iterator() = delete;


        iterator(list_t * list)
                : _list(list)
        {
        }

        iterator(list_t * list, list_node_t * node)
                : _list(list)
                , _list_node(node)
        {
        }

        iterator & operator++() {
                // printf("\n DEBUG START iterator ++()\n");
                if (_list_node->next != nullptr)
                  _list_node = _list_node->next;
                return *this;
        }

        iterator operator++(int) {
                printf("\n DEBUG START iterator ++(int)\n");
                iterator old = *this;
                if (_list_node->next != nullptr)
                  _list_node = _list_node->next;
                return old;
        }

        // // @fuchsto: Is this implententation necessary???
        iterator operator+(int go) {
                for (int i=0; i<go; i++)
                      _list_node = _list_node->next;
                return *this;
        }

        // // @fuchsto: Is this implententation necessary???
        iterator operator-(int go) {
                for (int i=0; i<go; i++)
                      _list_node = _list_node->next;
                return *this;
        }

        const ValueT & operator*() const {
                return _list_node->value;
        }

        ValueT & operator*() {
                return _list_node->value;
        }

        bool operator==(const self_t & rhs) const {
                return  (this == &rhs ||            // identity
                         ( _list == rhs._list
                           && _list_node == rhs._list_node
                         )
                         );
        }
        bool operator!=(const self_t & rhs) const {
                return !(this == &rhs ||       // identity
                         ( _list == rhs._list
                           && _list_node == rhs._list_node
                         )
                         );
        }

        private:
        list_node_t * _list_node = nullptr;
        list_t * _list;
    };     // END iterator

    public:
    list()
            : _begin(iterator(this))
            , _end(iterator(this))
    {
    }

    ~list() {
        // list_node* tmp;
        // for (; _begin != _end; _begin++) {
        //         tmp = _head;
        //         _head = _head->next;
        //         delete tmp;
        // }
    }

    // list<uint32_t>(list<int32_t>()) says 'nouh'
    list(const self_t & other)             = default;
    self_t & operator=(const self_t & rhs) = default;
    bool operator==(const self_t & rhs) const {
            printf("\n DEBUG START list==    %d / %d\n",size(), rhs.size());
            if (this == &rhs) return true; // identity
            if( empty() && rhs.empty()) return true;
            iterator tmp = _begin;
            if(size() == rhs.size()) {
              for (int i=0; tmp != _end; ++tmp) {
                printf("\nDEBUG list==     %d == %d   ",(*tmp),rhs[i]);
                if (*tmp != rhs[i]) return false;
                i++;
              }
              return true;
            }
            else return false;
            // printf("\n DEBUG END list==\n");
            return false;
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
            if (size() == 0) return true;
            else return false;
    }
    inline size_type size() const {
            printf("\n DEBUG START size()\n");
            typename iterator::difference_type n = std::distance(_begin, _end);
            printf("DEBUG size() %d\n",n);
            return n;
    }

    // vector__at
    inline ValueT operator[](int index)  {
            printf("\n DEBUG START operator[]\n");
            if (index < 0 || static_cast<int>(std::distance(_begin, _end)) <= index) {
                    throw std::invalid_argument("index out of bounds");
            }
            iterator tmpit = _begin;
            for(int i=0; tmpit != _end; ++i) {
                    if (i == index) {
                            return *tmpit;
                    }
                    ++tmpit;
            }
            throw std::invalid_argument("index could not be found");
            return default_value;
    }
    inline const ValueT & operator[](int index) const {
            printf("\n DEBUG START const operator[]\n");
            if (index < 0 || static_cast<int>(std::distance(_begin, _end)) <= index) {
                    throw std::invalid_argument("index out of bounds");
            }
            iterator tmpit = _begin;
            for(int i=0; tmpit != _end; ++i) {
                    if (i == index) {
                            return *tmpit;
                    }
                    ++tmpit;
            }
            throw std::invalid_argument("index could not be found");
            return default_value;
    }

    void push_back(ValueT val);
    ValueT pop_back();
    ValueT erase_after(iterator it);

    private:
    // same as = { }
    list_node _head         = { nullptr, default_value };
    list_node _tail         = { nullptr, default_value };

    // self_t * this

    iterator _begin = this;
    iterator _end;
};

  #include "list_impl.h"
}

#endif // CPPPC__A03__LIST_H__INCLUDED
