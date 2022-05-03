#ifndef EDGE
#define EDGE

#include "general.h"

class Edge
{
private:
    Natural source;
    Natural dest;
    int weight;
public:
    Edge(Natural source,Natural dest,int weight);
    ~Edge();
    int operator<(Edge& other);
    friend std::ostream& operator<< (std::ostream& out, Edge* e);
};

#endif
