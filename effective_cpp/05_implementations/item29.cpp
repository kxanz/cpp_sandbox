// Item 29 Lab: Strive for exception-safe code
// Build:  g++ -std=c++17 -Wall -Wextra -fsanitize=address item29.cpp -o lab && ./lab
//         (or from cpp_sandbox/: cmake -B build && cmakerun ec29)
//
// HOW TO USE
//   1. Read an exercise, PREDICT what state things will be in after the
//      exception is caught.
//   2. Run it and compare against the GOAL line.
//   3. Fix whatever's wrong. Each exercise demonstrates a DIFFERENT concern
//      from the Item, even though all three involve the same kind of throw.
//   4. Re-run and confirm the result matches the GOAL.

#include <iostream>
#include <stdexcept>
#include <memory>

// ===========================================================================
// EXERCISE 1 — resource leak: an exception skips a cleanup step that was
// only reachable by falling through to the end of the function normally.
// GOAL: prints "locked = false"
// ===========================================================================
bool locked = false;

void riskyOperation(bool bad)
{
    if (bad) throw std::runtime_error("something went wrong");
}

struct LockGuard
{
    LockGuard() { locked = true; }
    ~LockGuard() { locked = false; }
};

void exercise1()
{
    std::cout << "Exercise 1\n";
    locked = true;
    try {
        LockGuard guard;
        riskyOperation(true);
    } catch (const std::exception&) {
        std::cout << "  caught exception\n";
    }
    std::cout << "  locked = " << std::boolalpha << locked << "\n";
}

// ===========================================================================
// EXERCISE 2 — data corruption from statement ordering: the resource is
// released and a counter is updated BEFORE the operation that might fail.
// GOAL: prints "changes = 0", program does not crash on exit
// ===========================================================================
struct Image
{
    static int liveCount;
    explicit Image(bool bad) { if (bad) throw std::runtime_error("bad image"); ++liveCount; }
    ~Image() { --liveCount; }
};
int Image::liveCount = 0;

class Menu
{
public:
    Menu() : image_(new Image(false)), changes_(0) {}

    void changeBackground(bool bad)
    {
       image_.reset(new Image(bad));
        ++changes_;
    }

    int changes() const { return changes_; }

private:
    std::shared_ptr<Image> image_;
    int changes_;
};

void exercise2()
{
    std::cout << "Exercise 2\n";
    Menu menu;
    try {
        menu.changeBackground(true);
    } catch (const std::exception&) {
        std::cout << "  caught exception\n";
    }
    std::cout << "  changes = " << menu.changes() << "\n";
}

// ===========================================================================
// EXERCISE 3 — the strong guarantee via copy-and-swap: two pieces of state
// (an id and a label describing it) must always agree with each other. The
// naive version updates them one at a time, so a throw between the two
// updates leaves them describing two different things.
// GOAL: prints "id and label agree"
// ===========================================================================
#include <string>

class Record
{
public:
    Record() : id_(0), label_("none") {}

    void update(int newId, bool bad)
    {
        Record temp(*this);
        temp.id_ = newId;
        if (bad) throw std::runtime_error("update failed");
        temp.label_ = "record #" + std::to_string(newId);
        swap(temp);
    }

    void swap(Record& other)
    {
        std::swap(id_, other.id_);
        std::swap(label_, other.label_);
    }

    int id() const { return id_; }
    const std::string& label() const { return label_; }

private:
    int id_;
    std::string label_;
};

void exercise3()
{
    std::cout << "Exercise 3\n";
    Record r;
    try {
        r.update(7, true);
    } catch (const std::exception&) {
        std::cout << "  caught exception\n";
    }
    bool consistent = (r.label() == "record #" + std::to_string(r.id())) || (r.id() == 0 && r.label() == "none");
    std::cout << "  " << (consistent ? "id and label agree" : "id and label DISAGREE") << "\n";
}

// ===========================================================================
int main()
{
    exercise1();
    exercise2();
    exercise3();
}
