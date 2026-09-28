// Item 14 Lab: Declare functions noexcept if they won't emit exceptions
// Build:  g++ -std=c++17 -Wall -Wextra item14.cpp -o lab && ./lab
//         (or from cpp_sandbox/: cmake -B build && cmakerun emc14)
//
// HOW TO USE
//   1. Read an exercise, PREDICT what it will print.
//   2. Run the program and compare.
//   3. Fix whatever's wrong (each exercise is written the "naive" way on purpose).
//   4. Re-run and confirm the result matches the GOAL line.

#include <iostream>
#include <vector>
#include <type_traits>
#include <utility>

// ===========================================================================
// EXERCISE 1 — the headline reason noexcept exists: std::vector reallocation
// Widget's move constructor is NOT marked noexcept. When the vector below
// grows past its reserved capacity, std::vector can't safely trust an
// unmarked move constructor not to throw partway through (that would break
// push_back's strong exception guarantee), so it falls back to copying the
// existing elements into the new buffer instead of moving them.
// GOAL: copies=0 moves=1
// ===========================================================================
struct Widget 
{
    static int copies, moves;
    int value;

    Widget(int v) : value(v) {}
    Widget(const Widget& o) : value(o.value) { ++copies; }
    Widget(Widget&& o) noexcept : value(o.value) { ++moves; } 
    static void reset() { copies = moves = 0; }
    static void report(const char* label) {
        std::cout << "  " << label << ": copies=" << copies << " moves=" << moves << '\n';
    }
};
int Widget::copies = 0;
int Widget::moves = 0;

// ===========================================================================
// EXERCISE 2 — noexcept is part of the interface, not inferred from the body
// area() only multiplies two ints — nothing here can throw — but the
// compiler doesn't examine the body to decide noexcept-ness for you; you
// have to declare it.
// GOAL: prints true
// ===========================================================================
struct Rectangle 
{
    int w, h;
    int area() const noexcept { return w * h; } };

// ===========================================================================
// EXERCISE 3 — a conditionally-noexcept function
// swapValues should only promise noexcept if swapping T is actually
// guaranteed not to throw (this is the same pattern the real std::swap
// uses internally).
// GOAL: prints true (for int)
// ===========================================================================
template<typename T>
void swapValues(T& a, T& b) noexcept
(std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>)  
{
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

// ===========================================================================
// EXERCISE 4 — destructors are noexcept by default; nothing to fix here.
// This is here so you can SEE the default Item 14 relies on you knowing.
// ===========================================================================
struct Plain 
{
    ~Plain() {}
};

// ===========================================================================
int main()
{
    std::cout << std::boolalpha;

    std::cout << "Exercise 1 (noexcept move ctor -> vector reallocation)\n";
    {
        std::vector<Widget> v;
        v.reserve(1);
        v.emplace_back(1);
        Widget::reset();
        v.emplace_back(2);          // forces exactly one reallocation
        Widget::report("push_back causing reallocation");
    }

    std::cout << "\nExercise 2 (mark area() noexcept)\n";
    {
        Rectangle r{3, 4};
        std::cout << "  area() is noexcept: " << noexcept(r.area()) << '\n';
    }

    std::cout << "\nExercise 3 (conditionally noexcept swap)\n";
    {
        int x = 1, y = 2;
        std::cout << "  swapValues(int,int) is noexcept: " << noexcept(swapValues(x, y)) << '\n';
        swapValues(x, y);
        std::cout << "  x=" << x << " y=" << y << '\n';
    }

    std::cout << "\nExercise 4 (destructors are noexcept by default)\n";
    {
        std::cout << "  ~Plain() is noexcept: " << std::is_nothrow_destructible_v<Plain> << '\n';
        std::cout << "  (nothing to fix here)\n";
    }
}
