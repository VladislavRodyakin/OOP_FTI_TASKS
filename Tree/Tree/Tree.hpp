#pragma once
#include <vector> //std::vector
#include <algorithm> //std::find

template<typename T> class Tree final {
    std::vector<Tree> children; // * ��� &, ������ ����� // ������ removeChild �������� ���� �������� ���������� � ��������, ��� ����� ��������
    T& data;
public:
    // ������������ � ����������
    Tree() {}; // = delete?
    Tree(const Tree<T>& root): data(root.data) {
        children = root.children; // �������� ������ ���� �������
    }
    Tree(const T& value): data(value) {};

    ~Tree() { // �������������� ����� ����, ��� ����� ����� ��������� (�������� ��������, ���� � ��������� �����)
            // �� ������ ����������� ����� removeChild �� ���� �����, ����� ����� ���� data
            // ��� ��� ����� ������� � ���� ����������, ����� ����������� ���������
            //���� � removeChild � ��� ��� ����� ������ ������������ ���������� ����������� ��������
        for (auto child : children) {
            removeChild(child.data);
        }
        delete(data);
    }
    // ���������� � �������� ��������
    void addChild(const T& value) {
        children.emplace_back(value);
    }
    void removeChild(const T& value) { // ������� child � value find-��, ������������ ���� ��� children � �������� (���), � pop �������
                                            // ����� ����������� ��� ���� � data
        auto deletable = std::find(children.begin(), children.end(), value);
    #ifdef __cpp_lib_containers_ranges
        children.append_range(deletable.children); //��� ����� C++23, ������� ����� ����������� (����� �� ������� �� cppreference.com)
        // �������� ��������� �� �����, ��� ������ ��-�� �� ��������
    #else
        children.insert(children.end(), deletable->children.begin(), deletable->children.end()); // ��������� deletable->
    #endif
        delete(deletable->data);
        children.erase(deletable);
    }
    // ���������� � �������� ���������
    void addSubtree(Tree<T>& subtree) {
        children.push_back(subtree); //push_back �� ������� ������, �/� �����-�� �������� (�� ���������� ���������, ��� ��� ���������)
    }
    void removeSubtree(Tree<T>& subtree) { // ���� ���, ����� ������ ��������. ����� ���������� �� ������������, ������ ����� ���������� � �������������� get_data ��� ����-�� ��������
        removeChild(subtree.data);
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