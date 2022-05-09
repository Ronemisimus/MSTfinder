#include <iostream>

#include "list.h"

int main()
{
    List<Natural> lst1;
    List<Natural> lst2;

    Natural data[]= {1,2,3,4,5,6,7};

    Node<Natural> *res = lst1.addData(data[0],nullptr);
    Node<Natural> *res2 = lst2.addData(data[0],res);
    res->setBrother(res2);

    res = lst1.addData(data[1],nullptr);
    res2 = lst2.addData(data[1],res);
    res->setBrother(res2);

    res = lst1.addData(data[2],nullptr);
    res2 = lst2.addData(data[2],res);
    res->setBrother(res2);

    std::cout << lst1 << '\n';
    std::cout << lst2 << '\n';

    return 0;
}