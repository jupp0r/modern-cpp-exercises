#pragma once

#include <string>

// Task 1 - final classes
// Make sure no other class can inherit from Data
struct Data {
    int foo;
};

// Task 2 - override methods
// B is supposed to replace the implementation of the foo() method in A.
// Make the test pass. Use the override keyboard to catch this mistake in the future.
struct A {
    virtual int foo() {
        return 1;
    }
};

struct B : public A {
    int foo() const {
        return 2;
    }
};

// Task 3 - delete methods
// Use the delete keyword to prevent this struct from being copied.
// (Hint - delete copy constructor and copy assignment operator)
struct NonCopyable
{
    int a;
};

// Task 4 - default keyword
// struct Implementation implements Interface. This construct can leak memory when an instance
// of Implementation should be freed via a poiner to Interface. Use the default keyword in order
// to fix the leak without compromising performance (compiler generated methods are guaranteed to be inlined).
struct Interface {
    virtual int foo() = 0;
};

struct Implementation : public Interface {
    int foo() override {
        return 1;
    }
};

// Task 5 - delegating constructors
// This code contains a lot of duplication, which allowed errors to creep in!
// Fix the errors and refactor constructors using delegating constructors to make
// it harder to introduce errors like this in the future.
struct C {
    C()
            : intField(5), stringField("hello")
    {}

    C(int i)
            : intField(i)
    {}

    C(std::string str)
            : stringField(str)
    {}


    C(int i, std::string str)
            : intField(i)
            , stringField(str)
    {}

    int intField;
    std::string stringField;
};
