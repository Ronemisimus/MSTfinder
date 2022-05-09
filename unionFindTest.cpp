#include "unionFind.h"

#include <iostream>

int main()
{
    UnionFind uf = UnionFind(10);

    uf.MakeSet(1);
    uf.MakeSet(2);
    uf.MakeSet(4);
    uf.MakeSet(5);
    uf.MakeSet(6);
    uf.MakeSet(8);
    uf.MakeSet(9);
    uf.MakeSet(10);

    std::cout << uf.Find(5) << '\n';

    uf.Union(4,8);
    uf.Union(2,8);
    uf.Union(5,1);
    uf.Union(9,1);

    uf.Union(1,8);

    std::cout << uf.Find(5) << '\n';


}