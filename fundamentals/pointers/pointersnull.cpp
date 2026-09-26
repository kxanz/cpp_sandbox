#include <iostream>
#include <vector>


int main() 
{
    std::vector<int> nums {1, 2, 3, 4};

    [[maybe_unused]]int*& ptr { nums[0] };

    std::cout << ptr << '\n';
    return 0;
}
