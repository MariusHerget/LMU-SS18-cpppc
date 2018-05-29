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
  class sparse_array; // Forwarddeclaration

  template <class SparseArrayT>
  class sparse_array_proxy_ref;

// template<class T>
// void swap(sparse_array_proxy_ref<T> p1, sparse_array_proxy_ref<T> p2)
// {
//         p1.swap(p2);
// }
// // Maybe
// template <class T, std::size_t N>
// void swap(sparse_array<T, N> p1, sparse_array<T, N> p2) {
//         p1.swap(p2);
// }
// ############################################################################

  template <class SparseArrayT>
  class sparse_array_iterator
	  {
private:
	  using index_t = typename SparseArrayT::index_t;
	  using self_t = sparse_array_iterator<SparseArrayT>;
	  using proxy_reference = sparse_array_proxy_ref<SparseArrayT>;
	  typedef std::size_t size_t;


public: // Needed for STL algorithms
	  using iterator_category = std::random_access_iterator_tag;
	  using value_type = typename SparseArrayT::value_type;
	  using pointer = value_type *;
	  using reference = proxy_reference;
	  using const_reference = const value_type &;
	  using difference_type = typename SparseArrayT::difference_type;
// public functions
public:
// Constructors
	  sparse_array_iterator() = default; // Iterator muss default constructable sein!
	  sparse_array_iterator(SparseArrayT * array, index_t index)
		  : _array(array)
		  , _index(index)
		  , _swapindex(index)
		  {
		  }
	  ~sparse_array_iterator() = default;

// Operators
	  self_t & operator=(const self_t & other) = default;
	  proxy_reference operator*() {
		  // return (*_array)[_index];
		  return proxy_reference(*_array, _index);
		  }
	  const_reference operator*() const {
		  auto iter = _array->_data.find(_index);
		  if (iter == _array->_data.end()) {
			  return _array->def;
			  }
		  return iter->second;
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
	  self_t & operator+=(const difference_type offset) {
		  _index += offset;
		  return *this;
		  }
	  self_t operator+(const difference_type offset) const {
		  return self_t(_array, _index + offset);
		  }
	  self_t operator-=(const difference_type offset) {
		  _index -= offset;
		  return *this;
		  }
	  self_t operator-(const difference_type offset) const {
		  return self_t(_array, _index - offset);
		  }

	  difference_type operator-(self_t & other){
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
// proxy_reference operator->() {
//         return _array->at(_index);
// }
// const proxy_reference & operator->() const {
//         return _array->at(_index);
// }
	  proxy_reference operator[](difference_type offset){
		  // _index += offset;
		  // return _array->at(_index);

		  return proxy_reference(_array, offset);
		  }

	  bool operator<(const self_t & other) const {
		  printf("\n!!! DEBUG sparse_array_iterator operator<(const self_t & other) const %lu\n",(other._index - (*this)._index));
		  bool ret = proxy_reference(*_array, _index, _swapindex) < proxy_reference(*other._array, other._index);
		  _swapindex++;
		  return ret;
		  }
	  bool operator>(const self_t & other) const {
		  return proxy_reference(*_array, _index) > proxy_reference(*other._array, other._index);
		  }
// BACKUP
// bool operator<(const self_t & other) const {
//         // printf("\n!!! DEBUG sparse_array_iterator operator<(const self_t & other) const %lu\n",(other._index - (*this)._index));
//         return _index < other._index;
// }
// bool operator>(const self_t & other) const {
//         return _index > other._index;
// }
	  bool operator<=(const self_t & other) const {
		  return !(*this > other);
		  }
	  bool operator>=(const self_t & other) const {
		  return !(*this < other);
		  }

	  index_t _swapindex;
private:
// Member
	  SparseArrayT * _array;
	  size_t _index;
	  }; // END sparse_array_iterator

// ############################################################################
  template <class SparseArrayT>
  class sparse_array_proxy_ref

	  {
	  typedef sparse_array_proxy_ref<SparseArrayT> self_t;
	  using value_type =  typename SparseArrayT::value_type;
	  using index_t = typename SparseArrayT::index_t;

public:
	  sparse_array_proxy_ref() = delete; // REFERENCE ist niemals default constructable
	  sparse_array_proxy_ref(SparseArrayT & sa, index_t offset)
		  : _sa(sa), _index(offset) {
		  }
	  sparse_array_proxy_ref(SparseArrayT & sa, index_t offset, index_t swapindex)
		  : _sa(sa), _index(offset), _swapindex(swapindex) {
		  }
	  sparse_array_proxy_ref(const self_t & other) = default;

	  self_t & operator=(self_t other)  {
		  // printf("\n!!! DEBUG sparse_array_proxy_ref operator=(self_t other)\n");
		  if (&other != this) {
			  _sa = other._sa;
			  _index = other._index;
			  }
		  return *this;
		  }


	  void operator=(const value_type &value) {
		  // printf("!");
		  // printf("!!! DEBUG sparse_array_proxy_ref operator=(const value_type &value) %d\n", value);
		  auto it = _sa._data.find(_index);
		  if (it  == _sa._data.end())
			  _sa._data.insert({_index, value});
		  else
			  it->second = value;
		  }

	  bool operator<(const self_t & rhs) const {
		  printf("\n!!! DEBUG sparse_array_proxy_ref operator<(const self_t & other) const %d (%d) < %d (%d)  = %d\n", _sa.at(_index), _index, rhs._sa.at(rhs._index), rhs._index, ret);
		  bool ret = _sa.at(_index) < rhs._sa.at(rhs._index);
		  printf("\n!!! DEBUG sparse_array_proxy_ref operator<(const self_t & other) const %d (%d) < %d (%d)  = %d\n", _sa.at(_index), _index, rhs._sa.at(rhs._index), rhs._index, ret);
		  return ret;
		  }

	  bool operator>(const self_t & rhs) const {
		  bool ret = _sa.at(_index) > rhs._sa.at(rhs._index);
		  printf("\n!!! DEBUG sparse_array_proxy_ref operator>(const self_t & other) const %d > %d   = %d\n", _sa.at(_index), rhs._sa.at(rhs._index), ret);
		  return ret;
		  }

// self_t operator--(){
//         if((this->_sa._data[_index] -1) == value_type()) {
//                 this->_sa._data.erase(_index);
//         }
//         else{
//                 this->_sa._data[_index] -= 1;
//         }
//         return *this;
// }

// operator const value_type &() const {
//         auto iter = _sa._data.find(_index);
//         if (iter == _sa._data.end()) {
//                 return _sa._default;
//         }
//         return iter->second;
// }

// bool operator==(const value_type & other) const {
//         return static_cast<const value_type &>(*this) == other;
// }
//
// bool operator!=(const value_type & other) const {
//         return static_cast<const value_type &>(*this) != other;
// }

	  void swap(self_t & other) {
		  printf("\n!!! DEBUG sparse_array_proxy_ref swap  %d / %d", _swapindex, other._index);
		  value_type tmp = _sa.at(_swapindex);
		  auto it = _sa._data.find(_swapindex);
		  it->second = other._sa.at(other._index);
		  auto ito = _sa._data.find(other._index);
		  ito->second = tmp;
		  printf("\n!!! DEBUG sparse_array_proxy_ref swap2 %d / %d", tmp, other._sa.at(other._index));
		  other._sa = _sa;
		  // std::swap(*this, other);
		  }

	  operator value_type() const { // conversion
		  return _sa.at(_index);
		  }

// DEBUG
	  index_t _swapindex;
private:
	  SparseArrayT & _sa;
	  index_t _index;
	  }; // END sparse_array_proxy_ref

  } // namespace detail

// ############################################################################
template <class T, std::size_t N>
class sparse_array
	{
	using self_t = sparse_array<T, N>;
	using proxy_reference = typename detail::sparse_array_proxy_ref<self_t>;
	using const_proxy_reference =
		      typename detail::sparse_array_proxy_ref<const self_t>;
	using value_t = T;

public:
	using index_t = int;
	using value_type = T;
	using iterator = detail::sparse_array_iterator<self_t>;
	using const_iterator = detail::sparse_array_iterator<const self_t>;
	using difference_type = index_t;
	using reference = proxy_reference;
	using const_reference = const value_type &;
	using size_type = size_t;

	friend iterator;
	friend proxy_reference;
	friend const_proxy_reference;

public:
// Constructors
	sparse_array()
		: _sizeA(N)
		{
		}
// Copy
	sparse_array(const self_t & other) = default;
// Move
	sparse_array(self_t && other) = default;
//Assign
	self_t & operator=(const self_t & other) = default;
// {
//         if (_sizeA < other._sizeA) {
//                 throw std::invalid_argument("Size out of bounds");
//         }
//         _data = other._data;
//         return *this;
// }
// Move Assign
	self_t & operator=( self_t && other) = default;
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
	iterator         rend()             {
		return iterator(this, -1);
		}
	const_iterator rbegin() const {
		return iterator(this, size() - 1);
		}

	const_iterator rend() const {
		return iterator(this, -1);
		}

	const_iterator begin() const {
		return const_iterator(this, 0);
		}

	const_iterator end() const {
		return const_iterator(this, size());
		}

	const_iterator cbegin() const {
		return const_iterator(this, 0);
		}

	const_iterator cend() const {
		return const_iterator(this, size());
		}

// Front/Back
	const_reference front()  const {
		return *begin();
		}
	const_reference back()  const {
		return *rbegin();
		}
	proxy_reference front() {
		return proxy_reference(*this, 0);
		}

	proxy_reference back() {
		return proxy_reference(*this, size()-1);
		}
// Operators
	bool operator!=(const self_t & other) const noexcept {
		return !(*this == other);
		}
	bool operator==(const self_t & other) const noexcept {
		if (this == &other) {
			return true;
			}
		// printf("\n!!! DEBUG sparse_array == Size %d / %d, default %d / %d\n", size(), other.size(), _default, other._default);
		if (size() != other.size()) {
			return false;
			}
		// return std::equal(_data.begin(), _data.end(), other._data.begin());
		return (_data == other._data);
		}
// const bool operator==(const self_t & other) const noexcept {
//         return _data == other._data;
// }

	bool operator<(const self_t & other) const {
		// return ((other._sizeA - _sizeA) > 0);
		// return std::lexicographical_compare(cbegin(), cend()
		//                                     ,other.cbegin(), other.cend()
		//                                     );
		if((*this) == other)
			return false;

		return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
		}
	bool operator>(const self_t & other) const {
		return std::lexicographical_compare(other.begin(), other.end(), begin(), end());
		}
	bool operator<=(const self_t & other) const {
		return !(*this > other);
		}
	bool operator>=(const self_t & other) const {
		return !(*this < other);
		}

	const_reference operator[](index_t index) const {
		// if (index >= _sizeA || index < 0) {
		//         throw std::invalid_argument("Index out of bounds");
		// }
		return sparseValue(index);
		}

	proxy_reference operator[](index_t offset) {
		// if (offset >= _sizeA || offset < 0) {
		//         throw std::invalid_argument("Index out of bounds");
		// }
		return proxy_reference(*this, offset);
		}
	const_reference at(index_t index) const {
		// if (index >= _sizeA || index < 0) {
		//         throw std::invalid_argument("Index out of bounds");
		// }
		return sparseValue(index);
		}


// functions
	void fill(const value_t & value){
		if(value == value_t()) {
			_data.clear();
			}
		else{
			std::fill(begin(), end(), value);
			}
		}
	void swap(self_t & other){
		printf("\n!!! DEBUG sparse_array swap %d / %d", size(), other.size());
		_data.swap(other._data);
		std::swap(_sizeA, other._sizeA);
		std::swap(_default, other._default);
		}
	index_t debug_search (const value_t value) {
		index_t index = 0;
		for (auto i : _data) {
			if (i.second == value) return index;
			index++;
			}
		return index;
		}
// void sort() {
//         difference_type index = 0;
//         for (auto i : _data) {
//                 _data[index] = *i;
//                 _data.erase(i);
//         }
// }
// void swap(self_t & other) {
// std::swap_ranges(_data.begin(), _data.end(), other._data.begin(), other._data.end());
// }

private:
	const_reference sparseValue(index_t index) const {
		if (_data.find(index) != _data.end()) {
			return _data.at(index);
			}
		return _default;
		}


private:
	size_t _sizeA = 0;
	std::unordered_map<index_t, value_t> _data {};
	value_t _default {};
	}; // END sparse_array

template<typename T>
void swap(detail::sparse_array_proxy_ref<T> p1, detail::sparse_array_proxy_ref<T> p2)
	{
	printf("!!! DEBUG before proxy swap \n");
	p1.swap(p2);
	}
} // namespace cpppc

#endif // CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
