#pragma once
#include <iterator> // iterator tags
// #include "Node.hpp"

// making unbalanced binary tree

// make depth first iterator as default, allow to use other through template argument
// interface lookalike to map, in so implement [], returns (value) under (key) (it is a wrap around find(key), which returns iterator)

// expand template to key, value, cmp (as functor), iterator
template<typename Key, typename Value, typename Cmp> class Tree final { 

    class Node final{
        // weak pointer parent, unique children
        Node* right = nullptr;
        Node* left = nullptr;
        Node* parent = nullptr;
        Key key;
        Value data;
    public:
        void setData(Value& _data) { data = _data; }
        Value getData() { return data; }
        void setKey(Key& _key) { key = _key; }
        Key getKey() { return key; }
        void setLeft(Node* node) { left = node; }// copy/move?
        Node* getLeft() { return left; }
        void setRight(Node* node) { right = node; }
        Node* getRight() { return right; }
        void setParent(Node* node) { parent = node; }
        Node* getParent() { return parent; }
    };
    
    Cmp cmp; // get from template     typedef bool (*cmp_ptr)(Value a, Value b);
    Node* root = nullptr; // shared
    size_t size;

public:
    Tree() {}; // = delete?
    Tree(const Tree<Key, Value, Cmp>& other) : root(other.root), cmp(other.cmp) {}; // copy pointer w/ root and internal ptrs
    // Tree(const Value& value, cmp_ptr compare): data(value) {};
    ~Tree() { 
        delete(root);
        // delete(compare);
    }

    // redo
    /*
    void addElem(Value& value) {
        if (root)
            root = *Node(value);
        else
            root->addChild(value);
    }

    void removeElem(Value& value) {
        if (root && root->getData() == value) {
            Node::deleteNode(root);
        }
    }
    */

    void addSubtree(Tree<Key, Value, Cmp>& subtree) {

    }
    void removeSubtree(Tree<Key, Value, Cmp>& subtree) {

    }

    class Tree_Iterator { 
        // weak pointer to node, not index
        Node* node;
    public:
        using iterator_categoty = std::forward_iterator_tag; // check whether could be uptired
        using difference_type = std::ptrdiff_t;
        using value_type = Value;
        using pointer = Value*;
        using reference = Value&;

        //Tree_Iterator();
        //Tree_Iterator(const Tree_Iterator& other);
        //~Tree_Iterator();
        Tree_Iterator(Tree<Key, Value, Cmp>* root) {};

        //Tree_Iterator& operator=(const Tree_Iterator& other);
        // is it needed at all? wasnt in range task
        
        bool operator==(const Tree_Iterator& other) const {
            return node->getKey == other.node->getKey;
        }
        bool operator!=(const Tree_Iterator& other) const {
            return node->getKey != other.node->getKey;
        }

        Value& operator*() const {
            return *node;
        }
        Value* operator->() const {
            return node;
        }

        // redo as written
        Tree_Iterator& operator++() {// btree_next
            //index++;
            return *this;
        }
        Tree_Iterator operator+(int& increase) { // for increase btree_next
            //index += increase;
            return *this;
        }
        Tree_Iterator& operator--() { // btree_prev
            //index--;
            return *this;
        }
        Tree_Iterator operator-(int& decrease) { // for decrease btree_prev
            //index -= decrease; 
            return *this;
        }
    };

    // redo as written
    Tree_Iterator begin() const { // btree_first
        return Tree_Iterator(this);
    }
    Tree_Iterator end() const { // btree_last->right
        return Tree_Iterator(this);
    }
};