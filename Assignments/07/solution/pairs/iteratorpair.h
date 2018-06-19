#include <iterator>
#include <algorithm>
#include <utility>
#include <iostream>

namespace std {
  template<class Iter,
  class = typename std::iterator_traits<Iter>::iterator_category>
  decltype(auto)
  begin(pair<Iter, int> &p) {
	  return std::get<0>(p);
  }
  template<class Iter,
  class = typename std::iterator_traits<Iter>::iterator_category>
  decltype(auto)
  end(pair<Iter, int> &p) {
	  auto & it = std::get<0>(p);
	  std::advance(it, std::get<1>(p));
	  return it;
  }


  template<class Iter,
  class = typename std::iterator_traits<Iter>::iterator_category>
  std::pair<Iter, int> make_pair(Iter && iterator, int offset) {
	  return std::pair<Iter, int>(iterator, offset);
  }



} // END namespace std
