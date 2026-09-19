#include <iostream>


int main() {

    const size_t i { 5 };
    const size_t& iref { i };

    std::cout << iref << '\n';
    return 0;
}
