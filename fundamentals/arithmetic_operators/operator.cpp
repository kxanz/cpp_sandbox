#include <iostream>
#include <iterator>

void operation(int x, int y) 
{
    return x&y;
}

int main() 
{

    std::cout << operation(3, 5) "\n";
    return 0;
}