#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <boost/foreach.hpp>

// Googles Solution:
bool GoogleHasPairWithSum(const std::vector<int> data, int sum) {
	std::unordered_set<int> comp;
	for (int value : data) {
	    if (comp.find(value)!=comp.end()) return true;
	    comp.insert(sum-value);
	    }
	return false;
}

// Improvements: Use iterators over an unordered set to search for pais:
template<class ItStart, class ItEnd, class T>
bool searchSumSorted(ItStart && first, ItEnd && last, T sum) {
	//( Iterator last is behind the last element -> decrease to last -> name now correct)
	--last;
	while (first != last) {
	      auto sumtmp = *first + *last;
	      if (sumtmp == sum) {
		 return true;
		 }
	      if (sumtmp < sum) {
		 ++first;
		 } else {
		  --last;
		  }
	      }
	return false;
}

// we want to work with ranges:
template<class Range, class T>
decltype(auto)HasPairWithSumSorted(Range && range, T && sum) {
	return searchSumSorted(range.begin(), range.end(), sum);
}


template<class ItStart, class ItEnd, class T>
bool searchSumUnsorted(ItStart && first, ItEnd && last, T sum) {
	// --last;
	// Fill unoredered map with number and count how many times it is present
	//  --> Performance boost if many elements are duplicated
	std::unordered_map<T, std::size_t> map;
	for (auto it = first; it != last; ++it) {
	    auto itm = map.find(*it);
	    if (itm == map.end()) {
	       //Move insertion -> Any performance incresement?
	       // map.insert(std::make_pair<T, std::size_t>(*it,1));
	       //  Does not work -> Why?
	       map.insert({*it,1});
	       }
	    else {
				if (sum/2 == *it) return true;
				itm->second++;
				}
	    }


	for (const std::pair<T, std::size_t> &p : map) {
		if( map.find(sum - p.first) != map.end()
			&& map.find(sum - p.first)->first != p.first) {
			        return true;
				}
	}
	return false;


// SLOWER since it need to iterate over all elements in map
	// bool mapfind = false;
	// std::for_each(map.begin(),map.end(),
	//  [&](const std::pair<T, std::size_t> &p){
	// 	if( map.find(sum - p.first) != map.end()
	// 	&& map.find(sum - p.first)->first != p.first) {
	// 	        mapfind = true;
	// 		}
	// });
	// return mapfind;
}

template<class Range, class T>
decltype(auto)HasPairWithSumUnsorted(Range && range, T sum) {
	return searchSumUnsorted(range.begin(), range.end(), sum);
}

int main() {
	std::vector<int> v_sorted_1 {1, 2, 4, 9};
	std::vector<int> v_sorted_2 {1, 2, 4, 4};

	std::cout << "Googles Solution: \n";
	std::cout << "Sorted 1: " << GoogleHasPairWithSum(v_sorted_1, 8) << '\n';
	std::cout << "Sorted 2: " << GoogleHasPairWithSum(v_sorted_2, 8) << '\n';
	std::cout << "Own Solution: \n";
	std::cout << "Sorted 1: " << HasPairWithSumSorted(v_sorted_1, 8) << '\n';
	std::cout << "Sorted 2: " << HasPairWithSumSorted(v_sorted_2, 8) << '\n';


	std::vector<int> v_unsorted_1 {2, 9, 1, 4};
	std::vector<int> v_unsorted_2 {2, 4, 1, 4};
	std::vector<int> v_unsorted_3 {2, 3, 1, 5};

	std::cout << "Unsorted 1: " << HasPairWithSumUnsorted(v_unsorted_1, 8)
	          << '\n';
	std::cout << "Unsorted 2: " << HasPairWithSumUnsorted(v_unsorted_2, 8)
	          << '\n';
	std::cout << "Unsorted 3: " << HasPairWithSumUnsorted(v_unsorted_3, 8)
	          << '\n';
}
