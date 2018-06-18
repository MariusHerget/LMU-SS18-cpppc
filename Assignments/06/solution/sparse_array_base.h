#ifndef CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
#define CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

// Might come in handy:
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <unordered_map>

namespace cpppc {

namespace detail {

// Forward declaration
  template <class T, std::size_t N>
  class sparse_array;
// Forward declaration
  template <class SparseArrayT>
  class sparse_array_proxy_ref;

  template <
	  class Derived,
	  class value_type = typename Derived::value_type,
	  class reference = value_type &,
	  class const_reference  = value_type &,
	  class pointer = value_type *>
  class RandomAccessIteratorBase {
	  private:
		  using derived_t  = Derived;
		  using self_t     = RandomAccessIteratorBase<
			   Derived,
			   value_type,
			   reference,
			   const_reference,
			   pointer >;
		  using size_type  = std::size_t;
		  using index_type = std::ptrdiff_t;
		  using difference_type = std::ptrdiff_t;
		  using index_t    = index_type;

		  // using proxy_reference = typename derived_t::proxy_reference;
		  // using T = typename derived_t::SparseArrayT;

		  derived_t & derived() {
			  return static_cast<derived_t &>(*this);
		  }
		  constexpr const derived_t &derived() const {
			  return static_cast<const derived_t &>(*this);
		  }

	  public:
		  using iterator_category = std::random_access_iterator_tag;

	  private:
		  index_t _pos;

	  protected:
		  constexpr RandomAccessIteratorBase() = delete;

	  public:
		  constexpr RandomAccessIteratorBase(self_t &&) = default;
		  constexpr RandomAccessIteratorBase(const self_t &) = default;
		  ~RandomAccessIteratorBase() = default;
		  self_t &operator=(self_t &&) = default;
		  self_t &operator=(const self_t &) = default;

		  constexpr explicit RandomAccessIteratorBase(index_type position)
			  : _pos(position) {
		  }

		  constexpr index_type pos() const {
			  return _pos;
		  }

	  public:
		  derived_t &operator++() {
			  _pos++;
			  return derived();
		  }
		  derived_t &operator++(int) const {
			  self_t old(*this);
			  _pos++;
			  return old;
		  }
		  derived_t &operator--() {
			  _pos--;
			  return derived();
		  }
		  derived_t &operator--(int) const {
			  self_t old(*this);
			  _pos--;
			  return old;
		  }
		  derived_t &operator+=(const difference_type offset) {
			  _pos += offset;
			  return derived();
			  // return derived();
		  }
		  derived_t operator+(const difference_type offset) const {
			  return derived_t(derived(), _pos + offset);
		  }
		  derived_t operator-=(const difference_type offset) {
			  _pos -= offset;
			  return derived();
		  }
		  derived_t operator-(const difference_type offset) const {
			  return derived_t(derived(), _pos - offset);
		  }
		  constexpr derived_t operator+(const derived_t &rhs) const {
			  return _pos + rhs._pos;
		  }
		  constexpr derived_t operator-(const derived_t &rhs) const {
			  return _pos - rhs._pos;
		  }

		  bool operator==(const self_t &rhs) const noexcept {
			  return _pos == rhs._pos;
		  }
		  bool operator!=(const self_t &rhs) const noexcept {
			  return !(*this == rhs);
		  }
		  constexpr reference operator*() const {
			  return derived().dereference();
		  }
		  derived_t operator*() {
			  return derived().dereference();
		  }

		  derived_t operator[](difference_type offset) {
			  return derived().dereference(offset);
		  }

		  bool operator<(const derived_t &other) const {
			  return derived().dereference() < derived().dereference(other);
		  }
		  bool operator>(const derived_t &other) const {
			  return derived().dereference() > derived().dereference(other);
		  }
		  bool operator<=(const derived_t &other) const {
			  return !(*this > other);
		  }
		  bool operator>=(const derived_t &other) const {
			  return !(*this < other);
		  }
  };

  template <class SparseArrayT>
  class sparse_array_iterator
	      : public RandomAccessIteratorBase<
			sparse_array_iterator<SparseArrayT>,
			typename SparseArrayT::value_type,
			typename SparseArrayT::reference,
			typename SparseArrayT::const_reference,
			typename SparseArrayT::pointer
			>
  {
	  private:
		  using index_t = typename SparseArrayT::index_t;
		  using self_t  = sparse_array_iterator<SparseArrayT>;
		  using base_t  = RandomAccessIteratorBase<
			   sparse_array_iterator<SparseArrayT>,
			   typename SparseArrayT::value_type,
			   typename SparseArrayT::reference,
			   typename SparseArrayT::const_reference,
			   typename SparseArrayT::pointer
			   >;

	  public:
		  using iterator_category = typename base_t::iterator_category;
		  using value_type        = typename base_t::value_type;
		  using difference_type   = typename base_t::difference_type;
		  using proxy_reference   = typename base_t::proxy_reference;
		  using const_reference   = typename base_t::const_reference;

	  public:
		  // Constructors
		  sparse_array_iterator() =
		   default; // Iterator muss default constructable sein!
		  sparse_array_iterator(SparseArrayT *array, index_t index)
			  : _array(array), base_t(index) {
		  }
		  // Since we only this constructor while using const function we can Copy
		  // the pointer
		  sparse_array_iterator(const self_t &other, index_t index)
			  : _array(other._array), base_t(index) {
		  }
		  ~sparse_array_iterator() = default;

	  public:
		  // base
		  proxy_reference dereference() {
			  return proxy_reference(*_array, _index);
		  }
		  proxy_reference dereference(difference_type offset) {
			  return proxy_reference(*_array, offset);
		  }
		  proxy_reference dereference(const self_t &other) {
			  return proxy_reference(*other._array, other._index);
		  }
		  const_reference dereference() const {
			  auto iter = _array->_data.find(_index);
			  if (iter == _array->_data.end()) {
			     return _array->_default;
			     }
			  return iter->second;
		  }
		  const_reference dereference(const self_t &other) const {
			  auto iter = other._array->_data.find(other._index);
			  if (iter == other._array->_data.end()) {
			     return other._array->_default;
			     }
			  return iter->second;
		  }

	  public:
		  bool operator==(const self_t &rhs) const {
			  return (base_t::operator==(rhs) && (_array == rhs._array));
		  }
		  // Operators
		  self_t &operator=(const self_t &other) = default;

	  private:
		  // Member
		  SparseArrayT *_array;
		  size_t _index;
  }; // END sparse_array_iterator

// ############################################################################
  template <class SparseArrayT>
  class sparse_array_proxy_ref

  {
	  typedef sparse_array_proxy_ref<SparseArrayT> self_t;
	  using value_type = typename SparseArrayT::value_type;
	  using index_t = typename SparseArrayT::index_t;

	  public:
		  sparse_array_proxy_ref() =
		   delete; // REFERENCE ist niemals default constructable
		  sparse_array_proxy_ref(SparseArrayT &sa, index_t offset)
			  : _sa(sa), _index(offset) {
		  }
		  sparse_array_proxy_ref(const self_t &other) = default;

		  self_t &operator=(self_t other) {
			  if (&other != this) {
			     _sa = other._sa;
			     _index = other._index;
			     }
			  return *this;
		  }

		  void operator=(const value_type &value) {
			  auto it = _sa._data.find(_index);
			  if (it == _sa._data.end())
				  _sa._data.insert({_index, value});
			  else
				  it->second = value;
		  }

		  bool operator<(const self_t &rhs) const {
			  bool ret = _sa.at(_index) < rhs._sa.at(rhs._index);
			  return ret;
		  }

		  bool operator>(const self_t &rhs) const {
			  bool ret = _sa.at(_index) > rhs._sa.at(rhs._index);
			  return ret;
		  }

		  void swap(self_t &other) {
			  value_type tmp = _sa.at(_index);
			  auto it = _sa._data.find(_index);
			  it->second = other._sa.at(other._index);
			  auto ito = _sa._data.find(other._index);
			  ito->second = tmp;
			  other._sa = _sa;
		  }

		  operator value_type() const { // conversion
			  return _sa.at(_index);
		  }

		  // DEBUG
	  private:
		  SparseArrayT & _sa;
		  index_t _index;
  }; // END sparse_array_proxy_ref

} // namespace detail

// ############################################################################
template <class T, std::size_t N> class sparse_array {
	using self_t                = sparse_array<T, N>;
	using proxy_reference       =
	  typename detail::sparse_array_proxy_ref<self_t>;
	using const_proxy_reference =
	  typename detail::sparse_array_proxy_ref<const self_t>;
	using value_t = T;

	public:
		using index_t         = int;
		using value_type      = T;
		using iterator        = detail::sparse_array_iterator<self_t>;
		using const_iterator  = detail::sparse_array_iterator<const self_t>;
		using difference_type = index_t;
		using reference       = proxy_reference;
		using const_reference = const value_type &;
		using size_type       = size_t;
		using pointer       = value_type *;

		friend iterator;
		friend proxy_reference;
		friend const_proxy_reference;

	public:
		// Constructors
		sparse_array() : _sizeA(N) {
		}
		// Copy
		sparse_array(const self_t &other) = default;
		// Move
		sparse_array(self_t &&other) = default;
		// Assign
		self_t & operator=(const self_t &other) = default;
		// Move Assign
		self_t & operator=(self_t &&other) = default;
		// Destructor
		~sparse_array() = default;
		// Standard functions
		bool empty() const {
			return (size() == 0);
		}
		size_t size() const {
			return _sizeA;
		}
		size_t max_size() const {
			return size();
		}

		// Iterators
		iterator begin() {
			return iterator(this, 0);
		}
		const iterator end() {
			return iterator(this, size());
		}
		iterator rbegin() {
			return iterator(this, size() - 1);
		}
		iterator rend() {
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
		const_reference front() const {
			return *begin();
		}
		const_reference back() const {
			return *rbegin();
		}
		proxy_reference front() {
			return proxy_reference(*this, 0);
		}

		proxy_reference back() {
			return proxy_reference(*this, size() - 1);
		}
		// Operators
		bool operator!=(const self_t &other) const noexcept {
			return !(*this == other);
		}
		bool operator==(const self_t &other) const noexcept {
			if (this == &other) {
			   return true;
			   }
			if (size() != other.size()) {
			   return false;
			   }
			return (_data == other._data);
		}

		bool operator<(const self_t &other) const {
			if ((*this) == other)
				return false;

			return std::lexicographical_compare(begin(), end(), other.begin(),
				other.end());
		}
		bool operator>(const self_t &other) const {
			return std::lexicographical_compare(other.begin(), other.end(), begin(),
				end());
		}
		bool operator<=(const self_t &other) const {
			return !(*this > other);
		}
		bool operator>=(const self_t &other) const {
			return !(*this < other);
		}

		const_reference operator[](index_t index) const {
			return sparseValue(index);
		}

		proxy_reference operator[](index_t offset) {
			return proxy_reference(*this, offset);
		}
		const_reference at(index_t index) const {
			return sparseValue(index);
		}

		// functions
		void fill(const value_t &value) {
			if (value == value_t()) {
			   _data.clear();
			   } else {
			    std::fill(begin(), end(), value);
			    }
		}
		void swap(self_t &other) {
			_data.swap(other._data);
			std::swap(_sizeA, other._sizeA);
			std::swap(_default, other._default);
		}
		index_t debug_search(const value_t value) {
			index_t index = 0;
			for (auto i : _data) {
			    if (i.second == value)
				    return index;
			    index++;
			    }
			return index;
		}

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

template <typename T>
void swap(detail::sparse_array_proxy_ref<T> p1,
 detail::sparse_array_proxy_ref<T> p2) {
	p1.swap(p2);
}
} // namespace cpppc

#endif // CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
