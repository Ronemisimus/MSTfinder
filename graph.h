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
    List<fullEdge> sortedEdgeList;

public:
    Graph();
    ~Graph();
    void MakeEmptyGraph(Natural n);
    bool IsAdjacent(Natural u, Natural v);
    List<Edge>* GetAdjList(Natural u);
    void AddEdge(Natural u, Natural v, int weight);
    bool RemoveEdge(Natural u, Natural v);
    bool validVertex(Natural u);

    void sortEdgeList();

    Natural getVertexCount();
    Natural getEdgeCount();
    List<fullEdge>& getSortedEdgeList();

    friend std::ostream& operator<<(std::ostream& out, Graph& g);
};

#endif
