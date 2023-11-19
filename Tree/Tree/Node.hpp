#pragma once

template<typename T> class Node final { // перейдём на указатели
    bool (*compare)(T a, T b); //1: a<b -1: a>b 
    Node* right = nullptr;
    Node* left = nullptr;
    Node* parent = nullptr;
    T data;
public:
    // Конструкторы и деструктор
    Node() {} = delete;
    Node(const T& value, bool (*_compare)(T a, T b);) : data(value), compare(_compare) {};
    ~Node(){
        delete(compare);
        delete(left);
        delete(right);
    }
    // Добавление и удаление потомка
    void addChild(const T& value) { 
        if (compare(data, value)) left = Node(value);
        else right = Node(value);
    }
    void removeChild(const T& value) { // тут много

    }
    Node* remove_self() {
        Node* node = nullptr;
        if (this->left == this->right) //left == right == nullptr
            node = nullptr;
        else if (this->left == nullptr)
            node = this->right;
        else if (this->right == nullptr)
            node = this->left;
        else {
            Node* node2 = this->right;
            node = this->right;
            while (node2->left) node2 = node2->left;
            node2->left = this->left;
            this->left->parent = node2;
        }
        if (node != nullptr)
            node->parent = this->parent;
        delete(this); // огрызок предыдущей реализации, скорее всего убрать
        return node;
    }
};