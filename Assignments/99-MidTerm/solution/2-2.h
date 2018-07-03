
#include <vector>

namespace cpppc {
// Single chunk rows
class chunkIterator {};
template <int chunksizebytes, class ValueT, class Container> class chunk {

  chunk() { _row.reserve(chunksizebytes / (sizeof(ValueT) / 8)); }

private:
  std::vector<ValueT> _row;
};

// Outer layer for accessing
class chunksIterator {};
template <int chunksizebytes, class ValueT, class Container> class chunks {
public:
  using value_type = ValueT;
  using element_type = Container::const_iterator;

public:
  chunks() : chunks(Container()) {}
  chunks(Container &con) {}
  ~chunks() = default;

  Iterator begin(){return } Iterator end() {}

  value_type operator[](int index) {}

private:
  std::vector<element_type> _chunks;
};
} // namespace cpppc
