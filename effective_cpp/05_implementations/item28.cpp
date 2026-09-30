// Item 28 Lab: Avoid returning "handles" to object internals
// Build:  g++ -std=c++17 -Wall -Wextra -fsanitize=address item28.cpp -o lab && ./lab
//         (or from cpp_sandbox/: cmake -B build && cmakerun ec28)
//
// HOW TO USE
//   1. Read an exercise, PREDICT what will happen.
//   2. Run it and compare.
//   3. Fix whatever's wrong.
//   4. Re-run and confirm the result matches the GOAL.

#include <iostream>
#include <memory>

// ===========================================================================
// EXERCISE 1 — the book's own Rectangle/Point example: a const member
// function returns a non-const reference to internal data, so callers can
// mutate a "const" object right through it.
// GOAL: after the mutation attempt, rec's x is still 0 (unchanged) — or,
// once fixed, that line simply doesn't compile at all anymore.
// ===========================================================================
struct Point
{
    int x, y;
};

struct RectPoints
{
    Point ulhc;
    Point lrhc;
};

class Rectangle
{
public:
    Rectangle(Point ul, Point lr) : data_(std::make_shared<RectPoints>(RectPoints{ ul, lr })) {}

    const Point& upperLeft() const { return data_->ulhc; }
    const Point& upperRight() const { return data_->lrhc; }

private:
    std::shared_ptr<RectPoints> data_;
};

void exercise1()
{
    std::cout << "Exercise 1\n";
    const Rectangle rec({ 0, 0 }, { 100, 100 });
    //rec.upperLeft().x = 50;   // rec is supposed to be const!
    std::cout << "  rec.upperLeft().x = " << rec.upperLeft().x << "\n";
}

// ===========================================================================
// EXERCISE 2 — the book's boundingBox example: a function returns an object
// by value (a temporary), and a caller keeps a pointer into one of that
// temporary's internals. The temporary is destroyed at the end of the full
// expression — the pointer is left dangling immediately.
// GOAL: no sanitizer report
// ===========================================================================
struct RectData
{
    Point ulhc;
    Point lrhc;
};

class SharedRectangle
{
public:
    SharedRectangle(Point ul, Point lr)
        : data_(std::make_shared<RectData>(RectData{ ul, lr })) {}


    const Point& upperLeft() const { return data_->ulhc; }

private:
    std::shared_ptr<RectData> data_;
};

SharedRectangle boundingBox()
{
    return SharedRectangle({ 10, 20 }, { 200, 200 });
}

void exercise2()
{
    std::cout << "Exercise 2\n";
    SharedRectangle rect = boundingBox();
    const Point *pUpperLeft = &(rect.upperLeft());
    //const Point *pUpperLeft = &(boundingBox().upperLeft());
    // boundingBox()'s temporary SharedRectangle is already destroyed here —
    // its RectData went with it.
    std::cout << "  pUpperLeft->x = " << pUpperLeft->x << "\n";
}

// ===========================================================================
int main()
{
    exercise1();
    exercise2();
}
