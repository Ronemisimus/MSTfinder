#include "edge.h"
#include <iostream>

int main()
{
    Edge e = Edge(1,2,3);
    Edge e2 = Edge(1,2,3);

    std::cout << e << " compare to " << e2 << " is: " << (e<e2) <<"\n";

    e = Edge(1,2,3);
    e2 = Edge(1,2,-1);

    std::cout << e << " compare to " << e2 << " is: " << (e<e2) <<"\n";

    e = Edge(1,2,-10);
    e2 = Edge(1,2,3);

    std::cout << e << " compare to " << e2 << " is: " << (e<e2) <<"\n";

}