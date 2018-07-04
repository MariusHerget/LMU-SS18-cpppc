
#include "2-2-chunk.h"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <vector>
namespace cpppc {
// Outer layer for accessing

template <int chunksizebytes, class ValueT, class Container> class chunks {
public:
  class chunksIterator {
  private:
    int _size = chunksizebytes / (sizeof(ValueT));

  public:
    using self_t = chunksIterator;
    using iterator_category = std::random_access_iterator_tag;
    // using reference = value_type &;
    // using pointer = value_type *;
    using difference_type = std::ptrdiff_t;

  public:
    chunksIterator(const Container &con) : _con(con), _pos(0) {}
    chunksIterator(const Container &con, int position)
        : _con(con), _pos(position) {}
    chunksIterator(const self_t &rhs) : _con(rhs._con), _pos(rhs._pos) {}
    self_t &operator++() {
      _pos++;
      return *this;
    }

    self_t operator++(int) {
      auto tmp = *this;
      _pos++;
      return tmp;
    }

    self_t operator--() {
      _pos--;
      return *this;
    }

    self_t operator--(int) {
      auto tmp = *this;
      _pos--;
      return tmp;
    }

    decltype(auto) operator-(self_t &rhs) { return _pos - rhs._pos; }

    // Compare
    bool operator==(self_t &rhs) { return (this == &rhs || _pos == rhs._pos); }

    bool operator!=(self_t &rhs) { return !(*this == rhs); }

    constexpr ValueT operator*() const { return _con[_pos * _size]; }

    decltype(auto) begin() const {
      return value_type(_con, _pos * _size).begin();
      // return 5;
    }

    const ValueT operator[](std::size_t index) const {
      return _con[_pos * _size + index];
    }

  private:
    const Container &_con;
    int _pos;
  };

  const int _size = chunksizebytes / (sizeof(ValueT));
  using value_type = cpppc::chunk<chunksizebytes, ValueT, Container>;
  using Iterator = chunksIterator;

public:
  // chunks() : chunks(Container()) {}
  chunks() = delete;
  chunks(const Container &con) : _con(con) {}
  ~chunks() = default;

  Iterator begin() { return Iterator(_con, 0); }
  Iterator end() { return Iterator(_con, size()); }

  const value_type operator[](std::size_t index) const {
    return value_type(_con, index * _size);
  }

  std::size_t size() { return _con.size(); }

private:
  const Container &_con;
};
} // namespace cpppc

// All const
