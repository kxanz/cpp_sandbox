// Item 24 Lab: Declare non-member functions when type conversions should
// apply to all parameters
// Build:  g++ -std=c++17 -Wall -Wextra item24.cpp -o lab && ./lab
//         (or from cpp_sandbox/: cmake -B build && cmakerun ec24)
//
// HOW TO USE
//   1. Read the exercise, PREDICT which of the two multiplications below
//      will compile.
//   2. Build it — it should compile clean, with the second call still
//      commented out.
//   3. Uncomment the marked line and rebuild. Read the compiler error —
//      that error IS the bug this item is about, not a mistake in the lab.
//   4. Fix operator* so BOTH orders compile and print the same result.
//   5. Re-run and confirm the GOAL.

#include <iostream>

// ===========================================================================
// EXERCISE 1 — the book's own Rational example. Rational's constructor is
// deliberately non-explicit, so an int can implicitly convert to a
// Rational — but only when the Rational is already on one particular side
// of operator*.
// GOAL: both "oneHalf * 2" and "2 * oneHalf" compile and print "2/2".
// ===========================================================================
class Rational
{
public:
    Rational(int numerator = 0, int denominator = 1) : n(numerator), d(denominator) {}

    // A member operator* only lets the LEFT operand undergo the implicit
    // int-to-Rational conversion; compilers need a non-member search to
    // consider converting the RIGHT (first) operand too.
    const Rational operator*(const Rational& rhs) const
    {
        return Rational(n * rhs.n, d * rhs.d);
    }

    int numerator() const { return n; }
    int denominator() const { return d; }

private:
    int n, d;
};

void exercise1()
{
    std::cout << "Exercise 1 (mixed-mode multiplication)\n";
    Rational oneHalf(1, 2);

    Rational result = oneHalf * 2;
    std::cout << "  oneHalf * 2 = " << result.numerator() << "/" << result.denominator() << "\n";

    // Uncomment these two lines and rebuild — read the error before fixing anything:
    Rational result2 = oneHalf.operator*(2);
    std::cout << "  2 * oneHalf = " << result2.numerator() << "/" << result2.denominator() << "\n";
}

// ===========================================================================
int main()
{
    exercise1();
}
