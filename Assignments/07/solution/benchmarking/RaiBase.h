template <class Derived, class value_type = typename Derived::value_type,
          class reference = value_type &, class const_reference = value_type &,
          class pointer = value_type *>
class RandomAccessIteratorBase {
private:
  using derived_t = Derived;
  using self_t = RandomAccessIteratorBase<Derived, value_type, reference,
                                          const_reference, pointer>;
  using size_type = std::size_t;
  using index_type = std::ptrdiff_t;
  using difference_type = std::ptrdiff_t;
  using index_t = index_type;

private:
  derived_t &derived() { return static_cast<derived_t &>(*this); }
  constexpr const derived_t &derived() const {
    return static_cast<const derived_t &>(*this);
  }

public:
  typedef std::random_access_iterator_tag iterator_category;

  typedef ValueType value_type;
  typedef index_type difference_type;
  typedef Pointer pointer;
  typedef const Pointer const_pointer;
  typedef Reference reference;
  typedef const Reference const_reference;

public:
  constexpr RandomAccessIteratorBase() = default;
  constexpr RandomAccessIteratorBase(self_t &&) = default;
  constexpr RandomAccessIteratorBase(const self_t &) = default;
  ~RandomAccessIteratorBase() = default;
  self_t &operator=(self_t &&) = default;
  self_t &operator=(const self_t &) = default;

  reference operator*() const { return derived().dereference(); }

  reference operator->() const { return derived().dereference(); }

  reference operator[](int pos) {
    // TODO test this    return *(derived().increment(pos));
    derived().increment(pos);
    return derived().dereference();
  }

  derived_t operator+(int offset) {
    derived().increment(offset);
    return derived();
  }

  derived_t operator-(int offset) {
    derived().decrement(offset);
    return derived();
  }

  difference_type operator-(const derived_t &rhs) const {
    return derived().pos() - rhs.pos();
  }

  bool operator==(const derived_t &rhs) const {
    return (derived().pos() == rhs.pos());
  }

  bool operator!=(const derived_t &rhs) const { return !(derived() == rhs); }

  bool operator<(const derived_t &rhs) const {
    return derived().pos() < rhs.pos();
  }

  bool operator>(const derived_t &rhs) const {
    return derived().pos() > rhs.pos();
  }

  bool operator<=(const derived_t &rhs) const {
    return derived().pos() <= rhs.pos();
  }

  bool operator>=(const derived_t &rhs) const {
    return derived().pos() >= rhs.pos();
  }

  // Pre-increment
  derived_t &operator++() {
    derived().increment(1);
    return derived();
  }

  // Post-increment
  derived_t operator++(int) {
    derived_t old(derived());
    derived().increment(1);
    return old;
  }

  derived_t &operator+=(difference_type rhs) {
    derived().increment(rhs);
    return derived();
  }

  // Pre-decrement
  derived_t &operator--() {
    derived().decrement(1);
    return derived();
  }

  // Post-decrement
  derived_t operator--(int) {
    derived_t old(derived());
    derived().decrement(1);
    return old;
  }

  derived_t &operator-=(difference_type rhs) {
    derived().decrement(rhs);
    return derived();
  }
};
