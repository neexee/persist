#pragma once
#include <ostream>
#include "parray.h"

namespace persist {

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& stream, const parray<T, N>& array) {
	stream << "[";
	auto last = --array.cend();
	for (auto it = array.cbegin(); it != last; ++it) {
        stream << *it << ", ";
	}
	stream << *last  << "]";
    return stream;
}
}
