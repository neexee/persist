#pragma once
#include <algorithm>
#include <memory>
#include <stdexcept>

namespace persist {

template <typename T, class A = std::allocator<T>>
class list {
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type; 
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;
    typedef typename A::pointer pointer;
	typedef typename A::const_pointer const_pointer;
	
    template<bool is_const_iterator = true>
    class list_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        typedef typename std::conditional<is_const_iterator, typename list::const_pointer, typename list::pointer>::type pointer;
        typedef typename std::conditional<is_const_iterator, typename list::const_reference, typename list::reference>::type reference;
        
        typedef typename list::value_type value_type; 
        typedef typename list::difference_type difference_type;
        typedef typename list::size_type size_type;
        
        list_iterator() {
        }

        bool operator==(const list_iterator& rhs) const {
            return version == rhs.version && (node->prev == rhs.node->prev);
        }

        bool operator!=(const list_iterator& rhs) const {
            return !(*this == rhs);
        }
        
        list_iterator& operator++() {
            auto& nextmap = node->next;
            //end of list
            if(nextmap.empty()) {
                auto after_end_node = std::make_shared<list::node>(this->node, version);
                node = after_end_node;
                return *this;
            }

            auto lowest_it = nextmap.upper_bound(version);            
            if(lowest_it != nextmap.begin()) {
                --lowest_it;
            }
            node = lowest_it->second;
            return *this;
        }

        list_iterator& operator--() {
            auto& prevmap = node->prev;
            auto lowest_it = prevmap.upper_bound(version);
            if(lowest_it != prevmap.begin()) {
                --lowest_it;
            }
            node = lowest_it->second;
            return *this;
        }
        
        list_iterator operator++(int) {
            nodeptr prev = node;
            ++*this;
            return list_iterator(prev, version);
        }

        list_iterator operator--(int) {
            nodeptr prev = node;
            --*this;
            return list_iterator(prev, version);
        }

        reference operator*() {
            return node->data;
        }
        pointer operator->() {
            return &node->data;
        }

        friend class list_iterator<true>;
        friend class list;
    private:
        typedef typename list::nodeptr nodeptr;

        list_iterator(const nodeptr& node, size_type version) : node (node), version(version) {}
        
        nodeptr node;
        size_type version;
    };

    typedef list_iterator<false> iterator;
	typedef list_iterator<true> const_iterator;
       
    list() {
    }

    template <class InputIterator>
    list (InputIterator first, InputIterator last) : version(0) {
        startnode = std::make_shared<node>(*first, std::shared_ptr<node>());
        nodeptr prev = startnode;
        nodeptr tail;
        for (auto it = std::next(first); it != last; ++it) {
            tail = std::make_shared<node>(*it, prev);
            auto& prevnextmap = prev->next;
            prevnextmap.insert(std::make_pair(0, tail));
            prev = tail;
        }
        endnode = tail;
    }

    list (std::initializer_list<T> il): list(il.begin(), il.end()) {
    }

    iterator insert(const_iterator pos, const T& value ) {
        auto next = pos.node;
        nodeptr prev;
        if(pos.node->prev.empty()) {
            prev = nullptr;
        }
        else {
            prev = (--pos).node;
        }
        ++version;
        
        auto new_element = std::make_shared<node>(value, prev, next, version);
        
        next->prev[version] = new_element;
        if(prev != nullptr) {
            prev->next[version] = new_element;
        }
        else {
            startnode = new_element;
        }

        return iterator(new_element, version);
    }

    iterator begin() {
        return begin(version);
    }

    iterator end() {
        return end(version);
    }

    iterator begin (size_type version) {
        return iterator(startnode, version);
    }

    iterator end(size_type version) {
        return iterator(endnode, version);
    }
    
    const_iterator cbegin() const {
        return cbegin(version);
    }

    const_iterator cend() const {
        return cend(version);
    }

    const_iterator cbegin (size_type version) const {
        return const_iterator(startnode, version);
    }

    const_iterator cend(size_type version) const {
        auto after_end_node = std::make_shared<node>(endnode, version);
        return const_iterator(after_end_node, version);
    }
private:
    struct node;
    typedef std::shared_ptr<node> nodeptr;
    struct node
    {
        T data;
        node(nodeptr prev, size_type version) {
            this->prev[version] = prev;
        }

        node(const T& data, nodeptr prev): data(data) {
            this->prev[0] = prev;
        }

        node(const T& data, nodeptr prev, nodeptr next, size_type version): data(data) {
            this->prev[version] = prev;
            this->next[version] = next;
        }
        std::map<size_type, nodeptr> next;
        std::map<size_type, nodeptr> prev;
    };

    size_type version;
    nodeptr startnode;
    nodeptr endnode;
};

}
