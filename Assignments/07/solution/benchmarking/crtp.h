template <class Derived> class AllHailCrtpVector {
private:
  using derived_t = Derived;

public:
  AllHailCrtpVector() = default;
  AllHailCrtpVector(std::vector<int64_t> *v) : array(v) {}
  void setArray(std::vector<int64_t> *v) { array = v; }

protected:
  auto getSquare(int index) const {
    array->at(index)++;
    return array->at(index) * array->at(index);
  }
  std::vector<int64_t> *array = nullptr;
};

class GoodVectorImpl : public AllHailCrtpVector<GoodVectorImpl> {
public:
  using AllHailCrtpVector<GoodVectorImpl>::AllHailCrtpVector;
  //
  int64_t get(int index) const { return getSquare(index) * 2; }
};
