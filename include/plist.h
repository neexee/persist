#pragma once
#include <algorithm>
#include <memory>
#include <stdexcept>

namespace persist {

template <typename T, bool> class list_iterator;
template <typename T, bool> class list_const_iterator;

template <typename T, class A = std::allocator<T>>
class list {
public:
    typedef typename A::value_type value_type; 
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;
    typedef typename A::pointer pointer;
	typedef typename A::const_pointer const_pointer;
	
    typedef list_iterator<T, false> iterator;
	typedef list_iterator<T, true> const_iterator;
    
    friend iterator;
    friend const_iterator;
    
    list() {
    }

    template <class InputIterator>
    list (InputIterator first, InputIterator last);

    list (const list& x);

    list (list&& x);
    
    list (std::initializer_list<T> il);
    
    iterator insert(const_iterator pos, const T& value );

    iterator begin() {
        return iterator(startnode, 0); //!
    }

    iterator end() {
        return iterator(endnode, 0); //!
    }
private:
    struct node;
    typedef std::shared_ptr<node> nodeptr;
    struct node
    {
        T data;
        std::map<size_type, nodeptr> next;
        std::map<size_type, nodeptr> prev;
    };

    nodeptr startnode;
    nodeptr endnode;
};
}
#include "plistiter.h" 