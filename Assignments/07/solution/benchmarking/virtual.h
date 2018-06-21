class ShameOnVirtualVector {
protected:
  std::vector<int64_t> * array = nullptr;
public:
  ShameOnVirtualVector() = default;
  virtual int64_t get(int index) const = 0;

  void setArray(std::vector<int64_t> * v) {
    array = v;
  }
protected:
  auto getSquare(int index) const {
    return array->at(index) * array->at(index);
  }
};

// template <class T, class C>
class BadVectorImpl : public ShameOnVirtualVector {//<T, C> {
public:
  int64_t get(int index) const { return getSquare(index) * 2; }
};
