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

Natural Edge::getSource()
{
    return this->source-1;
}

Natural Edge::getDest()
{
    return this->dest-1;
}

int Edge::getWeight()
{
    return this->weight;
}

std::ostream& operator<< (std::ostream& out, Edge const& e)
{
    return out << "[ (" << e.source << ", " << e.dest << "):" << e.weight << " ]";
}