// TOPIC std::stack In C++

// Notes::
// 0 std::stack calss is a container adapter (another container dequeue) that gives the programmer the functionality of a stack
// 1 internally it used std::deque STL container
// 2 It is LIFO (last in, first out) data structure
// 3 std::stack allows to push(insert) and pop(remove) only from the back

// Functions Provided
// empty() - returns wether the stack is empty - Time complexity : O(1);
// size() -  returns the size of the stack : Time complexity : O(1);
// top() -  returns a reference to the top most element of the stack : Time complexity : O(1);
// push() - adds the elemet 'g' at the top of the stack : Time complexity : O(1);
// pop()  - deletes the top most element of the stack : Time complexity : O(1);

//Program
#include <stack>
#include <iostream>
using namespace std;

void print(std::stack<int> stk)
{
    while(!stk.empty()) 
    {
        cout<< stk.top() << endl;
        stk.pop(); //remove from the back
    }
}

int main() {
                    //overload std::vector<int>
    std::stack<int> stk;

    stk.push(2);
    stk.push(3);
    stk.push(4);

    stk.pop();

    print(stk);

    cout << stk.size() << endl;

    return 0;
}

/*
    Container Adapter 
    - Provide a restricted interface to meet special needs
    - Implemented with fundamental container classes
    1. stack: LIFO, push(), pop(), top()
    2. deque: FiFo, push(), pop(), front(), back()
    3. priority queue: first item always has the greatest priority push(), pop(), top()

    Another way of categorizing containers

    1. array based containers: vector deque

    2 node base container: list + associative containers + unordered containers

    array based containers invalidates pointers:
        - native pointers, iterators, references


vector<int> vec = {1, 2, 3, 4};
int* p = &vec[2]; // p points at 3
vec.insert(vec.begin(), 0);
cout << *p << endl; // 2 or ? undefined behavior;
*/