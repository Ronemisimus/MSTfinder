#include <iostream>

#define TYPE int

#include "Node.h"

int main()
{
    Node<int> test;

    int data[]= {1,2,3,4,5,6,7};

    test.brotherNode = nullptr;
    test.data = data[0];
    test.next =nullptr;
    test.prev = nullptr;

    std::cout << test << '\n';

    return 0;
}