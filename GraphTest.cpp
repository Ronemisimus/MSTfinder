#include "graph.h"

#include <iostream>

int main()
{
    Natural n = 3, m = 3;

    Graph g = Graph();

    g.MakeEmptyGraph(n);
    g.AddEdge(1,2,-2);
    g.AddEdge(2,3,3);
    g.AddEdge(3,1,5);

    std::cout << g;

    List<Natural>* res = g.GetAdjList(1);
    std::cout << *res << "\n";
    delete res;

    std::cout << "1 and 2 adjacent status: " << g.IsAdjacent(1,2) << '\n';

    std::cout << (g.RemoveEdge(1,2)?"Removed edge":"failed to remove") << "\n";

    std::cout << "1 and 2 adjacent status: " << g.IsAdjacent(1,2) << "\n";

    g.MakeEmptyGraph(0);

}