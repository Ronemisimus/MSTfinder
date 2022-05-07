#include "graph.h"

Graph::Graph(Natural vertexCount, Natural edgeCount, Edge* edges):vertexCount(vertexCount), edgeCount(edgeCount), edges(edges)
{
    vertexes = new List<Edge&>[vertexCount];
    Natural current = 0;
    for(;current<edgeCount;current++)
    {
        Natural source = edges[current].getSource();
        Natural dest = edges[current].getDest();

        Node<Edge&>* firstDirection = vertexes[source].addData(edges[current],nullptr);
        Node<Edge&>* secondDirection = vertexes[dest].addData(edges[current],firstDirection);
        firstDirection->setBrother(secondDirection);
    }
}

Graph::~Graph()
{
    delete [] this->vertexes;
}

std::ostream& operator<<(std::ostream& out, Graph& g)
{
    std::stringstream ss;
    for (Natural current = 0; current < g.vertexCount; current++)
    {
        ss << (current+1) << " : " << g.vertexes[current] << '\n';
    }

    return out << ss.str();
    
}