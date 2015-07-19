#pragma once

namespace persist {

template <typename T>
class list_iterator {
    typedef list<T> C;
public:
    typedef typename C::size_type size_type;
    typedef typename C::difference_type difference_type;
    typedef typename C::value_type value_type;
    typedef typename C::reference reference;
    typedef typename C::const_reference const_reference;
    typedef typename C::pointer pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

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

    reference operator*() const;
    pointer operator->() const;
private:
    typedef typename list<T>::nodeptr nodeptr;
    list_iterator(nodeptr& node, size_type version) : node (node), version(version) {
    }
    nodeptr node;
    size_type version;
};

template <typename T>
class list_const_iterator { 
    typedef list<T> C;
public:
    typedef typename C::size_type size_type;
    typedef typename C::difference_type difference_type;
    typedef typename C::value_type value_type;
    typedef typename C::reference reference;
    typedef typename C::const_reference const_reference;
    typedef typename C::pointer pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    //iterator(const iterator&)
    ~list_const_iterator(){}

    //iterator& operator=(const iterator&);
    bool operator==(const list_const_iterator& rhs) const {
    	return version == rhs.version && node == rhs.node;
    }
    bool operator!=(const list_const_iterator& rhs) const {
    	return !(*this == rhs);
    }
    list_const_iterator& operator++() {
        return *this;
    }
    list_const_iterator& operator--() {
        return *this;
    }
    const_reference operator*() const;
    pointer operator->() const;

private:
    typedef typename list<T>::nodeptr nodeptr;
    list_const_iterator(const nodeptr& node, size_type version) : node(node), version(version) {
    }
    const nodeptr node;
	size_type version;
};

}