#include <iostream>

#include "Node.h"

int main()
{
    Natural data[]= {1,2,3,4,5,6,7};
    Node<Natural> test(data[0],nullptr,nullptr,nullptr);

    std::cout << test << '\n';

    return 0;
}