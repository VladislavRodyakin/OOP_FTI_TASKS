#pragma once
#include<memory>
#include<utility>

template<class Type, class TDeleter = std::default_delete<Type>> class UniquePointer final{
    Type* m_ptr = nullptr;
    using t_UniquePTR = UniquePointer<Type, TDeleter>;
public:
    // просто UniquePoiner() = default;
    // UniquePoiner() = default; results in errors like "UniquePointer<Type, std::default_delete<Type>> has no default constructor
    // maybe it would fix itself with VS restart
    UniquePointer() : UniquePointer{ nullptr } {};
    explicit UniquePointer(Type* pObject) {
        if (pObject) {
            m_ptr = pObject;
        }
    }
    UniquePointer(t_UniquePTR&& uniquePTR) noexcept {
        std::swap(m_ptr,uniquePTR.m_ptr); // yes, we dont have to delete
    }
    ~UniquePointer() {
        if (m_ptr) {
            delete m_ptr;
        }
    }

    // Assignment.
    UniquePointer& operator=(t_UniquePTR&& uniquePTR) noexcept {
        if (this != &uniquePTR) {
            std::swap(m_ptr, uniquePTR.m_ptr);
            uniquePTR.release();
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
    void release() {
        if (m_ptr)
            delete m_ptr;
        m_ptr = nullptr;
        //Type* old = std::exchange(m_ptr, nullptr);
        //if (old != nullptr) {
            // delete old;
            // old = nullptr;
        ///} // best guess is that it calls "delete old" by itself at the end of the method, so any meddling is causing runtime SEH errors

        // delete std::exchange(m_ptr, nullptr); // memory access runtime errors
        // but problem is elsewhere

    } // it calls delete here, for some reason (see higher)

    void reset(Type* pObject = nullptr, TDeleter deleter = {}) {
        if (m_ptr) {
            delete m_ptr;
        }
        m_ptr = pObject;
    }
    void swap(t_UniquePTR& uniquePTR) { std::swap(this->m_ptr, uniquePTR.m_ptr); }// Exchange the pointer with another object.

private: // Disable copy from lvalue.
    UniquePointer(const t_UniquePTR&) = delete;
    t_UniquePTR& operator=(const t_UniquePTR&) = delete;
};

template<class Type, class... Args> UniquePointer<Type> make_unique(Args &&...args) {
    return UniquePointer<Type>(new Type(std::forward<Args>(args)...));
}
