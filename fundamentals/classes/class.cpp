#include <iostream>
#include <ostream>

//Creating stream-anebled Class
struct Dog {
    int age_;
    std::string name_;

};
std::ostream& operator<<(std::ostream& sm, const Dog& d) {
    sm << "My name is" << d.name_ << " and my age is " << d.age_ << std::endl;
    return sm;
}

std::istream& operator >> (std::istream& sm, Dog& d) {
    sm >> d.age_;
    sm >> d.name_;
}

int main() {
    Dog d{2, "Bob"}; //universal initialization
    std::cout << d;

    std::cin >> d;
    std::cout << d;
    
    return 0;
}