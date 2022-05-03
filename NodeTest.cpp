#include <iostream>

#include "Node.h"

int main()
{
    int data[]= {1,2,3,4,5,6,7};
    Node<int> test(data[0],nullptr,nullptr,nullptr);

    std::cout << test << '\n';

    return 0;
}