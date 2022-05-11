#include "edge.h"

int Edge::operator<(Edge& other)
{
    return this->weight-other.weight;
}

Edge::Edge(Natural dest, int weight):dest(dest), weight(weight)
{
    marked = false;
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


void Edge::markEdge()
{
    this->marked = true;
}


bool Edge::getMarked() const
{
    return this->marked;
}


void Edge::unMarkEdge()
{
    this->marked = false;
}

int fullEdge::operator<(const fullEdge& other) const
{
    return this->getWeight() - other.getWeight();
}

fullEdge::fullEdge()
{

}


void fullEdge::setU(Natural u)
{
    this->u = u;
}


void fullEdge::setV(Natural v)
{
    this->v = v;
}


void fullEdge::setWeight(int weight)
{
    this->weight = weight;
}


Natural fullEdge::getU() const
{
    return u;
}


Natural fullEdge::getV() const
{
    return v;
}


int fullEdge::getWeight() const
{
    return weight;
}

