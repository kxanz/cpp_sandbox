// TOPIC std::dequeue in C++ !! (Double Ended Queue)

// Notes:
// 0 std::deque is an indexed sequence container
// 1 it allows fast insertion at both beginning and end 
// 2 unlike vector elements of deque are not sorted contigously
// 3 it uses individual allocated fixed array, with addional bookeeping, meaning index 
//   based access to deque must peform two pointer dereference but in vector we get in one
//   dereference
// 4 The storage of a dequeue is automatically expanded and contracted as needed
// 5 Expansion of deque is cheaper than expansion of vector
// 6 A deque holding just one element as to alllocate its full internal array (eg 8 times
//   the object size on 64-bit libstdc++; 16 times the object size or 4096 bytes
//   which is larger, on 64 bit libc++).
//


// Timer Complexity
// Random Access - Constant O(1)
// Instertion or removal of elements at the end or beginning - constant O(1)
// Insertion or romval of elements - linear O(n)
//           in         in 
//             | | | | |
//           out       out

#include <iostream>
#include <deque>
using namespace std;

void print(std::deque<int>& dqu) {for (int num : dqu) cout << num << " "; cout << endl; }

int main() 
{
    std::deque<int> dqu = {2, 3, 4};
    dqu.push_front(1);
    dqu.push_back(5);
    print(dqu);
{   
    std::deque<int> dqu = {2, 3, 4};
    dqu.pop_front();
    dqu.pop_back();
    print(dqu);
}

    return 0;
}