#include <iostream>
#include <ostream>
#include <string>

class Fruit {
    private: 
        std::string name_;
        std::string color_;

    public: 
        Fruit(std::string_view name = " ", std::string_view color = " " )
            : name_{ name } 
            , color_{ color }
        { }
    const std::string& getName() const { return name_; }
    const std::string& getColor() const { return color_; }

};
class Apple : public Fruit {
    private:
        double fiber_;
    public:
        Apple (std::string_view name = " ", std::string_view color = " ", double fiber = 0.0)
        : Fruit{ name, color }
        , fiber_ { fiber }
    { }
    
    double getFiber() const { return fiber_; }
};

std::ostream& operator << (std::ostream& out, const Apple& a)
{
    out << "Apple(" << a.getName() << ", " << a.getColor() << ", " << a.getFiber() << ')';
    return out;
}

class Banana : public Fruit {
    public:
        Banana(std::string_view name = " ", std::string_view color = " " )
            : Fruit { name, color }
    { }
};

std::ostream& operator << (std::ostream& out, const Banana& b)
{
    out << "Apple(" << b.getName() << ", " << b.getColor()  << ')';
    return out;
}


int main() {

    const Apple a { "Red delicious", "Red", 4.2};
    std::cout << a << '\n';

    const Banana b { "Cavendish", "yellow" };
    std::cout << b << '\n';

    return 0;
}