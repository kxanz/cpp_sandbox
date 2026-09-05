#include <iostream>
#include <bit>
/*
reinterpret_cast: reinterpreting the bit patter of an object

bit_cast: designing to avoid violating the aliasing rules
- reinterpreting the bit pattern of the soruce object into the type of 
  destination object. it does by creating a bitwise copy of source 
  representation into destination object without chaning the bit 
  patter

*/
template <class To, class From>
constexpr To bit_cast(const From& from) noexcept; 

int main() {


    return 0;
}
   
