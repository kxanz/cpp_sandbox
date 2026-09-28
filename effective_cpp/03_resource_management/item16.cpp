// Item 16 Lab: Use the same form in corresponding uses of new and delete
// Build:  g++ -std=c++17 -Wall -Wextra item16.cpp -o lab && ./lab
//         (or from cpp_sandbox/: cmake -B build && cmakerun ec16)
//
// HOW TO USE
//   1. Read an exercise, PREDICT whether it's a mismatch.
//   2. Compile it. -Wall/-Wextra already catch this class of bug at
//      COMPILE TIME (clang's -Wmismatched-new-delete) — you don't need a
//      sanitizer for this one, a warning is the reliable signal here.
//   3. Fix whatever's wrong.
//   4. Recompile and confirm that specific warning is gone.
//   5. Once all three are fixed, it compiles with zero warnings and runs
//      to completion — that's the final GOAL.
//
// Optional, for the curious: this IS also a real runtime bug ASan can catch
// (it's genuine undefined behavior), but on this platform that specific
// check is off by default — you'd need
// ASAN_OPTIONS=alloc_dealloc_mismatch=1 ./lab (built with -fsanitize=address)
// to see it abort at runtime too. The compiler warning is the dependable
// signal; treat the sanitizer as a bonus, not the primary tool, for this item.

#include <iostream>

// ===========================================================================
// EXERCISE 1 — new[] paired with plain delete
// GOAL: no compiler warning
// ===========================================================================
void exercise1()
{
    std::cout << "Exercise 1\n";
    int* values = new int[10];
    values[0] = 1;
    delete[] values;
}

// ===========================================================================
// EXERCISE 2 — the reverse: plain new paired with delete[]
// GOAL: no compiler warning
// ===========================================================================
void exercise2()
{
    std::cout << "Exercise 2\n";
    int* single = new int;
    *single = 42;
    delete single;
}

// ===========================================================================
// EXERCISE 3 — a class with two constructors, both allocating the same
// member. The book's warning: when a class has multiple constructors that
// all initialize the same pointer, EVERY one of them must use the same form
// of new, because the destructor can only pick one form of delete.
// GOAL: no compiler warning
// ===========================================================================
class Buffer
{
public:
    explicit Buffer(std::size_t n) : data_(new int[n]) {}
    Buffer() : data_(new int[1]) {}

    ~Buffer() { delete[] data_; }

private:
    int* data_;
};

void exercise3()
{
    std::cout << "Exercise 3\n";
    Buffer b(5);
}

// ===========================================================================
int main()
{
    exercise1();
    exercise2();
    exercise3();
    std::cout << "All clean — no sanitizer report above this line.\n";
}
