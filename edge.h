#ifndef EDGE
#define EDGE

#include "general.h"

class fullEdge
{
    Natural u;
    Natural v;
    int weight;

    public:
    fullEdge();
    fullEdge(Natural u,Natural v,int weight):u(u),v(v),weight(weight){}
    void setU(Natural u);
    void setV(Natural v);
    void setWeight(int weight);
    Natural getU() const;
    Natural getV() const;
    int getWeight() const;
};

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
