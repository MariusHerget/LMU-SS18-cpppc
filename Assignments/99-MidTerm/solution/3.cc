// Thanks to https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/enable-if
#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <stdlib.h> /* srand, rand */
#include <string>
#include <time.h> /* time */
#include <utility>
#include <vector>

// First try: compiler errors since int is ambigious
// template <class T>
// typename std::enable_if<std::is_integral<T>::value, T>::type log10(T t) {
//   return std::log(t);
// }
//
// template <class T>
// typename std::enable_if<std::is_arithmetic<T>::value, T>::type log10(T t) {
//   return std::log(std::sqrt(t));
// }

// Second try: works!
template <class T>
void log10(typename std::enable_if<std::is_integral<T>::value>::type t) {
  std::cout << std::log(t) << '\n';
}
template <class T>
void log10(typename std::enable_if<std::is_arithmetic<T>::value>::type t) {
  std::cout << std::log(std::sqrt(t)) << '\n';
}

template <class T>
void print_walk(T begin, T end, std::input_iterator_tag, auto print) {
  std::cout << "InputIterator: ";
  std::for_each(begin, end, print);
}

template <class T>
void print_walk(T begin, T end, std::bidirectional_iterator_tag, auto print) {
  std::cout << "BidirectionalIterator: ";
  std::reverse(begin, end);
  std::for_each(begin, end, print);
}

template <class T>
void print_walk(T begin, T end, std::random_access_iterator_tag, auto print) {
  // Random enough?
  std::random_shuffle(begin, end);
  std::cout << "RandomAccessIterator: ";
  std::for_each(begin, end, print);
}

template <class T> void print_walk(T begin, T end) {
  auto print = [](const int &n) { std::cout << " " << n; };
  print_walk(begin, end, typename std::iterator_traits<T>::iterator_category(),
             print);
  std::cout << '\n';
}

int main() {
  std::cout << log10(1.23) << '\n';
  std::cout << log10(10) << '\n';
  std::cout << log10('t') << '\n'; // Works as well! -> is this intended?

  // ForwardIterator
  std::forward_list<int> flist({1, 2, 3});
  // BidirectionalIterator
  std::list<int> bilist({1, 2, 3});
  // RandomAccessIterator
  std::vector<int> rivector({1, 2, 3, 4, 5, 6, 7, 8, 9});
  print_walk(std::begin(flist), std::end(flist));
  print_walk(std::begin(bilist), std::end(bilist));
  print_walk(std::begin(rivector), std::end(rivector));
  return 1;
}
