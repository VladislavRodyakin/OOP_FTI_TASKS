#pragma once

template<typename T> class Node final {
    Node right;
    Node left;
    T data;
public:
    //  онструкторы и деструктор
    Node() {}; // = delete?
    Node(const T& value) : data(value) {};

    ~Node(){
        delete(data);
    }
    // ƒобавление и удаление элемента
    void addChild(const T& value, bool is_greater) { // если хранить функцию сравнени€ в ноде, то is_greater не потребуетс€
        if (is_greater) right = Node(value);
        left = Node(value);
    }
    void removeChild(const T& value) { // тут очень хотелось бы иметь функцию 
    }

    // Ќасколько плох вложенный класс итератора? ≈сли только вдруг нам не потребуетс€ дерево без итератора
    // »тератор перемещени€ по дереву
    class Tree_Iterator final { // видимо нужно будет 2 итератора. —корее всего наследованные от этого
        size_t index; //сомнительна€ иде€ - в begin собирать все ноды в нужном пор€дке и итератором ходить по вектору.
        // за это мен€ скорее всего повес€т, поэтому нужно сделать по-другому
    public:
        using iterator_categoty = std::forward_iterator_tag; // нужно уточнить
        using difference_type = std::ptrdiff_t;

        // хороший вопрос - что мы возвращаем, хранимое или ноду
        // LegacyIterator и RangeIterator возвращает хранимое
        // нужно согласовыватьс€ вверху с удалением, т.к. оно может использовать итераторы
        // так-то не должны использовать
        // 500% не должны, у нас же итератор после первого удалени€ сломаетс€ (инвалидируетс€)
        using value_type = T;
        using pointer = T*;
        using reference = T&;


        //  онструкторы и деструктор
        //Tree_Iterator();
        //Tree_Iterator(const Tree_Iterator& other);
        //~Tree_Iterator();
        // нужно будет посмотреть подробнее
        Tree_Iterator(Tree<T>* root) {}; // указатель дл€ согласованности с end(), т.к. нельз€ разыменовывать nullptr

        // ќператор присваивани€
        //Tree_Iterator& operator=(const Tree_Iterator& other);
        // оно надо вообще? в range не было

        // ќператоры сравнени€
        bool operator==(const Tree_Iterator& other) const {
            return index == other.index;
        }
        bool operator!=(const Tree_Iterator& other) const {
            return index != other.index;
        }

        // ќператоры разыменовани€
        // нужно понимание реализации
        T& operator*() const;
        T* operator->() const;

        // ќператоры инкремента и декремента
        Tree_Iterator& operator++() {
            index++;
            return *this;
        }
        Tree_Iterator operator++(int increase) {
            index += increase; // не мог прин€ть по ссылке, почему?
            return *this;
        }
        Tree_Iterator& operator--() {
            index--;
            return *this;
        }
        Tree_Iterator operator--(int decrease) {
            index -= decrease; // не мог прин€ть по ссылке, почему?
            return *this;
        }
    };

    // »тератор обхода в глубину
    Tree_Iterator beginDepth() const {
        return Tree_Iterator(this);
    }
    Tree_Iterator endDepth() const {
        return Tree_Iterator(nullptr);
    }

    // »тератор обхода в ширину
    Tree_Iterator beginBreadth() const {
        return Tree_Iterator(this);
    }
    Tree_Iterator endBreadth() const {
        return Tree_Iterator(nullptr);
    }
};