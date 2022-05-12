#include "edge.h"


// constructors

Edge::Edge(Natural dest, int weight):dest(dest), weight(weight)
{
    marked = false;
}

Edge::~Edge()
{
    
}

fullEdge::fullEdge()
{

}


/**
 * @brief mark an edge for any reason
 * 
 */
void Edge::markEdge()
{
    this->marked = true;
}


/**
 * @brief clear a marked edge
 * 
 */
void Edge::unMarkEdge()
{
    this->marked = false;
}


// comperators

int Edge::operator<(Edge& other)
{
    return this->weight-other.weight;
}

int fullEdge::operator<(const fullEdge& other) const
{
    return this->getWeight() - other.getWeight();
}


/**
 * @brief print operator for edge
 * 
 * @param out - the stream
 * @param e - the edge
 * @return std::ostream& 
 */
std::ostream& operator<< (std::ostream& out, Edge const& e)
{
    return out << "[ " << e.dest << ": " << e.weight << "]";
}


// setters
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


// getters

Natural Edge::getDest() const
{
    return this->dest;
}

int Edge::getWeight() const
{
    return this->weight;
}

bool Edge::getMarked() const
{
    return this->marked;
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

