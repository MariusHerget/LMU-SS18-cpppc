#include <iterator>
#include <functional>
#include <algorithm>


namespace cpppc {
namespace detail {
template<class LazySequence>
class lazy_sequence_iterator {
using self_t = lazy_sequence_iterator<LazySequence>;
using lazy_seq_t = LazySequence;
using size_t = std::size_t;
using size_type = std::size_t;

public:
using iterator_category = std::random_access_iterator_tag;
using value_type = typename LazySequence::value_type;
using pointer = typename LazySequence::pointer;
using reference = typename LazySequence::reference;
using difference_type = std::ptrdiff_t;

public:
lazy_sequence_iterator() = default;
~lazy_sequence_iterator() = default;

lazy_sequence_iterator(const lazy_seq_t & seq, size_t pos)
        : _seq(&seq)
        , _pos(pos)
{}
lazy_sequence_iterator(const self_t &other)
        : _seq(other._seq)
        , _pos(other._pos)
{}

value_type operator*() const {            return (*_seq)[_pos]; }
value_type operator[](int offset) const { return (*_seq)[_pos + offset]; }

self_t & operator++(){
        ++_pos;
        return *this;
}
self_t operator++(int) {
        auto old = *this;
        ++_pos;
        return old;
}

self_t & operator+=(int offset){
        _pos += offset;
        return *this;
}
self_t & operator+(int offset){
        auto it = *this;
        it += offset;
        return it;
}

difference_type operator-(const self_t & rhs) const {
        return (rhs._pos - _pos);
}

bool operator==(const self_t rhs) const {
        return _pos == rhs._pos && _seq == rhs._seq;
}

bool operator!=(const self_t rhs) const {
        return !(*this == rhs);
}

private:
const lazy_seq_t *    _seq=nullptr;
size_t _pos =0;
};
}


template<class T>
class lazy_sequence {
using self_t = lazy_sequence<T>;
using value_t = T;
using size_t = std::size_t;
using difference_type = std::ptrdiff_t;


public:
using size_type = std::size_t;
using value_type = T;
using iterator = detail::lazy_sequence_iterator<const self_t>;
using const_iterator = detail::lazy_sequence_iterator<const self_t>;
using reference = const T &;
using cont_reference = const T &;
using pointer = const T *;
using cont_pointer = const T *;


public:
lazy_sequence() = default;
~lazy_sequence() = default;

lazy_sequence(int size, std::function<T(int)> fun)
        : _size(size)
        , _fun(fun)
{
}

lazy_sequence(const self_t & other) = default;
lazy_sequence(self_t && other) = default;

self_t & operator=(const self_t & rhs) = default;
self_t & operator=( self_t && rhs) = default;

const_iterator begin() const {
        return const_iterator(*this, 0);
}

const_iterator end() const {
        return const_iterator(*this, _size);
}

size_type size() {  return _size; }
bool empty() const {      return size() == 0; }

value_t operator[](int offset) const {
        return _fun(offset);
}

bool operator==(const self_t & rhs) const {
        if (this == &rhs) {return true;}
        if (_size != rhs._size) {return false;}
        return std::equal(begin(), end(), rhs.begin());
}

bool operator!=(const self_t & rhs) const {
        return !(*this == rhs);
}

value_type front() const {
      return *begin();
}

value_type back() const {
      return *(begin() + (_size -1));
}


private:
int _size;
std::function<value_t(int)> _fun;
}; // END CLASS lazy_sequence
} // NAMEspace cpppc
