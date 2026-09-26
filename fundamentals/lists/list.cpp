// TOPIC: list in STL

/*
1. This is double linked list what we know from C programming language 
2. List is a sequene container that allows non-contigous memory allocation.
3. List is faster compared to other sequences containers (vector, foward_list deque)
    in terms of insertion, remocal and moving elements in any position provided we have the 
    iterator of the position.
4. We use this class instead of traditional double linked list because 
    a. Well Tested 
    b. Bunch of available function
5. Few available operations
    operator = assign, front, back, empty, size, max_size, clear. insert, emplace, push_back, pop_back, push_front
    , reverse, sort, merge, splice, unique, remove, remove if, resize.
*/

#include <iterator>
#include <list>
#include <iostream>

int main() {

    std::list<int> list1 = {5, 2, 4, 6, 2};
    std::list<int> list2 = {7, 6, 1, 9 };
    list1.sort();
    list2.sort();
    list1.merge(list2);

    for (auto& elm: list1)
        std::cout << elm << ' ';
    std::cout << std::endl;

    for (auto& elm: list2)
        std::cout << elm << ' ';
    std::cout << std::endl;
    
    return 0;
}