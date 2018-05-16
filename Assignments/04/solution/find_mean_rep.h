#ifndef CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
#define CPPPC__S03__FIND_MEAN_REP_H__INCLUDED

// Some headers you might find useful:
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

namespace cpppc {

template <class Iter>
Iter find_mean_rep(Iter first, Iter last) {
        typedef typename std::iterator_traits<Iter>::value_type value_t;

        auto dist = std::distance(first, last);
        value_t sum = std::accumulate(first, last, 0);
        if (dist != 0 ) {
                auto median = sum / dist;
                auto medforiter = std::accumulate(std::next(first),
                                                  last,
                                                  *first,
                                                  [=](value_t old, value_t current) {
                                if(std::abs(median-old) < std::abs(median-current)) {
                                        return old;
                                } else {
                                        return current;
                                }
                        });

                return std::find(first, last, medforiter);

        }
        else
                return first;


}
} // namespace cpppc

#endif // CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
