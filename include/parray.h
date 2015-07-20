#pragma once
#include <algorithm>
#include <map>
#include <memory>
#include <stdexcept>

namespace persist {

template <typename T, size_t N, bool> class array_iterator;

template <typename T, size_t N, class A = std::allocator<T>>
class parray {
public:
    typedef typename A::value_type value_type; 
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;
    typedef typename A::pointer pointer;
	typedef typename A::const_pointer const_pointer;
	
	typedef array_iterator<T, N, false> iterator;
	typedef array_iterator<T, N, true> const_iterator;

    parray(): version(0) {
    }

    parray(std::initializer_list<T> list) : parray() {
		std::copy_n(list.begin(), N, values.begin());
    }

    parray(const std::array<T, N>& array) : version(0), values(array) {
    }
/*
	reference lookup(size_type index, size_type version) {
	    return const_cast<reference>(
	    	   static_cast<const parray<T, N>&>(*this).lookup(index, version));
	}
*/
	const_reference lookup(size_type index, size_type version) const {
        if(this->version < version) {
        	throw std::out_of_range("version is not created yet"); // Is it container problem?
        }

		auto update_iterator = updates.find(index);
    	if (update_iterator != updates.end()) {
            auto& updatemap = update_iterator->second;
            auto most_recent_update = updatemap.upper_bound(version);
            if(most_recent_update != updatemap.begin()) {
            	return (--most_recent_update)->second;
            }
    	}
    	return values[index];
	}

	void update(size_type index, T value) {
       	++version;
       	auto& updatemap = updates[index];
       	updatemap[version] = value;
	}

    size_type most_recent_version(size_type index) const {
        auto update_iterator = updates.find(index);
    	if (update_iterator != updates.end()) {
            auto& updatemap = update_iterator->second;
            auto most_recent_update = updatemap.rbegin();
            if (most_recent_update != updatemap.rend()) {
                return most_recent_update->first;
            }
    	}
    	return 0;
    }

    iterator begin() {
        return iterator(*this, 0);
    }

    iterator end() {
        return iterator(*this, N);
    }

    const_iterator cbegin() const{
        return const_iterator(*this, 0);
    }

    const_iterator cend() const {
        return const_iterator(*this, N);
    }
	
 	bool operator==(const parray<T, N>& rhs) const {
 	    return version == rhs.version && values == rhs.values && updates == rhs.updates;
 	}
private:
	static_assert(N > 0, "array size must be > 0");
	typedef size_type version_type;	
	typedef std::map<version_type, T, std::less<version_type>, A> updatemap_type;

	std::array<T, N> values;
	std::map<size_type, updatemap_type, std::less<version_type>, A> updates;
	size_type version;
};
}

#include "parrayiter.h"
