#pragma once

namespace persist {
template<typename T, bool is_const_iterator = true>
class list_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    typedef list<T> C;
public:
    typedef typename std::conditional<is_const_iterator, typename C::const_pointer, typename C::pointer>::type pointer;
    typedef typename std::conditional<is_const_iterator, typename C::const_reference, typename C::reference>::type reference;
    
    typedef typename C::size_type size_type;
    typedef typename C::difference_type difference_type;
    typedef typename C::value_type value_type;
    typedef typename C::const_reference const_reference;

    //iterator(const iterator&)
    ~list_iterator(){}

    //iterator& operator=(const iterator&);
    bool operator==(const list_iterator& rhs) const {
    	return version == rhs.version && node == rhs.node;
    }
    bool operator!=(const list_iterator& rhs) const {
    	return !(*this == rhs);
    }
    
    list_iterator& operator++() {
        return *this;
    }
	list_iterator& operator--() {
        return *this;
    }

    reference operator*();
    pointer operator->();

    friend class list_iterator<T, true>;
    friend class list<T>;
private:
    typedef typename C::nodeptr nodeptr;
    list_iterator(nodeptr& node, size_type version) : node (node), version(version) {
    }
    nodeptr node;
    size_type version;
};

}