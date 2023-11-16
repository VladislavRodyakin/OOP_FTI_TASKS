#pragma once

template<typename T> class Node final {
    Node right;
    Node left;
    T data;
public:
    // ������������ � ����������
    Node() {}; // = delete?
    Node(const T& value) : data(value) {};

    ~Node(){
        delete(data);
    }
    // ���������� � �������� ��������
    void addChild(const T& value, bool is_greater) { // ���� ������� ������� ��������� � ����, �� is_greater �� �����������
        if (is_greater) right = Node(value);
        left = Node(value);
    }
    void removeChild(const T& value) { // ��� ����� �������� �� ����� ������� 
    }

    // ��������� ���� ��������� ����� ���������? ���� ������ ����� ��� �� ����������� ������ ��� ���������
    // �������� ����������� �� ������
    class Tree_Iterator final { // ������ ����� ����� 2 ���������. ������ ����� ������������� �� �����
        size_t index; //������������ ���� - � begin �������� ��� ���� � ������ ������� � ���������� ������ �� �������.
        // �� ��� ���� ������ ����� �������, ������� ����� ������� ��-�������
    public:
        using iterator_categoty = std::forward_iterator_tag; // ����� ��������
        using difference_type = std::ptrdiff_t;

        // ������� ������ - ��� �� ����������, �������� ��� ����
        // LegacyIterator � RangeIterator ���������� ��������
        // ����� ��������������� ������ � ���������, �.�. ��� ����� ������������ ���������
        // ���-�� �� ������ ������������
        // 500% �� ������, � ��� �� �������� ����� ������� �������� ��������� (��������������)
        using value_type = T;
        using pointer = T*;
        using reference = T&;


        // ������������ � ����������
        //Tree_Iterator();
        //Tree_Iterator(const Tree_Iterator& other);
        //~Tree_Iterator();
        // ����� ����� ���������� ���������
        Tree_Iterator(Tree<T>* root) {}; // ��������� ��� ��������������� � end(), �.�. ������ �������������� nullptr

        // �������� ������������
        //Tree_Iterator& operator=(const Tree_Iterator& other);
        // ��� ���� ������? � range �� ����

        // ��������� ���������
        bool operator==(const Tree_Iterator& other) const {
            return index == other.index;
        }
        bool operator!=(const Tree_Iterator& other) const {
            return index != other.index;
        }

        // ��������� �������������
        // ����� ��������� ����������
        T& operator*() const;
        T* operator->() const;

        // ��������� ���������� � ����������
        Tree_Iterator& operator++() {
            index++;
            return *this;
        }
        Tree_Iterator operator++(int increase) {
            index += increase; // �� ��� ������� �� ������, ������?
            return *this;
        }
        Tree_Iterator& operator--() {
            index--;
            return *this;
        }
        Tree_Iterator operator--(int decrease) {
            index -= decrease; // �� ��� ������� �� ������, ������?
            return *this;
        }
    };

    // �������� ������ � �������
    Tree_Iterator beginDepth() const {
        return Tree_Iterator(this);
    }
    Tree_Iterator endDepth() const {
        return Tree_Iterator(nullptr);
    }

    // �������� ������ � ������
    Tree_Iterator beginBreadth() const {
        return Tree_Iterator(this);
    }
    Tree_Iterator endBreadth() const {
        return Tree_Iterator(nullptr);
    }
};