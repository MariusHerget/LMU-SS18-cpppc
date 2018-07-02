// Thanks to https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/enable-if
#include <algorithm>
#include <iostream>
#include <utility>
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
T log10(typename std::enable_if<std::is_integral<T>::value>::type t) {
  return std::log(t);
}
template <class T>
T log10(typename std::enable_if<std::is_arithmetic<T>::value>::type t) {
  return std::log(std::sqrt(t));
}

int main() {
  std::cout << log10(1.23) << '\n';
  std::cout << log10(10) << '\n';
  return 1;
}
