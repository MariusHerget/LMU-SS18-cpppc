#ifndef CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
#define CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

// Might come in handy:
#include <unordered_map>
#include <iterator>
#include <stdexcept>
#include <algorithm>

namespace cpppc {

namespace detail {

template <class T, std::size_t N>
class sparse_array;

template <class SparseArrayT>
class sparse_array_proxy_ref;

template<typename T>
void swap(sparse_array_proxy_ref<T> p1, sparse_array_proxy_ref<T> p2)
{
        p1.swap(p2);
}
// ############################################################################
template <class SparseArrayT>
class sparse_array_iterator
{
private:
typedef sparse_array_iterator<SparseArrayT>     self_t;
typedef typename SparseArrayT::value_t value_t;
typedef std::size_t index_t;
typedef std::size_t size_t;


public:
using iterator_category = std::random_access_iterator_tag;
using value_type    = typename SparseArrayT::value_type;
using difference_type   = std::ptrdiff_t;
using reference   = value_type &;
using pointer     = value_type *;
using proxy_reference = typename SparseArrayT::proxy;
// public functions
public:
// Constructors
sparse_array_iterator() = default;
sparse_array_iterator(SparseArrayT * array, index_t index)
        : _array(array)
        , _index(index)
{
}
sparse_array_iterator(const self_t & other)
        : _array(other._array)
        , _index(other._index)
{
}
~sparse_array_iterator() = default;

// Operators
self_t & operator=(const self_t & other) = default;
proxy_reference operator*() {
        // return proxy_reference(*_array, _index);
        return (*_array)[_index];
}
self_t & operator++(){
        ++_index;
        return *this;
}
self_t & operator++(int) const {
        self_t old(*this);
        ++_index;
        return old;
}
self_t & operator--() {
        --_index;
        return *this;
}
self_t & operator--(int) const {
        self_t old(*this);
        --_index;
        return old;
}
self_t & operator+=(int offset) {
        _index += offset;
        return *this;
}
self_t operator+(int offset) const {
        self_t res(*this);
        res += offset;
        return res;
}
self_t operator-=(int offset) {
        _index -= offset;
        return *this;
}
self_t operator-(int offset) const {
        self_t res(*this);
        res -= offset;
        return res;
}

difference_type operator-(self_t other){
        return (_index - other._index);
}

bool operator==(const self_t & other) const noexcept {
        return ( this == &other
                 || (_array == other._array && _index == other._index)
                 );
}
bool operator!=(const self_t & other) const noexcept {
        return !(*this == other);
}
const proxy_reference operator*() const {
        // return proxy_reference(*_array, _index);
        return _array->at(_index);
}
proxy_reference operator->() {
        return _array->at(_index);
}
const proxy_reference & operator->() const {
        return _array->at(_index);
}
proxy_reference operator[](difference_type offset){
        _index += offset;
        return _array->at(_index);
}

bool operator<(const self_t & other) const {
        printf("\n!!! DEBUG sparse_array_iterator operator<(const self_t & other) const %lu\n",(other._index - (*this)._index));
        return (other._index - (*this)._index > 0);
}
bool operator>(const self_t & other) const {
        return (other<(*this));
}
bool operator<=(const self_t & other) const {
        return !(*this > other);
}
bool operator>=(const self_t & other) const {
        return !(*this < other);
}

private:
// Member
SparseArrayT *  _array;
size_t _index;
}; // END sparse_array_iterator

// ############################################################################
template <class SparseArrayT>
class sparse_array_proxy_ref

{
typedef sparse_array_proxy_ref<SparseArrayT>    self_t;
using value_type =  typename SparseArrayT::value_type;
using index_t = typename SparseArrayT::index_t;

public:
sparse_array_proxy_ref() = delete;
sparse_array_proxy_ref(SparseArrayT & sa, index_t offset)
        : _sa(sa), _index(offset) {
}
sparse_array_proxy_ref(const self_t & other)
        : _sa(other._sa)
        , _index(other._index)
{
}

self_t & operator=(self_t other)  {
        printf("\n!!! DEBUG sparse_array_proxy_ref operator=(self_t other)\n");
        if (&other != this) {
                _sa = other._sa;
                _index = other._index;
        }
        return *this;
}

value_type operator=(const value_type &value) {
        // printf("!");
        // printf("!!! DEBUG sparse_array_proxy_ref operator=(const value_type &value) %d\n", value);
        _sa._data[_index] = value;
        if(value_type() == value) {
                this->_sa._data.erase(_index);
                return value_type();
        }
        this->_sa._data[_index] = value;
        return value;
        // auto it = _sa._data.find(_index);
        // if (it  == _sa._data.end())
        //         _sa._data.insert({_index, value});
        // else
        //         it->second = value;
        // return value
}

self_t operator--(){
        if((this->_sa._data[_index] -1) == value_type()) {
                this->_sa._data.erase(_index);
        }
        else{
                this->_sa._data[_index] -= 1;
        }
        return *this;
}

operator const value_type &() const {
        auto iter = _sa._data.find(_index);
        if (iter == _sa._data.end()) {
                return _sa._default;
        }
        return iter->second;
}

bool operator==(const value_type & other) const {
        return static_cast<const value_type &>(*this) == other;
}

bool operator!=(const value_type & other) const {
        return static_cast<const value_type &>(*this) != other;
}

void swap(self_t & other) {
        std::swap(*this, other);
}

private:
SparseArrayT & _sa;
index_t _index;
}; // END sparse_array_proxy_ref

} // namespace detail

// ############################################################################
template <class T, std::size_t N>
class sparse_array
{
// Just a suggestion:

typedef sparse_array<T, N>                      self_t;
typedef detail::sparse_array_proxy_ref<self_t>  proxy_reference;
typedef std::size_t size_t;
typedef T value_t;
typedef detail::sparse_array_proxy_ref<self_t>  proxy;
typedef std::unordered_map<size_t, T> data;

public:
typedef size_t index_t;
typedef detail::sparse_array_iterator<self_t>   iterator;
typedef detail::sparse_array_iterator<const self_t> const_iterator;
typedef index_t difference_type;
typedef T value_type;
typedef T&           reference;
typedef const T&         const_reference;
typedef value_type*          pointer;
typedef const pointer const_pointer;
typedef std::reverse_iterator<iterator>    reverse_iterator;
typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

friend iterator;
friend const_iterator;
friend proxy;

public:
// Constructors
sparse_array()
        : _sizeA(N)
{
}
// Copy
sparse_array(const self_t & other) = default;
// Destructor
~sparse_array()                    = default;
// Standard functions
bool             empty() const {
        return (size()==0);
}
size_t           size()  const {
        return _sizeA;
}
size_t           max_size()  const {
        return size();
}

// Iterators
iterator         begin()     {
        return iterator(this, 0);
}
const iterator   end()       {
        return iterator(this, size());
}
iterator         rbegin()             {
        return iterator(this, size()-1);
}
const_iterator cbegin() const {
        return const_iterator(this, 0);
}
const_iterator cend() const {
        return const_iterator(this, size());
}
const_iterator crbegin() const {
        return const_iterator(this, size()-1);
}


// Front/Back
value_t &         front()  const {
        return *begin();
}
value_t  &        back()  const {
        return *rbegin();
}
proxy_reference front() {
        return proxy_reference(*this, 0);
}

proxy_reference back() {
        return proxy_reference(*this, size()-1);
}
// Operators
self_t & operator=(const self_t & other) {
        if (_sizeA < other._sizeA) {
                throw std::invalid_argument("Size out of bounds");
        }
        _data = other._data;
        return *this;
}
bool operator!=(const self_t & other) const noexcept {
        return !(*this == other);
}
bool operator==(self_t & other) noexcept {
        return _data == other._data;
}
const bool operator==(const self_t & other) const noexcept {
        return _data == other._data;
}

bool operator<(const self_t & other) const {
        // return ((other._sizeA - _sizeA) > 0);
        // return std::lexicographical_compare(cbegin(), cend()
        //                                     ,other.cbegin(), other.cend()
        //                                     );
        if((*this) == other)
                return false;

        return std::lexicographical_compare(cbegin(), cend(), other.cbegin(), other.cend());
}
bool operator>(const self_t & other) const {
        return !(*this < other);
}
bool operator<=(const self_t & other) const {
        return !(*this > other);
}
bool operator>=(const self_t & other) const {
        return !(*this < other);
}

value_t operator[](index_t index) const {
        if (index >= _sizeA || index < 0) {
                throw std::invalid_argument("Index out of bounds");
        }
        auto it_match = _data.find(index);
        if (it_match == _data.end()) {
                return _default;
        }
        return it_match->second;
}

proxy_reference operator[](index_t offset) {
        if (offset >= _sizeA || offset < 0) {
                throw std::invalid_argument("Index out of bounds");
        }
        return proxy_reference(*this, offset);
}

// functions
void fill(const value_type & value){
        if(value == value_type()) {
                _data.clear();
        }
        else{
                std::fill(begin(), end(), value);
        }
}
void swap(self_t & other){
        std::swap(_data, other._data);
}
// void swap(self_t & other) {
// std::swap_ranges(_data.begin(), _data.end(), other._data.begin(), other._data.end());
// }

private:
size_t _sizeA = 0;
std::unordered_map<index_t, value_t> _data;
value_t _default;
}; // END sparse_array

} // namespace cpppc

#endif // CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
