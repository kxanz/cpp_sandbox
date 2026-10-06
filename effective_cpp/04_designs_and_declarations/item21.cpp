// Item 21 Lab: Don't try to return a reference when you must return an object
// Build:  g++ -std=c++17 -Wall -Wextra -fsanitize=address,undefined item21.cpp -o lab && ./lab
//         (or from cpp_sandbox/: cmake -B build && cmakerun ec21)
//
// HOW TO USE
//   1. Read an exercise, PREDICT what it will print.
//   2. Run it and compare — notice that nothing crashes by default; you
//      just get a visibly WRONG value back. That silent wrongness is the
//      whole danger the book is warning about.
//   3. Fix whatever's wrong.
//   4. Re-run and confirm the result matches the GOAL.
//
// Optional, for Exercise 1 specifically: you can also turn the dangling
// reference into a hard crash, pinpointed to the exact line, with:
//   ASAN_OPTIONS=detect_stack_use_after_return=1 ./lab
// That's a stronger confirmation once you think it's fixed — the primary
// signal to watch while fixing it is still the printed value being wrong.

#include <iostream>

// ===========================================================================
// EXERCISE 1 — the book's own example: returning a reference to a LOCAL
// object. `result` is destroyed the instant the function returns, so the
// reference handed back refers to memory that's already gone.
// GOAL: prints "3/10", not garbage.
// ===========================================================================
struct Rational
{
    int n, d;
};

inline const Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational( lhs.n * rhs.n, lhs.d * rhs.d );
    
}

void exercise1()
{
    std::cout << "Exercise 1 (reference to a local)\n";
    Rational a{ 1, 2 }, b{ 3, 5 };
    const Rational r = a * b;
    std::cout << "  " << r.n << "/" << r.d << " (expected 3/10)\n";
}

// ===========================================================================
// EXERCISE 2 — returning a reference to a HEAP object that nobody ever
// deletes. There's no reasonable way for a caller to get at the pointer
// hiding behind the returned reference, so it can never be freed.
// GOAL: after a/b go out of scope, liveCount == 0 (nothing leaked).
// ===========================================================================
struct CountedRational
{
    int n, d;
    static int liveCount;
    CountedRational(int n_, int d_) : n(n_), d(d_) { ++liveCount; }
    ~CountedRational() { --liveCount; }
};
int CountedRational::liveCount = 0;

const CountedRational multiplyLeaked(const CountedRational& lhs, const CountedRational& rhs)
{
    CountedRational result(lhs.n * rhs.n, lhs.d * rhs.d);
    return result;
}

void exercise2()
{
    std::cout << "\nExercise 2 (reference to a leaked heap object)\n";
    CountedRational::liveCount = 0;
    {
        CountedRational a{ 1, 2 }, b{ 3, 5 };
        const CountedRational& r = multiplyLeaked(a, b);
        std::cout << "  " << r.n << "/" << r.d << "\n";
    }
    // a and b are destroyed by now — whatever's left in liveCount is a leak.
    std::cout << "  liveCount after a/b go out of scope: " << CountedRational::liveCount << " (expected 0)\n";
}

// ===========================================================================
// EXERCISE 3 — the book's "one static isn't enough" trap: every call
// reuses the SAME static object, so two calls alive in one expression end
// up comparing that one object against itself.
// GOAL: (a*b) == (c*d) correctly evaluates to false for these values.
// ===========================================================================
bool rationalEquals(const Rational& lhs, const Rational& rhs)
{
    return lhs.n * rhs.d == rhs.n * lhs.d;
}

const Rational multiplyStatic(const Rational& lhs, const Rational& rhs)
{
    static Rational result;
    result.n = lhs.n * rhs.n;
    result.d = lhs.d * rhs.d;
    return result;
}

void exercise3()
{
    std::cout << "\nExercise 3 (shared static — always compares equal)\n";
    Rational a{ 1, 2 }, b{ 3, 5 }, c{ 9, 9 }, d{ 9, 9 };
    // a*b = 3/10, c*d = 1/1 — these must NOT be equal.
    bool same = rationalEquals(multiplyStatic(a, b), multiplyStatic(c, d));
    std::cout << "  (a*b) == (c*d): " << std::boolalpha << same << " (expected false)\n";
}

// ===========================================================================
int main()
{
    exercise1();
    exercise2();
    exercise3();
}
