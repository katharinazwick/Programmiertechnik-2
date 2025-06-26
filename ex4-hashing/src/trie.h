#ifndef __TRIE_H__
#define __TRIE_H__

#include <array>
#include <functional>
#include <map>
#include <cassert>

#include "st.h"

// I am also used in the tests. So do not change me! :)
// I am also useful for the implementation of the Trie CLI ;)
template <std::size_t N>
std::array<char, N> strtoarr(const std::string &s) {
    assert(s.size() == N);
    std::array<char, N> arr;
    for (int i = 0; i < N; i++) {
        arr[i] = (char)s[i];
    }
    return (arr);
}

// Trie
template <typename Key, typename Value, size_t U>
class Trie {
    struct Node {
        Key key;
        Value val;
        int size;
        // TODO: how would you represent the multiple paths?

        // constructor with values
        Node(const Key &k, const Value &v, const int s)
            : key(k), val(v), size(s) {}
    };
    Node *root;  // root of the search forest
    // TODO: you will need to save the allowed alphabet somewhere
    // be mindful that you need a fast structure here

    // TODO: it helps to write a function that returns a index in the alphabet based
    // on the key, be mindful that this function needs to be fast

    // copys an existing tree pointed to by n
    const Node *deep_copy_tree(const Node *n) const {
        if (n) {
            auto node = new Node(n->key, n->val, n->size);
            // TODO: how would you handle the paths?
            return (node);
        }
        return (nullptr);
    }

    // frees the tree pointed to by n
    void free_tree(const Node *n) const {
        if (n) {
            // TODO: how would you handle the children?
            delete n;
        }
        return;
    }

   public:
    // default constructor
    template <std::size_t N>  // single functions can have a size template
    Trie(const std::array<Key, N> &a) {
        // TODO: the argument is an array of keys - why?
    }

    // copy constructor
    Trie(const Trie &t) { root = deep_copy_tree(t.root); }

    // move constructor
    Trie(Trie &&t) : root(t.root) { t.root = nullptr; }

    // copy assignment
    Trie &operator=(const Trie &t) {
        // free the existing trie
        free_tree(root);
        // copy the tree
        root = deep_copy_tree(t.root);
        return (*this);
    }

    // move assignment
    Trie &operator=(Trie &&t) {
        // free the existing tree
        free_tree(root);
        root = t.root;
        t.root = nullptr;
        return (*this);
    }

    // destructor
    ~Trie() { free_tree(root); }

    // put a key-value pair into the table
    template <std::size_t N>
    void add(const std::array<Key, N> &k, const Value a) {
        // TODO: Add implementation.
    }

    template <std::size_t N>
    bool contains(const std::array<Key, N> &k) {
        // TODO: Add implementation.
        return false;
    }

    template <std::size_t N>
    bool observed(const std::array<Key, N> &k) {
        // TODO: Add implementation.
        return false;
    }

    // we could also implement a function that returns the value of a key
    // this is not needed for the trie CLI, but it would be useful in practice
    // feel free to implement it if you want to - it is not required
};

#endif
