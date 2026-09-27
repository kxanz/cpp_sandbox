// Item 25 Lab: std::move on rvalue references, std::forward on universal references
// Build:  g++ -std=c++17 -Wall -Wextra item25.cpp -o lab && ./lab
//         (or from cpp_sandbox/: cmake -B build && cmakerun emc25)
//
// HOW TO USE
//   1. Read an exercise, PREDICT the copy/move counts it will print.
//   2. Run the program and compare.
//   3. Fix the code where it says TODO (each is written the "naive" way on purpose).
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
// EXERCISE 1 — rvalue reference parameter
// rhs is bound to an object that may be moved from... but rhs itself is an lvalue.
// GOAL: copies=0 moves=2
// ===========================================================================

struct Person 
{
Tracker name, email;
Person(Tracker n, Tracker e) 
    : name(std::move(n))
    , email(std::move(e)) 
{  }

Person(Person&& rhs)
    : name(std::move(rhs.name)) //TODO
    , email(std::move(rhs.email))     // TODO
{  }
};

// ===========================================================================
// EXERCISE 2 — universal reference parameter
// Callers pass both lvalues and rvalues here.
// GOAL: lvalue call -> copies=1 moves=0, AND the caller's string must survive.
//       rvalue call -> copies=0 moves=1
// Bonus: after fixing, temporarily swap in std::move and watch what
//        happens to `keepMe` in main(). That's why std::move on a
//        universal reference is "bad, bad, bad".
// ===========================================================================

struct Account {
Tracker owner;

template<typename T>
void setOwner(T&& newOwner) 
{
    owner = std::forward<T>(newOwner);      // TODO
}
};

// ===========================================================================
// EXERCISE 3 — using the parameter more than once
// We want to log the value, THEN store it. Only the final use may
// move/forward, otherwise we'd log a gutted object.
// GOAL: lvalue -> copies=1 (the store), rvalue -> copies=0 moves=1
//       AND the log line must print the real text, not an empty string.
// ===========================================================================
std::vector<Tracker> history;

void logIt(const Tracker& t) { std::cout << "    log: \"" << t.value << "\"\n"; }

template<typename T>
void logAndStore(T&& item) 
{
    logIt(item);                     // leave this alone
    history.push_back(std::forward<T>(item));         // TODO (this is the LAST use)
}

// ===========================================================================
// EXERCISE 4 — returning an rvalue-reference parameter by value
// lhs is known to be a temporary we can recycle.
// GOAL: copies=0 moves=1
// ===========================================================================
Tracker appendTo(Tracker&& lhs, const Tracker& rhs) 
{
    lhs.value += rhs.value;
    return std::move(lhs);                      // TODO
}

// ===========================================================================
// EXERCISE 5 — returning a universal-reference parameter by value
// GOAL: lvalue arg -> copies=1 moves=0, rvalue arg -> copies=0 moves=1
// ===========================================================================
template<typename T>
Tracker shout(T&& t) 
{
    t.value += "!";
    return std::forward<T>(t);                        // TODO
}

// ===========================================================================
// EXERCISE 6 — the trap: a LOCAL variable
// This one is already CORRECT. Your job: add std::move to the return,
// re-run, and explain why the counts get WORSE (hint: RVO).
// Also try compiling with -Wpessimizing-move / -Wall on clang or gcc.
// ===========================================================================
Tracker makeTracker() 
{
    Tracker t("local");
    t.value += " object";
    return std::move(t);                        // try: return std::move(t);  then undo it
}

// ===========================================================================
int main() {
    std::cout << "Exercise 1 (rvalue ref -> std::move)\n";
    {
        Person p1(Tracker("Ada"), Tracker("ada@x.com"));
        Tracker::reset();
        Person p2(std::move(p1));
        Tracker::report("move-construct Person");
    }

    std::cout << "\nExercise 2 (universal ref -> std::forward)\n";
    {
        Account a;
        Tracker keepMe("Grace");
        Tracker::reset();
        a.setOwner(keepMe);
        Tracker::report("lvalue");
        std::cout << "    caller's keepMe is still: \"" << keepMe.value << "\"\n";

        Tracker::reset();
        a.setOwner(Tracker("Linus"));
        Tracker::report("rvalue (ignore the temp's construction)");
    }

    std::cout << "\nExercise 3 (forward only on the last use)\n";
    {
        history.reserve(10);         // so vector growth doesn't add moves
        Tracker kept("kept");
        Tracker::reset();
        logAndStore(kept);
        Tracker::report("lvalue");

        Tracker::reset();
        logAndStore(Tracker("temp"));
        Tracker::report("rvalue");
    }

    std::cout << "\nExercise 4 (return rvalue-ref param)\n";
    {
        Tracker suffix(" world");
        Tracker::reset();
        Tracker r = appendTo(Tracker("hello"), suffix);
        Tracker::report("appendTo");
        std::cout << "    result: \"" << r.value << "\"\n";
    }

    std::cout << "\nExercise 5 (return universal-ref param)\n";
    {
        Tracker x("hey");
        Tracker::reset();
        Tracker r1 = shout(x);
        Tracker::report("lvalue");

        Tracker::reset();
        Tracker r2 = shout(Tracker("yo"));
        Tracker::report("rvalue");
    }

    std::cout << "\nExercise 6 (local variable: DON'T std::move)\n";
    {
        Tracker::reset();
        Tracker r = makeTracker();
        Tracker::report("makeTracker");
    }
}
