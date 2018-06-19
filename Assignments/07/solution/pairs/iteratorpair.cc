#include "iteratorpair.h"

int main () {
	std::vector<std::string> v {
		"Monday", "Tuesday", "Wednesday",
		"Thursday", "Brainfryday", "Saturday", "Sunday"
	};
	auto range = std::make_pair(v.begin(), 6);
	auto test = std::begin(range);
	for (const auto & value : range) {
	    std::cout << value << '\n';
	    }
	return 0;
}
