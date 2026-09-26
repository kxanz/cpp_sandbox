//Topic: std::deque in C++

// Notes
// 0 std::queue class is a container adapter that gives the programmer the functionlity of a queue
// 1 queue is FIFO (first in, first out,) data structure
// 2 std::queue provides only specific set of fucntions
// 3 std::queue allows to push(insert) at the back and pop(remove) from front 
// 4 std::queue gives front, back, push, pop, empty, size.

// Front | 1 | 2 | 3 | 4 | 5 | Rean
//          FIFO

#include <iostream>
#include <queue>
using namespace std;

//Program
void print(std::queue<int> que)
{
    while(!que.empty()) 
    {
        cout << que.front() << endl;
        que.pop(); // remove from front
    }
}
int main() {

    std::queue<int> que;

    que.push(2);
    que.push(3);
    que.push(4);

    print(que);

    return 0;
}