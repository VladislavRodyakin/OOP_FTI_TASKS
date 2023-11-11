#pragma once

class Tree {
public:
    // Конструкторы и деструктор
    Tree();
    Tree(const Tree& root);
    ~Tree();

    // Добавление и удаление элемента
    void addNode(const T& value);
    void removeNode(const T& value);

    // Добавление и удаление поддерева
    void addSubtree(Tree& subtree);
    void removeSubtree(Tree& subtree);

    // Итератор перемещения по дереву
    class Tree_Iterator {
    public:
        // Конструкторы и деструктор
        Tree_Iterator();
        Tree_Iterator(const Tree_Iterator& other);
        ~Tree_Iterator();

        // Оператор присваивания
        Tree_Iterator& operator=(const Tree_Iterator& other);

        // Операторы сравнения
        bool operator==(const Tree_Iterator& other) const;
        bool operator!=(const Tree_Iterator& other) const;

        // Операторы разыменования
        Tree& operator*() const;
        Tree* operator->() const;

        // Операторы инкремента и декремента
        Tree_Iterator& operator++(); // Инкремент (перемещение в следующий элемент)
        Tree_Iterator operator++(int); // Инкремент (постфиксный)
        Tree_Iterator& operator--(); // Декремент (перемещение в предыдущий элемент)
        Tree_Iterator operator--(int); // Декремент (постфиксный)
    };

    // Итератор обхода в глубину
    Tree_Iterator beginDepthFirst() const;
    Tree_Iterator endDepthFirst() const;

    // Итератор обхода в ширину
    Tree_Iterator beginBreadthFirst() const;
    Tree_Iterator endBreadthFirst() const;
};