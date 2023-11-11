#pragma once

class Tree {
public:
    // ������������ � ����������
    Tree();
    Tree(const Tree& root);
    ~Tree();

    // ���������� � �������� ��������
    void addNode(const T& value);
    void removeNode(const T& value);

    // ���������� � �������� ���������
    void addSubtree(Tree& subtree);
    void removeSubtree(Tree& subtree);

    // �������� ����������� �� ������
    class Tree_Iterator {
    public:
        // ������������ � ����������
        Tree_Iterator();
        Tree_Iterator(const Tree_Iterator& other);
        ~Tree_Iterator();

        // �������� ������������
        Tree_Iterator& operator=(const Tree_Iterator& other);

        // ��������� ���������
        bool operator==(const Tree_Iterator& other) const;
        bool operator!=(const Tree_Iterator& other) const;

        // ��������� �������������
        Tree& operator*() const;
        Tree* operator->() const;

        // ��������� ���������� � ����������
        Tree_Iterator& operator++(); // ��������� (����������� � ��������� �������)
        Tree_Iterator operator++(int); // ��������� (�����������)
        Tree_Iterator& operator--(); // ��������� (����������� � ���������� �������)
        Tree_Iterator operator--(int); // ��������� (�����������)
    };

    // �������� ������ � �������
    Tree_Iterator beginDepthFirst() const;
    Tree_Iterator endDepthFirst() const;

    // �������� ������ � ������
    Tree_Iterator beginBreadthFirst() const;
    Tree_Iterator endBreadthFirst() const;
};