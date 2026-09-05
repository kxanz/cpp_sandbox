// Topic: std: priotity_queue in C++ (priority queue)

// What is it??

// Notes:
// 0 std::priority_queue is a container adapter that provides constant time lookup of
//   the largest or smallest elemnt
// 1 By default std::vector is the container used inside
// 2 Cost of insertion and extraction is logarithmic
// 3 std priority_queue is implemented using std::make_heap(coverts a vector into a heap),
//   std::push_heap std::pop_heap funcitons

// Program 
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

template<typename T> void print_queue(T& q) 
{
    while (!q.empty()) 
    {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

int main() 
{
    {
        //first example max to min
        std::priority_queue<int> q;
        for (int elm : {1, 8, 5, 6,3,4,0,9,7,2})
        { q.push(elm); }
        print_queue(q);
    }
    {
        //second example min to max
        std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
        for (int elm : {1, 8, 5, 6,3,4,0,9,7,2})
        { q2.push(elm); }
        print_queue(q2);
    }
    //using lambda to compare elements
    {
        //third example max to min
        auto cmp = [](int left, int right) {return (left) < (right);};
        std::priority_queue<int, std::vector<int>, decltype(cmp) > q3(cmp);
        
        for (int elm : {1, 8, 5, 6,3,4,0,9,7,2})
        { q3.push(elm); }
        print_queue(q3);
    }

    return 0;
}

