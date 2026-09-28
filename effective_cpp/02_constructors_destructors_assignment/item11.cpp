// Item 11 Lab: Handle assignment to self in operator=
// Build:  g++ -std=c++17 -Wall -Wextra -fsanitize=address item11.cpp -o lab && ./lab
//         (or from cpp_sandbox/: cmake -B build && cmakerun ec11)
//
// HOW TO USE
//   1. Read an exercise, PREDICT whether self-assignment is safe here.
//   2. Run it. AddressSanitizer aborts the whole program at the first
//      heap-use-after-free it finds — expected, not an accident.
//   3. Fix whatever's wrong. Each exercise asks for a DIFFERENT technique
//      from the Item, even though the bug looks identical each time.
//   4. Re-run — the next (still-broken) exercise will stop it there.
//   5. Once all three are fixed, the program runs to completion cleanly.

#include <iostream>

// ===========================================================================
// EXERCISE 1 — the book's exact scenario: a class holding a raw pointer to
// a heap resource. Self-assignment isn't always obviously `w = w;` — here
// it happens through aliasing, the same way the book's `*px = *py` does.
// Fix this one using an identity test.
// ===========================================================================
class WidgetV1
{
public:
    WidgetV1() : pb_(new int(0)) {}
    WidgetV1(const WidgetV1& other) : pb_(new int(*other.pb_)) {}
    ~WidgetV1() { delete pb_; }

    WidgetV1& operator=(const WidgetV1& rhs)
    {
        if(this == &rhs) return *this;
        delete pb_;
        pb_ = new int(*rhs.pb_);
        return *this;
    }

    int value() const { return *pb_; }

private:
    int* pb_;
};

void exercise1()
{
    std::cout << "Exercise 1\n";
    WidgetV1 w;
    WidgetV1& alias = w;
    w = alias;
    std::cout << "  w.value() = " << w.value() << "\n";
}

// ===========================================================================
// EXERCISE 2 — the exact same bug. This time, fix it WITHOUT an identity
// test — using careful statement ordering instead (don't release the old
// resource until after the new one is safely built).
// ===========================================================================
class WidgetV2
{
public:
    WidgetV2() : pb_(new int(0)) {}
    WidgetV2(const WidgetV2& other) : pb_(new int(*other.pb_)) {}
    ~WidgetV2() { delete pb_; }

    WidgetV2& operator=(const WidgetV2& rhs)
    {     
        int* oldValue = pb_;
        pb_ = new int(*rhs.pb_);
        delete oldValue;
        return *this;
    }

    int value() const { return *pb_; }

private:
    int* pb_;
};

void exercise2()
{
    std::cout << "Exercise 2\n";
    WidgetV2 w;
    WidgetV2& alias = w;
    w = alias;
    std::cout << "  w.value() = " << w.value() << "\n";
}

// ===========================================================================
// EXERCISE 3 — the exact same bug again. This time, fix it using
// copy-and-swap — a working swap() is already provided.
// ===========================================================================
class WidgetV3
{
public:
    WidgetV3() : pb_(new int(0)) {}
    WidgetV3(const WidgetV3& other) : pb_(new int(*other.pb_)) {}
    ~WidgetV3() { delete pb_; }

    void swap(WidgetV3& other)
    {
        int* tmp = pb_;
        pb_ = other.pb_;
        other.pb_ = tmp;
    }

    WidgetV3& operator=(const WidgetV3& rhs)
    {
        WidgetV3 temp(rhs);
        swap(temp);
        return *this;
    }

    int value() const { return *pb_; }

private:
    int* pb_;
};

void exercise3()
{
    std::cout << "Exercise 3\n";
    WidgetV3 w;
    WidgetV3& alias = w;
    w = alias;
    std::cout << "  w.value() = " << w.value() << "\n";
}

// ===========================================================================
int main()
{
    exercise1();
    exercise2();
    exercise3();
    std::cout << "All clean — no sanitizer report above this line.\n";
}
