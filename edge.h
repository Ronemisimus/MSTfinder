#include "general.h"
#include <iostream>

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
