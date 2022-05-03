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
};
