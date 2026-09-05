#include <array>
#include <iostream>
#include <string_view>
#include <string>

/*
 * Pointer Reference Derived Classes
 */

class Animal
{
protected:
    std::string name_;
    std::string speak_;
    
    Animal(std::string name, std::string speak)
        : name_ { name }
        , speak_ { speak }
    {  }

    Animal(const Animal&) = delete;
    Animal& operator=(const Animal&) = delete;

public:
    std::string_view getName() const { return name_; }
    std::string_view speak() const { return speak_; }


};

class Cat: public Animal
{
public:
    Cat(std::string name)
        : Animal { name, "Meow" }
    {  }
};

class Dog: public Animal
{
public:
    Dog(std::string name)
        : Animal { name, "Woof" }
    {  }
};

int main()
{
    const Cat fred{ "Fred" };
    const Cat misty{ "Misty" };
    const Cat zeke{ "Zeke" };

    const Dog garbo{ "Garbo" };
    const Dog pooky{ "Pooky" };
    const Dog truffle{ "Truffle" };

    // Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
    const auto animals{ std::to_array<const Animal*>({ &fred, &garbo, &misty, &pooky, &truffle, &zeke }) };

    // Before C++20, with the array size being explicitly specified
    // const std::array<const Animal*, 6> animals{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };

    for (const auto animal : animals)
    {
        std::cout << animal->getName() << " says " << animal->speak() << '\n';
    }

    return 0;
}
