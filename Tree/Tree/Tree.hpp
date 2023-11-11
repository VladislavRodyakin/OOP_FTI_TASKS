#pragma once
#include <vector> //std::vector
#include <algorithm> //std::find

template<typename T> class Tree final {
    std::vector<Tree> children; // * или &, дальше решим // вообще removeChild копирует всех потомков удаляемого к родителю, что очень затратно
    T& data;
public:
    // Конструкторы и деструктор
    Tree() {}; // = delete?
    Tree(const Tree<T>& root): data(root.data) {
        children = root.children; // наверное должно быть сложнее
    }
    Tree(const T& value): data(value) {};

    ~Tree() { // проитерируемся через всех, для этого нужны итераторы (итератор ломается, если я правильно помню)
            // на сейчас реализовать через removeChild по всем детям, потом убить свою data
            // чую что можно влететь в цикл реализаций, нужно разобраться подробнее
            //беда с removeChild в том что будет просто неадекватное количество копирований потомков
        for (auto child : children) {
            removeChild(child.data);
        }
        delete(data);
    }
    // Добавление и удаление элемента
    void addChild(const T& value) {
        children.emplace_back(value);
    }
    void removeChild(const T& value) { // находим child с value find-ом, подсоединяем всех его children к родителю (нам), и pop элемент
                                            // нужно разобраться как быть с data
        auto deletable = std::find(children.begin(), children.end(), value);
    #ifdef __cpp_lib_containers_ranges
        children.append_range(deletable.children); //это фишка C++23, поэтому такая конструкция (взято из примера на cppreference.com)
        // учитывая насколько всё серое, оно видимо всё-же не работает
    #else
        children.insert(children.end(), deletable->children.begin(), deletable->children.end()); // проверить deletable->
    #endif
        delete(deletable->data);
        children.erase(deletable);
    }
    // Добавление и удаление поддерева
    void addSubtree(Tree<T>& subtree) {
        children.push_back(subtree); //push_back не выделен цветом, м/б какая-то проблема (всё собирается нормально, так что непонятно)
    }
    void removeSubtree(Tree<T>& subtree) { // пока так, вроде должно работать. нужно посмотреть на инкапсуляцию, скорее всего переделать с использованием get_data или чего-то похожего
        removeChild(subtree.data);
    }

    // Насколько плох вложенный класс итератора? Если только вдруг нам не потребуется дерево без итератора
    // Итератор перемещения по дереву
    class Tree_Iterator final { // видимо нужно будет 2 итератора. Скорее всего наследованные от этого
        size_t index; //сомнительная идея - в begin собирать все ноды в нужном порядке и итератором ходить по вектору.
                        // за это меня скорее всего повесят, поэтому нужно сделать по-другому
    public:
        using iterator_categoty = std::forward_iterator_tag; // нужно уточнить
        using difference_type = std::ptrdiff_t;

        // хороший вопрос - что мы возвращаем, хранимое или ноду
        // LegacyIterator и RangeIterator возвращает хранимое
        // нужно согласовываться вверху с удалением, т.к. оно может использовать итераторы
        // так-то не должны использовать
        // 500% не должны, у нас же итератор после первого удаления сломается (инвалидируется)
        using value_type = T;
        using pointer = T*;
        using reference = T&;


        // Конструкторы и деструктор
        //Tree_Iterator();
        //Tree_Iterator(const Tree_Iterator& other);
        //~Tree_Iterator();
        // нужно будет посмотреть подробнее
        Tree_Iterator(Tree<T>* root) {}; // указатель для согласованности с end(), т.к. нельзя разыменовывать nullptr

        // Оператор присваивания
        //Tree_Iterator& operator=(const Tree_Iterator& other);
        // оно надо вообще? в range не было
        
        // Операторы сравнения
        bool operator==(const Tree_Iterator& other) const {
            return index == other.index;
        }
        bool operator!=(const Tree_Iterator& other) const {
            return index != other.index;
        }

        // Операторы разыменования
        // нужно понимание реализации
        T& operator*() const;
        T* operator->() const;

        // Операторы инкремента и декремента
        Tree_Iterator& operator++() {
            index++;
            return *this;
        }
        Tree_Iterator operator++(int increase) {
            index += increase; // не мог принять по ссылке, почему?
            return *this;
        }
        Tree_Iterator& operator--() {
            index--;
            return *this;
        }
        Tree_Iterator operator--(int decrease) {
            index -= decrease; // не мог принять по ссылке, почему?
            return *this;
        }
    };

    // Итератор обхода в глубину
    Tree_Iterator beginDepth() const {
        return Tree_Iterator(this);
    }
    Tree_Iterator endDepth() const {
        return Tree_Iterator(nullptr);
    }

    // Итератор обхода в ширину
    Tree_Iterator beginBreadth() const {
        return Tree_Iterator(this);
    }
    Tree_Iterator endBreadth() const {
        return Tree_Iterator(nullptr);
    }
};