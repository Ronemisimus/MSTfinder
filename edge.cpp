#include "edge.h"

int Edge::operator<(Edge& other)
{
    return this->weight-other.weight;
}

Edge::Edge(Natural source, Natural dest, int weight):source(source),dest(dest), weight(weight)
{

}

Edge::~Edge()
{
    
}