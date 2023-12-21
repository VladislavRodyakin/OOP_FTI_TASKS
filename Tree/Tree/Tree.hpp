#pragma once
#include <iterator> // iterator tags

// making unbalanced binary tree
// key everywhere

// interface lookalike to map, in so implement [], returns (value) under (key) (it is a wrap around find(key), which returns iterator)
template<typename Key, typename Value, typename Cmp> class Tree {

    class Node final {
        // weak pointer parent, unique children
        Node* right = nullptr;
        Node* left = nullptr;
        Node* parent = nullptr;
        const Key key;
        Value data;
    public:
        Node() = delete;
        Node(const Key& _key, Value _value) : key(_key), data(_value) {};
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

    Cmp compare_func; // int (*cmp_ptr)(Value a, Value b);
    Node* root = nullptr; // shared
    size_t size = 0;

    Node* insert_node(Node* _root, const Key& key, Value value) {
        if (_root == nullptr) {
            _root = new Node(key, value);
            root = _root;
            return _root;
        }
        int compare_result = compare_func(_root->getKey(), key);
        if (compare_result > 0) {
            if (_root->getLeft() == nullptr) {
                _root->setLeft(new Node(key, value));
                _root->getLeft()->setParent(_root);
                return _root->getLeft();
            }
            return insert_node(_root->getLeft(), key, value);
        }
        if (compare_result < 0) {
            if (_root->getRight() == nullptr) {
                _root->setRight(new Node(key, value));
                _root->getRight()->setParent(_root);
                return _root->getRight();
            }
            return insert_node(_root->getRight(), key, value);
        }
        else { //there is node w/ this key already
            _root->setData(value);
            return _root;
        }
    }

    Node* remove_single_node(Node* _root) {
        Node* node = nullptr;
        if (_root->getLeft() == _root->getRight()) //empty undertree 
            node = nullptr;
        else if (_root->getLeft() == nullptr)
            node = _root->getRight();
        else if (_root->getRight() == nullptr)
            node = _root->getLeft();
        else { // both undertrees
            Node* node2 = _root->getRight();
            node = _root->getRight();
            while (node2->getLeft())
                node2 = node2->getLeft();
            node2->setLeft(_root->getLeft());
            _root->getLeft()->setParent(node2);
        }
        if (node != nullptr)
            node->setParent(_root->getRight());
        delete _root;
        size--;
        return node;
    }

    void erase(Node* _root) {
        if (_root == nullptr) {
            return;
        }
        Node* parent = _root->getRight();
        if (parent == nullptr)
            root = remove_single_node(_root);
        else if (parent->getLeft() == _root)
            parent->setLeft(remove_single_node(_root));
        else
            parent->setRight(remove_single_node(_root));
    }

    Node* find_node(Node* start_node, const Key& key) {
        if (start_node == nullptr)
            return nullptr;
        int compare_result = compare_func(key, start_node->getKey());
        if (compare_result == 0)
            return start_node;
        if (compare_result < 0)
            return find_node(start_node->getLeft(), key);
        return find_node(start_node->getRight(), key);
    }

public:
    Tree() = delete;
    Tree(Cmp cmp) : compare_func(cmp) {};
    Tree(const Tree<Key, Value, Cmp>& other) : root(other.root), compare_func(other.compare_func) {}; // copy pointer w/ root and internal ptrs
    ~Tree() { 
        delete(root);
    }

    void addNode(const Key& key, Value value) {
        insert_node(root, key, value);
    }

    void removeNode(const Key& key) {
        erase(find_node(root, key));
    }

    Value& getValue(const Key& key) { // through iterator?
        Value r = find_node(root, key)->getData();
        return r;
        //return find_node(root, key)->getData();
    }

    Value& operator[](const Key& key) {
        Value r = find_node(root, key)->getData();
        return r;
        //return find_node(root, key)->getData();
    }

    // delete
    /*
    void addSubtree(Tree<Key, Value, Cmp>& _subtree) { // bad implementation
        Tree<Key, Value, Cmp> subtree = _subtree;
        while (subtree.root != nullptr) {
            (*this).addNode(subtree.root->getKey(), subtree.root->getData());
            subtree.removeNode(subtree.root->getKey());
        }
    }
    void removeSubtree(Tree<Key, Value, Cmp>& subtree) { // key implementation?
    }*/

    class Tree_Iterator { 
        Tree<Key, Value, Cmp>* tree;
        Node* node; // weak pointer
        Node* find_left(Node* root) {
            if (root == nullptr)
                return nullptr;
            Node* root2 = root;
            while (root2->getLeft())
                root2 = root2->getLeft();
            return root2;
        }
        Node* find_right(Node* root) {
            if (root == nullptr)
                return nullptr;
            Node* root2 = root;
            while (root2->getRight())
                root2 = root2->getRight();
            return root2;
        }
        //last
        Node* stop() {
            return nullptr;
        }
    public:
        using iterator_categoty = std::forward_iterator_tag; // check whether could be uptired, could be random access
        using difference_type = std::ptrdiff_t;
        using value_type = Value;
        using pointer = Value*;
        using reference = Value&;

        //Tree_Iterator();
        //Tree_Iterator(const Tree_Iterator& other);
        //~Tree_Iterator();
        Tree_Iterator(Tree<Key, Value, Cmp>* _tree) { //* not & bc "this" in tree.begin
            tree = _tree;
            node = find_left(tree->root);
        };
        
        bool operator==(const Tree_Iterator& other) const {
            return node->getKey() == other.node->getKey();
        }
        bool operator!=(const Tree_Iterator& other) const {
            return node->getKey() != other.node->getKey();
        }

        Value operator*() const {
            return node->getData();
        }
        Value* operator->() const {
            return *(node->getData());
        }


        Tree_Iterator& operator++() {// btree_next
            if (node == find_right(tree->root))
                node = stop();
            Node* node2 = node;
            if (node2->getRight() != nullptr)
                node = find_left(node2->getRight());
            while (node2->getParent()->getLeft() != node2)
                node2 = node2->getParent();
            node = node2->getParent();
            
            return *this;
        }
        Tree_Iterator operator+(int& increase) { // for increase btree_next
            for (int i = 0; i != increase; i++) {
                *this++;
            }
            return *this;
        }
        Tree_Iterator& operator--() { // btree_prev
            if (node == find_left(tree->root))
                node = stop();
            Node* node2 = *node;
            if (node2->getLeft() != nullptr)
                node = find_right(node2->getLeft());
            while (node2->getParent()->getRight() != node2)
                node2 = node2->getParent();
            node = node2->getParent();

            return *this;
        }
        Tree_Iterator operator-(int& decrease) { // for decrease btree_prev
            for (int i = 0; i != decrease; i++) {
                *this--;
            }
            return *this;
        }
    };

    // redo as written
    Tree_Iterator begin() { // btree_first
        return Tree_Iterator(this);
    }
    Tree_Iterator end()  { // btree_last->right
        return Tree_Iterator(this);
    }
};



// make depth first iterator as default, allow to use other through template argument
//
//template<typename Key, typename Value, typename Cmp, typename OwnIterator> class Tree final {
//public:
//    Tree_Iterator begin() const { // btree_first
//        return OwnIterator(this);
//    }
//    Tree_Iterator end() const { // btree_last->right
//        return OwnIterator(this);
//    }
//};