#ifndef CPPPC__S03__HISTOGRAM_H__INCLUDED
#define CPPPC__S03__HISTOGRAM_H__INCLUDED

// Some headers you might find useful:
#include <unordered_map> // nice hint
#include <set>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>


template <class Iter>
inline Iter histogram(Iter first, Iter last) {
        typedef typename std::iterator_traits<Iter>::value_type value_t;
        typedef typename std::iterator_traits<Iter>::difference_type index_t;

        // if (first == last) return last;

        std::unordered_map<index_t, value_t> countOccur;

        std::for_each(first,last,[&](value_t n){ // Possible since it is in c++11
                countOccur[n]++;             // add one for each occurrence of n
        });


        for (auto const& pair: countOccur) {
                std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }


        // build new vector which represents the occurences of each value
        // within the given Iterators
        auto ret = first;
        std::cout << "countOccur.size() is " << countOccur.size() << std::endl;
        std::for_each(first, last, [&](value_t n){
                // Since countOccur addes new element if those occur in the memory it
                // is already in orden
                if (countOccur.find(n) != countOccur.end()) { // check whether every element is used
                        *ret = countOccur[n];
                        ret++;
                        countOccur.erase(n); // delete value since we have added it
                }
        });


        // for (std::vector<value_t>::iterator it = first ; it != last; ++it) {
        //         for (int j = 0; j < sizeb; ++j)
        //             cout <<  "\t" << it;
        //         cout << endl;
        //     }

        return ret;
}

#endif // CPPPC__S03__HISTOGRAM_H__INCLUDED
