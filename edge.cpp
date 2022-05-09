#include "edge.h"

int Edge::operator<(Edge& other)
{
    return this->weight-other.weight;
}

Edge::Edge(Natural dest, int weight):dest(dest), weight(weight)
{

}

Edge::~Edge()
{
    
}

Natural Edge::getDest() const
{
    return this->dest;
}

int Edge::getWeight() const
{
    return this->weight;
}

std::ostream& operator<< (std::ostream& out, Edge const& e)
{
    return out << "[ " << e.dest << ": " << e.weight << "]";
}