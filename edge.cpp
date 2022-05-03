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

std::ostream& operator<< (std::ostream& out, Edge* e)
{
    if (e) return out << "[ (" << e->source << ", " << e->dest << "):" << e->weight << " ]";
    else return out << "[ null edge ]";
}