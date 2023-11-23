#pragma once

//not implementing, all logic in Tree

// into tree
// must implement setter/getter, contain key, value, parent and children

template<typename T> class Node final {
    bool (*compare)(T a, T b); //1: a<b -1: a>b 
    // weak pointer parent, unique children
    Node<T>* right = nullptr;
    Node<T>* left = nullptr;
    Node<T>* parent = nullptr;
    T data;
public:
    Node() = delete;
    Node(const T& value, bool (*_compare)(T a, T b)) : data(value), compare(_compare) {};
    ~Node(){
        delete(compare);
        delete(left);
        delete(right);
    }

    T getData() {
        return data;
    }
    
    void addChild(const T& value) {
        bool direct = compare(data, value);
        if (direct && left == nullptr) left = Node<T>(value);
        else if (!direct && right == nullptr) right = Node<T>(value);
        else if (direct && left != nullptr) left->addChild(value);
        else if (!direct && right != nullptr) right->addChild(value);
    }

    void removeChild(const T& value) { 
        bool direct = compare(data, value);
        if (direct && left == nullptr); // return error
        else if (!direct && right == nullptr); // return error
        else if (direct && left->data == value) {
            Node<T>* tmp = left;
            left = reassignOwnStructure();
            delete(tmp);
        }
        else if (direct && right != nullptr) {
            Node<T>* tmp = right;
            right = reassignOwnStructure();
            delete(tmp);
        }
        else if (direct && left != nullptr) left->addChild(value);
        else if (!direct && right != nullptr) right->addChild(value);
    }

    void deleteNode(Node<T>* node) {
        Node<T>* tmp = node;
        node = reassignOwnStructure();
        delete(tmp);
    }

    // reassignOwnStructure move to private
    Node<T>* reassignOwnStructure() { 
        Node<T>* node = nullptr;
        if (this->left == this->right) //left == right == nullptr
            node = nullptr;
        else if (this->left == nullptr)
            node = this->right;
        else if (this->right == nullptr)
            node = this->left;
        else {
            Node<T>* node2 = this->right;
            node = this->right;
            while (node2->left) node2 = node2->left;
            node2->left = this->left;
            this->left->parent = node2;
        }
        if (node != nullptr)
            node->parent = this->parent;
        return node; // assignable value
    }

    void clear_undertree() {
        if (left) left->clear_undertree();
        if (right) right->clear_undertree();
        delete(data);
        delete(left);
        delete(right);
    }
};