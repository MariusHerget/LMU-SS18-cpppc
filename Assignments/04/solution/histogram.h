#ifndef CPPPC__S03__HISTOGRAM_H__INCLUDED
#define CPPPC__S03__HISTOGRAM_H__INCLUDED

// Some headers you might find useful:
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iterator>


template <class Iter>
inline Iter histogram(Iter first, Iter last) {
    typedef typename std::iterator_traits<Iter>::value_type      value_t;
    typedef typename std::iterator_traits<Iter>::difference_type index_t;

    std::unordered_map<index_t, value_t> countOccur;

    std::for_each(first, last, [](value_t &n){  // Possible since it is in c++11
      countOccur[n]++;                       // add one for each occurrence of n
    });

    // build new vector which represents the occurences of each value
    // within the given Iterators
    auto ret = first;
    std::for_each(first, last, [](value_t &n){
        // Since countOccur addes new element if those occur in the memory it
        // is already in orden
        *ret = countOccur[n];
        ret++;
        countOccur.erase(n); // delete value since we have added it
    });
}

#endif // CPPPC__S03__HISTOGRAM_H__INCLUDED
