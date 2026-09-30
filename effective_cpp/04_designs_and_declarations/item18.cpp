// Item 18 Lab: Make interfaces easy to use correctly and hard to use incorrectly
// Build:  g++ -std=c++17 -Wall -Wextra item18.cpp -o lab && ./lab
//         (or from cpp_sandbox/: cmake -B build && cmakerun ec18)
//
// HOW TO USE
//   1. Read an exercise, PREDICT what it will print.
//   2. Run it and compare.
//   3. Fix whatever's wrong.
//   4. Re-run and confirm the result matches the GOAL.

#include <iostream>
#include <memory>

// ===========================================================================
// EXERCISE 1 — the book's own example: a factory that returns a raw pointer
// forces every caller to remember to delete it. "Forgetting" is exactly the
// kind of client error a better interface should make impossible.
// GOAL: prints "liveCount after client code: 0"
// ===========================================================================
struct Investment
{
    static int liveCount;
    Investment() { ++liveCount; }
    ~Investment() { --liveCount; }
};
int Investment::liveCount = 0;

std::shared_ptr<Investment> createInvestment()
{
    return std::make_shared<Investment>();
}

void clientCode()
{
    std::shared_ptr<Investment> inv = createInvestment();
    std::cout << " liveCount right after createInvestment(): " << Investment::liveCount << '\n';
    // client forgets to delete inv — an easy, realistic mistake
}

// ===========================================================================
// EXERCISE 2 — the book's Date example: three plain ints in a constructor
// let a caller silently transpose month and day, and it compiles either way.
// The fix isn't to fix this one call — it's to change the constructor so a
// transposed call couldn't compile at all, for anyone, ever.
// GOAL: prints "date: 1995-3-30" (year-month-day), same as it does now —
// the point is to make a WRONG call impossible, not to change what a
// correct call looks like. Once you've changed the types, try transposing
// the two middle arguments in main() and see what happens when you rebuild.
// ====================================================================== =====
struct Year
{
    explicit Year (int y) 
        : val(y)
    {  }
    int val;
};

struct Month
{
    explicit Month (int m)
        : val(m)
    {  }
    int val;
};

struct Day    
{
    explicit Day (int d)
        : val(d)
    {  }
    int val;
}; 

class Date
{
public:
    Date(const Month& m, const Day& d, const Year& y)
        : month(m)
        , day(d)
        , year(y)
    {  }
    Month month;
    Day day;
    Year year;
};

// ===========================================================================
int main()
{
    std::cout << "Exercise 1 (factory returning a raw pointer)\n";
    {
        Investment::liveCount = 0;
        clientCode();
        std::cout << "  liveCount after client code: " << Investment::liveCount << "\n";
    }

    std::cout << "\nExercise 2 (three ints invite argument-order mistakes)\n";
    {
        Date d(Month(3), Day(30), Year(1995));   // March 30, 1995
        std::cout << "  date: " << d.year.val << "-" << d.month.val << "-" << d.day.val << "\n";
    }
}
