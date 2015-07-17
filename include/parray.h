#pragma once
#include <algorithm>
#include <map>
#include <memory>
#include <stdexcept>

namespace persist {

template <typename T, size_t N> class array_iterator;
template <typename T, size_t N> class array_const_iterator;

template <typename T, size_t N, template <typename T> class _Alloc = std::allocator>
class parray {
public:
	typedef _Alloc<T> A; 
    typedef typename A::value_type value_type; 
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;
    typedef typename A::pointer pointer;
	
	typedef array_iterator<T, N> iterator;
	typedef array_const_iterator<T, N> const_iterator;

    parray() {
    }

    parray(std::initializer_list<T> list) {
		std::copy_n(list.begin(), N, values.begin());
    }

    parray(const std::array<T, N>& array) : values(array) {
    }
/*
	reference lookup(size_type index, size_type version) {
	    return const_cast<reference>(
	    	   static_cast<const parray<T, N>&>(*this).lookup(index, version));
	}
*/
	const_reference lookup(size_type index, size_type version) const {
        if(this->version < version) {
        	throw std::out_of_range("version is not created yet");
        }
		auto update_iterator = updates.find(index);
    	if (update_iterator != updates.end()) {
            auto updatemap = update_iterator->second;
            auto most_recent_update = updatemap.lower_bound(version);
            if (most_recent_update->first <= version) {
                return most_recent_update->second;
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
	typedef size_t version_type;
	
	template <typename VT> 
	using map_allocator_type = _Alloc<std::pair<const version_type, VT>>;
	
	typedef std::map<version_type, T, std::less<version_type>, map_allocator_type<T>> updatemap_type;

	std::array<T, N> values;
	std::map<size_type, updatemap_type, std::less<version_type>, map_allocator_type<updatemap_type>> updates;
	size_type version;
};
}

#include "parrayiter.h"
