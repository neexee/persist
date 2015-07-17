#pragma once

namespace persist {

template <typename T, size_t N>
class array_iterator { 
public:
    typedef parray<T, N> C;
    typedef typename C::size_type size_type;
    typedef typename C::difference_type difference_type;
    typedef typename C::value_type value_type;
    typedef typename C::reference reference;
    typedef typename C::const_reference const_reference;
    typedef typename C::pointer pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    array_iterator(parray<T, N>& array, size_type index) : array(array), index(index) {
    }
    //iterator(const iterator&)
    ~array_iterator(){}

    //iterator& operator=(const iterator&);
    bool operator==(const array_iterator& rhs) const {
    	return array == rhs.array && index == rhs.index;
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

    reference operator*() const {
    	return array.lookup(index, array.most_recent_version(index));
    }
    pointer operator->() const;
private:
	parray<T, N> & array;
    size_type index;
};

template <typename T, size_t N>
class array_const_iterator { 
public:
    typedef parray<T, N> C;
    typedef typename C::size_type size_type;
    typedef typename C::difference_type difference_type;
    typedef typename C::value_type value_type;
    typedef typename C::reference reference;
    typedef typename C::const_reference const_reference;
    typedef typename C::pointer pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    array_const_iterator(const parray<T, N>& array, size_type index) : array(array), index(index) {
    }
    //iterator(const iterator&)
    ~array_const_iterator(){}

    //iterator& operator=(const iterator&);
    bool operator==(const array_const_iterator& rhs) const {
    	return array == rhs.array && index == rhs.index;
    }
    bool operator!=(const array_const_iterator& rhs) const {
    	return !(*this == rhs);
    }
    array_const_iterator& operator++() {
        ++index;
        return *this;
    }
    array_const_iterator& operator--() {
        --index;
        return *this;
    }
    const_reference operator*() const {
    	return array.lookup(index, array.most_recent_version(index));
    }
    pointer operator->() const;
private:
	const parray<T, N> & array;
	size_type index;
};

}