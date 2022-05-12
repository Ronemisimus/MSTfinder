#ifndef GRAPH
#define GRAPH

#include "general.h"
#include "edge.h"
#include "list.h"

#include <sstream>
#include <string>
#include <stdlib.h>

class Graph
{
private:
    Natural vertexCount;
    Natural edgeCount;
    List<Edge>* vertexes;
    fullEdge* sortedEdgeList;

public:
    Graph();
    ~Graph();
    void MakeEmptyGraph(Natural n);
    bool IsAdjacent(Natural u, Natural v) const;
    List<Edge>* GetAdjList(Natural u) const;
    void AddEdge(Natural u, Natural v, int weight);
    bool RemoveEdge(Natural u, Natural v);
    bool validVertex(Natural u) const;

    static void markEdge(Node<Edge>* edge);

    void sortEdgeList();

    Natural getVertexCount() const;
    Natural getEdgeCount() const;
    fullEdge* getSortedEdgeList();
    Node<Edge>* getEdge(Natural u, Natural v) const;

    void unMarkAllEdges();

    friend std::ostream& operator<<(std::ostream& out, Graph& g);
};

#endif
