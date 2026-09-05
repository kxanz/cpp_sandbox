#include <iostream>
#include <bitset>
/*
test() allows us to query where a bit is a 0 or 1 
set() allows us to turn a bit on(will not do tnothing is its on)
rest() allows us to turn off a bit
flip() allows us to flip a bit value from 0 to a 1 vice versa

Querying:
size() returns the number of bits in the bitset
count() returns the number  of bits in the bitset that are set to true
all() return boolean indicating wheter all bits are set to true
any() return boolean indicating whether any bits are set to true
none() returns a boolean indicating whether no bits are to true
*/

int main()
{
    std::bitset<4> bitsOne { 0b1001 };
    std::bitset<8> bits {};
    std::cout << bits << bits.set(3) << '\n';
    std::cout << bits.size() << '\n';
    std::cout << bitsOne << '\n'; 
    return 0; 
}  
