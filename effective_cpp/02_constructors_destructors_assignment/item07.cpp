// Item 7 Lab: Declare destructors virtual in polymorphic base classes
// Build:  g++ -std=c++17 -Wall -Wextra item07.cpp -o lab && ./lab
//         (or from cpp_sandbox/: cmake -B build && cmakerun ec07)
//
// HOW TO USE
//   1. Read an exercise, PREDICT what it will print.
//   2. Run the program and compare.
//   3. Fix whatever's wrong (each exercise is written the "naive" way on purpose).
//   4. Re-run and confirm the result matches the GOAL line.

#include <iostream>

// ===========================================================================
// EXERCISE 1 — the book's own running example: TimeKeeper / AtomicClock
// A factory function hands back a base-class pointer to a heap-allocated
// derived object. Deleting a derived object through a base pointer with a
// non-virtual destructor is undefined behavior — in practice, only the base
// part gets destroyed; the derived part's destructor never runs.
// GOAL: prints "AtomicClock destroyed" before the program ends
// ===========================================================================
class TimeKeeper
{
public:
    TimeKeeper() {}
    virtual ~TimeKeeper() { std::cout << "TimeKeeper destroyed\n"; }
};

class AtomicClock : public TimeKeeper
{
public:
    AtomicClock() {}
    ~AtomicClock() { std::cout << "AtomicClock destroyed\n"; }
};

TimeKeeper* makeTimeKeeper()
{
    return new AtomicClock();
}

// ===========================================================================
// EXERCISE 2 — the flip side: don't add virtual where it isn't earned
// Point isn't meant to be used polymorphically — it has no virtual functions
// at all. Adding a virtual destructor anyway costs every Point object a
// vptr, growing its size even though nothing needs one.
// This exercise is read-only: nothing to fix, just predict then check.
// ===========================================================================
struct PointPlain
{
    int x, y;
    ~PointPlain() {}
};

struct PointWithVirtualDtor
{
    int x, y;
    virtual ~PointWithVirtualDtor() {}
};

// ===========================================================================
int main()
{
    std::cout << "Exercise 1 (delete derived object through base pointer)\n";
    {
        TimeKeeper* tk = makeTimeKeeper();
        delete tk;
    }

    std::cout << "\nExercise 2 (cost of a gratuitous virtual destructor)\n";
    {
        std::cout << "  sizeof(PointPlain)           = " << sizeof(PointPlain) << " bytes\n";
        std::cout << "  sizeof(PointWithVirtualDtor) = " << sizeof(PointWithVirtualDtor) << " bytes\n";
        std::cout << "  (the difference is the vptr every virtual function costs the object)\n";
    }
}
