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
    Edge* edges;
    List<Edge&>* vertexes;
public:
    Graph(Natural vertexCount, Natural edgeCount, Edge* edges);
    ~Graph();
    friend std::ostream& operator<<(std::ostream& out, Graph& g);
};

#endif
