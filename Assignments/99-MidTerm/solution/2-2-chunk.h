
#include <iostream>
#include <stdexcept>
#include <vector>
namespace cpppc {
// Single chunk rows
template <int chunksizebytes, class ValueT, class Container>
class chunkIterator {
public:
  using size_t = std::size_t;
  chunkIterator() = default;
  ~chunkIterator() = default;

  chunkIterator(const Container &con, const int offset)
      : _con(con), _offset(offset) {}

  const ValueT operator*() const { return _con[_offset]; }

  const decltype(auto) data() const { return _con.data() + _offset; }

private:
  const Container &_con;
  int _offset;
};

template <int chunksizebytes, class ValueT, class Container> class chunk {
public:
  using value_type = ValueT;
  using Iterator = chunkIterator<chunksizebytes, ValueT, Container>;
  chunk(const Container &con, int offset) : _con(con), _offset(offset) {}

public:
  decltype(auto) data() const { return _con.data() + _offset; }

  decltype(auto) operator[](std::size_t index) const {
    if (index >= _size)
      throw std::out_of_range("Index is out of this chunks bounds.");
    return *(Iterator(_con, _offset + index));
  }

  Iterator begin() const { return Iterator(_con, _offset); }

  // const Iterator begin() const { return chunkIterator(); }

private:
  const int _size = chunksizebytes / (sizeof(ValueT));
  const Container &_con;
  int _offset;
};
} // namespace cpppc
