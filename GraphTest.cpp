#include "graph.h"

#include <iostream>

int main()
{
    Natural n = 3, m = 3;

    Edge edges[3] = { Edge(1,2,-2), Edge(2,3,3), Edge(3,1,5) };

    Graph g = Graph(n,m,edges);

    std::cout << g;

}