#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <random>

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
	return searchSumSorted(std::begin(range), std::end(range), sum);
}


template<class ItStart, class ItEnd, class T>
bool searchSumUnsorted(ItStart && first, ItEnd && last, T sum) {
	// --last;
	// Fill unoredered map with number and count how many times it is present
	//  --> Performance boost in find if many elements are duplicated
	//  --> already searching for duplicated elements which form the sum
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
	    // If element finds itself: Only possible solution is that 2*element=sumtmp
	    // --> already checked in fill
	    // --> no other solution for this element --> return false
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
	//      if( map.find(sum - p.first) != map.end()
	//      && map.find(sum - p.first)->first != p.first) {
	//              mapfind = true;
	//              }
	// });
	// return mapfind;
}

template<class Range, class T>
decltype(auto)HasPairWithSumUnsorted(Range && range, T sum) {
	return searchSumUnsorted(std::begin(range), std::end(range), sum);
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

	// First create an instance of an engine.
	std::random_device rnd_device;
	// Specify the engine and distribution.
	std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
	std::uniform_int_distribution<int> dist {1, 100};

	auto gen = [&dist, &mersenne_engine](){
		 return dist(mersenne_engine);
	 };

	std::vector<int> vec(10000000);
	std::generate(std::begin(vec), std::end(vec), gen);

	std::cout << "Unsorted 1: " << HasPairWithSumUnsorted(v_unsorted_1, 8)
	          << '\n';
	std::cout << "Unsorted 2: " << HasPairWithSumUnsorted(v_unsorted_2, 8)
	          << '\n';
	std::cout << "Unsorted 3: " << HasPairWithSumUnsorted(v_unsorted_3, 8)
	          << '\n';
	std::cout << "Unsorted 4: " << HasPairWithSumUnsorted(vec, 8)
	          << "\n\nRandom vector: ";

	// std::for_each(std::begin(vec),
	//  std::end(vec),
	//  [](int v){
	// 	 	std::cout << v << " ";
	//  });
}
