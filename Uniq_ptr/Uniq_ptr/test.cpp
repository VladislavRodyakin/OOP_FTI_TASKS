#include "gtest/gtest.h"
#include "uniq_ptr.h"

struct test_struct {
    int* _val;
    test_struct(int* val) { _val = val; }
    test_struct(const test_struct& other) {
        _val = other._val;
    }
    ~test_struct() { _val = nullptr; }
    void multiply(int times) {
        if (_val) {
            _val[0] *= times;
        }
        else {
            return;
        }
    }
};

TEST(Constructor, Default) {
    UniquePointer<int> ptr;
    EXPECT_FALSE(ptr);
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(Constructor, PointerToObject) {
    int* p1 = new int[150];
    UniquePointer<int> ptr(p1);
    EXPECT_EQ(ptr.get(), p1);

    test_struct* p2 = new test_struct(p1);
    UniquePointer <test_struct> ptr2(p2);
    EXPECT_EQ(ptr2.get(), p2);
}

TEST(Constructor, Move) {
    test_struct* p2 = new test_struct(new int[10]);
    UniquePointer<test_struct> ptr(p2);
    EXPECT_TRUE(ptr);

    UniquePointer <test_struct> ptr2(std::move(ptr));
    EXPECT_TRUE(ptr2);
    EXPECT_FALSE(ptr);
}

TEST(Assignment, Move) {
    int* p1 = new int[10];
    UniquePointer<int> ptr(p1);
    int* p2 = new int[100];
    UniquePointer <int> ptr2(p2);
    ptr = std::move(ptr2);

    EXPECT_EQ(ptr.get(), p2);
    EXPECT_EQ(ptr2, NULL);
}

TEST(Assignment, PointerToObject) {
    int* p1 = new int[100];
    int* p2 = new int[10];
    UniquePointer<int> sptr(p1);
    sptr = p2;
    EXPECT_EQ(sptr.get(), p2);

    test_struct* sp1 = new test_struct(p1);
    UniquePointer <test_struct> sptr1(sp1);
    test_struct* sp2 = new test_struct(p2);
    sptr1 = sp2;
    EXPECT_EQ(sptr1.get(), sp2);
}

TEST(Operators, Dereference) {
    UniquePointer <test_struct> ptr;
    int* new_int = new int[10];
    test_struct* p2 = new test_struct(new_int);

    UniquePointer <test_struct> ptr2(p2);

    EXPECT_EQ(ptr2->_val, new_int);
    ptr2->multiply(0);
    EXPECT_EQ(p2->_val[0], 0);


}
TEST(Release, NoErrors) {
    int* new_int = new int[10];
    test_struct* sp = new test_struct(new_int);
    UniquePointer <test_struct> ptr(sp);
    EXPECT_EQ(ptr.get(), sp);
    ptr.release();
    EXPECT_EQ(ptr.get(), nullptr);
    UniquePointer <test_struct> ptr2(sp);
    EXPECT_EQ(ptr2.get(), sp);
}


TEST(Reset, NoErrors) {
    double* d = new double[100];
    UniquePointer <double> dptr;
    dptr.reset(d);
    EXPECT_EQ(dptr.get(), d);
}

TEST(Swap, NoErrors) {
    test_struct* sp = new test_struct(new int[100]);
    UniquePointer <test_struct> ptr1(sp);
    UniquePointer <test_struct> ptr2;
    ptr2.swap(ptr1);
    EXPECT_EQ(ptr2.get(), sp);
    EXPECT_EQ(ptr1.get(), nullptr);
}

TEST(MakeShared, NoErrors) {
    int* new_int = new int[10];
    auto ptr = make_unique<test_struct>(new_int);
    EXPECT_EQ(ptr.get()->_val, new_int);
    auto ptr2 = make_unique<double>(100);
    double t = 100;
    EXPECT_EQ(*ptr2, t);
}