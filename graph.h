#include "edge.h"
#include "list.h"

class Graph
{
private:
    unsigned int vertexCount;
    unsigned int edgeCount;
    Edge* edges;
    List* vertexes;
public:
    Graph(unsigned int vertexCount, unsigned int edgeCount, Edge* edges):vertexCount(vertexCount), edgeCount(edgeCount){}
    ~Graph();
};