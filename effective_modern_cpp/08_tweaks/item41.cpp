// Item 41 Lab: Consider pass by value for copyable parameters that are
// cheap to move and always copied
// Build:  g++ -std=c++17 -Wall -Wextra item41.cpp -o lab && ./lab
//         (or from cpp_sandbox/: cmake -B build && cmakerun emc41)
//
// HOW TO USE
//   1. Read an exercise, PREDICT the copy/move counts it will print.
//   2. Run the program and compare.
//   3. Fix whatever's wrong (each exercise is written the "naive" way on purpose).
//   4. Re-run and confirm the counts match the GOAL line.

#include <iostream>
#include <string>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Tracker: a string wrapper that counts how it gets copied and moved.
// Don't modify this.
// ---------------------------------------------------------------------------
struct Tracker {
    static int copies, moves;
    std::string value;

    Tracker() = default;
    Tracker(const char* s) : value(s) {}
    Tracker(const Tracker& o) : value(o.value) { ++copies; }
    Tracker(Tracker&& o) noexcept : value(std::move(o.value)) { ++moves; }
    Tracker& operator=(const Tracker& o) { value = o.value; ++copies; return *this; }
    Tracker& operator=(Tracker&& o) noexcept { value = std::move(o.value); ++moves; return *this; }

    static void reset() { copies = moves = 0; }
    static void report(const char* label) {
        std::cout << "  " << label << ": copies=" << copies << " moves=" << moves << '\n';
    }
};
int Tracker::copies = 0;
int Tracker::moves = 0;

// ===========================================================================
// EXERCISE 1 — the book's own addName example: a pass-by-value parameter
// that's unconditionally stored. The one non-obvious part of this pattern
// is what you do with the parameter INSIDE the function body.
// GOAL: lvalue arg -> copies=1 moves=1, rvalue arg -> copies=0 moves=2
// (matches the book's own cost table for "Approach 3: pass by value")
// ===========================================================================
struct Widget1
{
    std::vector<Tracker> names;
    void addName(Tracker newName)
    { names.push_back(std::move(newName)); }
};

void exercise1()
{
    std::cout << "Exercise 1 (unconditional store)\n";
    Widget1 w;
    Tracker t("Bart");

    Tracker::reset();
    w.addName(t);
    Tracker::report("lvalue arg");

    Tracker::reset();
    w.addName(Tracker("Lisa"));
    Tracker::report("rvalue arg");
}

// ===========================================================================
// EXERCISE 2 — the book's caveat #4: pass by value is only worth it for
// parameters that are ALWAYS copied. Here, addName rejects names outside
// a length range — so the parameter sometimes gets constructed for
// nothing, paying a cost the reference-based "overloading" approach
// would never pay in the first place.
// GOAL: for a name that gets REJECTED, copies=0 moves=0 — rewrite
// addName so a rejected call costs nothing at all.
// ===========================================================================
struct Widget2
{
    std::vector<Tracker> names;
    static constexpr std::size_t minLen = 2, maxLen = 5;

    bool ok(const Tracker& t) const
    {
        return t.value.length() >= minLen && t.value.length() <= maxLen;
    }

    void addName(const Tracker& newName)
    {
        if (ok(newName)) names.push_back(newName);
    }
    void addName(Tracker&& newName)
    {
        if (ok(newName)) names.push_back(std::move(newName));
    }
};

void exercise2()
{
    std::cout << "\nExercise 2 (conditionally copied)\n";
    Widget2 w;

    Tracker::reset();
    Tracker tooLong("WayTooLongAName");
    w.addName(tooLong);
    Tracker::report("lvalue arg, rejected by length check");
}

// ===========================================================================
int main()
{
    exercise1();
    exercise2();
}
