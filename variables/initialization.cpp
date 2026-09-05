#include <iostream>

int main() {

    int f; // default initialization // gargabe value

    int x; //assignment
    x = 2;

    int b { 5 }; // direct list initialization
    int q = { 5 }; // copy list initialization

    int r = ( 5 );

    int a {}; //zero initialization or value initialization
    int z = 5; // copy initialization

    [[maybe_unused]]double pi { 3.4 };

    std::cout<< b;
    

    return 0;
}