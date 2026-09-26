#include <iostream>


struct Date {
    int year;
    int month;
    int day;

    static int mode;
};

struct Foo {
    int a{};
    int b{};
    int c{};
};

int main() {
    Foo f1{ .a{ 1 }, .b{ 2 } }; // 1
    Foo f2{ .a{ 1 }, .c{ 2 } }; // 2
    Foo f3{ .b{ 1 }, .c{ 2 } }; // 3
    Foo f4{ .a = 1, .b = 2 };   // 4
    Foo f5{ .a{ 1 }, .b = 2 };  // 5
    Foo f6{ .b{ 1 }, .a{ 2 } }; // 6 wrong order rule
    Foo f7{ .b{ 1 } };          // 7



    //Date d1 { .mode = 10; }            // err, mode is static!
    Date d2 { .day = 1, .year = 2010 }; // err, out of order!
    Date d3 { 2050, .month = 12 };      // err, mix!
    //Date d4 { .mh.min = 55 };           // err, nested!


};