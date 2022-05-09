#ifndef GRAPH
#define GRAPH

#include "general.h"
#include "edge.h"
#include "list.h"

#include <sstream>
#include <string>

class Graph
{
private:
    Natural vertexCount;
    Natural edgeCount;
    List<Edge>* vertexes;
public:
    Graph();
    ~Graph();
    void MakeEmptyGraph(Natural n);
    bool IsAdjacent(Natural u, Natural v);
    List<Natural>* GetAdjList(Natural u);
    void AddEdge(Natural u, Natural v, int weight);
    bool RemoveEdge(Natural u, Natural v);
    bool validVertex(Natural u);

    friend std::ostream& operator<<(std::ostream& out, Graph& g);
};

#endif
