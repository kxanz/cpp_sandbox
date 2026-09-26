#include <iostream>
#include <ostream>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    A set is a collection of unique elements (no duplications).
    Oder -> by insertion, or by sorted
    In C++
        a set is in sorted order, whereas in other languages, set may not be sorted.
        An unoredered set is not or ordered by insertion, not sorted.
    A vector is ordered by insertion (not sorted)

*/
template <typename T>
void print(const T& container) {
    for (auto it = container.begin(); it != container.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    //multiset can have duplicates sorted ordered

    unordered_set<string> emailtList {"banana@gmail.com", "orange@gmail.com"}; // a container with unique elements
    emailtList.insert("orange@gmail.com");
    emailtList.insert("apple@gmail.com");
    emailtList.erase("banana@gmail.com");

    cout << emailtList.size() << endl;
    cout << emailtList.count("orange@gmail.com") << endl;
    cout << emailtList.count("melon@gmail.com") << endl;

    /*
    vector<char> charVec {'C', 'A', 'B'};
    set<char> charSet {'C', 'A', 'B'}; //tree data structure
    unordered_set<char> charSet2 {'C', 'A', 'B'}; //implemented with a hashtable
    
    print(charVec);
    print(charSet);
    print(charSet2);

    for (auto it = charSet.begin(); it != charSet.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    */
}