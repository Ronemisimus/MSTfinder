#include "graph.h"

Graph::Graph():vertexCount(0), edgeCount(0)
{
    this->vertexes=nullptr;
    this->sortedEdgeList = List<fullEdge>();
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


bool Graph::validVertex(Natural u)
{
    return u>0 && u<=vertexCount;
}


void Graph::MakeEmptyGraph(Natural n)
{
    if(vertexCount!=0)
    {
        if(vertexes!=nullptr) delete [] vertexes;
    }

    vertexes = new List<Edge>[n];

    this->vertexCount = n;
    this->edgeCount = 0;
}


bool Graph::IsAdjacent(Natural u, Natural v)
{
    bool adj = false;
    bool validInput = validVertex(u) && validVertex(v);
    if(vertexes && validInput)
    {
        List<Edge>* adjlst = this->GetAdjList(u);
        
        for(const Edge& adjacent:*adjlst)
        {
            if(adjacent.getDest()==v)
            {
                adj = true;
            }
        }

    }

    return adj;
}


List<Edge>* Graph::GetAdjList(Natural u)
{
    if(vertexes!=nullptr && validVertex(u))
    {
        return &vertexes[u-1];
    }  

    return nullptr;
}


void Graph::AddEdge(Natural u, Natural v, int weight)
{
    if( validVertex(u) && validVertex(v) )
    {
        edgeCount++;
        Edge data(v, weight);
        Node<Edge>* res = vertexes[u-1].addData(data,nullptr);
        data = Edge(u,weight);
        res->setBrother(vertexes[v-1].addData(data,res));
    }
}


bool Graph::RemoveEdge(Natural u, Natural v)
{
    bool removed = false;
    if( validVertex(u) && validVertex(v) && IsAdjacent(u,v) )
    {
        auto iter = vertexes[u-1].start();

        Node<Edge>* res = nullptr, *temp = nullptr;

        for(iter;!iter.isEnd();++iter)
        {
            temp = *iter;
            if(temp->getData().getDest()==v) res=temp;
        }

        Node<Edge>* bro = res->getBrother();

        removed = vertexes[u-1].removeNode(res) && vertexes[v-1].removeNode(bro);

        delete res;
        delete bro;        
    }

    return removed;
}


Natural Graph::getVertexCount()
{
    return this->vertexCount;
}


Natural Graph::getEdgeCount()
{
    return this->edgeCount;
}


List<fullEdge>& Graph::getSortedEdgeList()
{
    return this->sortedEdgeList;
}


void Graph::sortEdgeList()
{
    
}


