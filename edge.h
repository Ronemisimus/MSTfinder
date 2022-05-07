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
    Edge():source(0),dest(0),weight(0){}
    Edge(Natural source,Natural dest,int weight);
    ~Edge();

    Natural getSource();
    Natural getDest();
    int getWeight();

    int operator<(Edge& other);
    friend std::ostream& operator<< (std::ostream& out, Edge const& e);
};

#endif
