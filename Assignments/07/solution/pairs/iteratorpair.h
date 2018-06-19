#include <iterator>
#include <algorithm>
#include <utility>

namespace std {
  namespace detail {
    template<class Iter, class T>
    class iteratorToRange;
    template<class Iter>
    decltype(auto)
    ibegin(pair<Iter, int> && p);
    template<class Iter>
    decltype(auto)
    iend(pair<Iter, int> && p);

    template<class Iter, class T>
    decltype(auto)
    make_pair_impl(
     Iter && iterator,
     T && offset,
     typename std::iterator_traits<Iter>::iterator_category) {
      return iteratorToRange<Iter, T>(iterator, offset);
    }

    template<class Iter, class T>
    class iteratorToRange{
      iteratorToRange() = delete;
      iteratorToRange(Iter begin, T offset)
      : _begin(begin)
      , _offset(offset)
      {}

    public:
      auto begin() {
        return detail::ibegin<Iter>(std::pair<Iter, T>(_begin, _offset));
      }

      auto end() {
        return detail::iend<Iter>(std::pair<Iter, T>(_begin, _offset));
      }

    private:
      Iter _begin   = nullptr;
      T    _offset  = 0;
    };

    template<class Iter>
    decltype(auto)
    ibegin(pair<Iter, int> && p) {
      return std::get<0>(p);
    }
    template<class Iter>
    decltype(auto)
    iend(pair<Iter, int> && p) {
      return std::advance(std::get<0>(p), std::get<1>(p));
    }

    // template<class Iter, class T>
    // decltype(auto)
    // make_pair_impl(
    //  Iter && iterator,
    //  T && offset,
    //  std::forward_iterator_tag) {
	  //   // Implementation for forward iterators
    //   return nullptr;
    // }
  }



  template<class Iter>
  std::pair<Iter, Iter>
  make_pair(Iter iterator, int offset) {
    return make_pair_impl(iterator, offset,  std::iterator_traits<Iter>::iterator_category);
  }



} // END namespace std
