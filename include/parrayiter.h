#pragma once

namespace persist {

template <typename T, size_t N, bool is_const_iterator = true>
class array_iterator  : public std::iterator<std::bidirectional_iterator_tag, T> { 
    typedef parray<T, N> C;
public:
    typedef typename C::value_type value_type;
    typedef typename C::size_type size_type;
    typedef typename C::difference_type difference_type;
    typedef typename std::conditional<is_const_iterator, typename C::const_pointer, typename C::pointer>::type pointer;
    typedef typename std::conditional<is_const_iterator, typename C::const_reference, typename C::reference>::type reference;
    typedef typename std::conditional<is_const_iterator, const C&, C&>::type data_reference;
    
    array_iterator() {
    }
    
    array_iterator(data_reference array, size_type index) : array(array), index(index) {
    }

    array_iterator(const array_iterator<T, N, is_const_iterator>& rhs): array(rhs.array), index(rhs.index) {
    }

    bool operator==(const array_iterator& rhs) const {
    	return index == rhs.index;
    }
    bool operator!=(const array_iterator& rhs) const {
    	return !(*this == rhs);
    }
    
    array_iterator& operator++() {
        ++index;
        return *this;
    }
	array_iterator& operator--() {
        --index;
        return *this;
    }

    array_iterator operator++(int) {
       auto prev = *this;
       ++*this;
       return prev;
    }

    array_iterator operator--(int) {
        auto prev = *this;
        --*this;
        return prev;
    }

    reference operator*() {
    	return array.lookup(index, array.most_recent_version(index));
    }
    
    pointer operator->() const {
        return &array.lookup(index, array.most_recent_version(index));
    }

private:
	data_reference array;
    size_type index;
};

}
