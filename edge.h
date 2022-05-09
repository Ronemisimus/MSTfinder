#ifndef EDGE
#define EDGE

#include "general.h"

class Edge
{
private:
    Natural dest;
    int weight;
public:
    Edge():dest(0),weight(0){}
    Edge(Natural dest,int weight);
    ~Edge();
    
    Natural getDest() const;
    int getWeight() const;

    int operator<(Edge& other);
    friend std::ostream& operator<< (std::ostream& out, Edge const& e);
};

#endif
