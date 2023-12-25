#pragma once
#include<memory>
#include<utility>

template<class Type, class TDeleter = std::default_delete<Type>> class UniquePointer final{
    Type* m_ptr;
    using t_UniquePTR = UniquePointer<Type, TDeleter>;
public:
    // просто UniquePoiner() = default
    UniquePointer() : UniquePointer{ nullptr } {};
    //надо проверить на null pObject
    explicit UniquePointer(Type* pObject) : m_ptr{ pObject } {};
    UniquePointer(t_UniquePTR&& uniquePTR) noexcept : m_ptr{ uniquePTR.release() } {};
    ~UniquePointer() {
        if (m_ptr) {
            delete m_ptr;
        }
    }

    // Assignment.
    //кажется проще будет сделать std::swap и указателей
    UniquePointer& operator=(t_UniquePTR&& uniquePTR) noexcept {
        if (this != &uniquePTR) {
            reset(uniquePTR.release());
        }
        return *this;
    }
    UniquePointer& operator=(Type* pObject) {
        reset(pObject);
        return *this;
    }

    // Observers.
    Type& operator*() const { return *m_ptr; } // Dereference the stored pointer.
    Type* operator->() const { return m_ptr; } // Return the stored pointer.
    Type* get() const { return m_ptr; } // Return the stored pointer.
    TDeleter& get_deleter() { return TDeleter; }// Return a reference to the stored deleter.

    // Return false if the stored pointer is null.
    operator bool() const {
        return m_ptr != nullptr;
    }

    // Modifiers.
    // Надо еще удалить old, иначе утечка памяти
    Type* release() {
        Type* old = m_ptr;
        m_ptr = nullptr;
        return old;
        // return std::exchange(m_ptr, nullptr);
    }

    // Без дополнительного old вообще можно обойтись
    // if (m_ptr) {delete m_ptr};
    //  m_ptr = pObject;
    void reset(Type* pObject = nullptr, TDeleter deleter = {}) {
        Type* old = m_ptr;
        m_ptr = pObject;
        // Type* old = std::exchange(m_ptr, pObject);
        if (old) {
            delete old;
        }
    }
    void swap(t_UniquePTR& uniquePTR) { std::swap(this->m_ptr, uniquePTR.m_ptr); }// Exchange the pointer with another object.

private: // Disable copy from lvalue.
    UniquePointer(const t_UniquePTR&) = delete;
    t_UniquePTR& operator=(const t_UniquePTR&) = delete;
};

template<class Type, class... Args> UniquePointer<Type> make_unique(Args &&...args) {
    return UniquePointer<Type>(new Type(std::forward<Args>(args)...));
}
