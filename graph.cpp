#include "graph.h"

Graph::Graph():vertexCount(0), edgeCount(0)
{
    this->vertexes=nullptr;
    this->sortedEdgeList = nullptr;
}

Graph::~Graph()
{
    delete [] this->vertexes;
    if(this->sortedEdgeList) delete [] this->sortedEdgeList;
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


bool Graph::validVertex(Natural u) const
{
    return u>0 && u<=vertexCount;
}


void Graph::MakeEmptyGraph(Natural n)
{
    if(vertexCount!=0)
    {
        if(vertexes!=nullptr) delete [] vertexes;
        if(sortedEdgeList!=nullptr) delete [] sortedEdgeList;
    }

    vertexes = new List<Edge>[n];
    this->sortedEdgeList = nullptr;

    this->vertexCount = n;
    this->edgeCount = 0;
}


bool Graph::IsAdjacent(Natural u, Natural v) const
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


Node<Edge>* Graph::getEdge(Natural u, Natural v) const
{
    Node<Edge>* res = nullptr;
    auto iter = vertexes[u-1].start();
    for(iter;!iter.isEnd();++iter)
    {
        Node<Edge>* curr = *iter;
        if(curr->getData().getDest()==v)
        {
            res = curr;
        }
    }

    return res;
}


List<Edge>* Graph::GetAdjList(Natural u) const
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

        res->setNext(nullptr);
        res->setPrev(nullptr);

        bro->setNext(nullptr);
        bro->setPrev(nullptr);

        if(sortedEdgeList)
        {
            Natural found = edgeCount;
            for (Natural i = 0; i < edgeCount; i++)
            {
                if(found==edgeCount)
                {
                    fullEdge* current = &sortedEdgeList[i];
                    if(current->getU()==u && current->getV() == v)
                    {
                        found = i;
                    }   
                }
                if(found!=edgeCount && i<edgeCount-1)
                {
                    sortedEdgeList[i] = sortedEdgeList[i+1];
                }
            }
        }

        edgeCount--;

        delete res;
        delete bro;        
    }

    return removed;
}


Natural Graph::getVertexCount() const
{
    return this->vertexCount;
}


Natural Graph::getEdgeCount() const
{
    return this->edgeCount;
}


fullEdge* Graph::getSortedEdgeList()
{
    return this->sortedEdgeList;
}


int compareEdge(const void* a, const void* b)
{
    const fullEdge* e1 = (const fullEdge*) a;
    const fullEdge* e2 = (const fullEdge*) b;

    return *e1 < *e2;

}

void Graph::sortEdgeList()
{
    sortedEdgeList = new fullEdge[edgeCount];

    Natural vertex = 0, edgeIndex=0;
    Node<Edge> *current = nullptr;

    for(vertex=0;vertex<vertexCount;vertex++)
    {
        auto iter = vertexes[vertex].start();
        for(iter;!iter.isEnd();++iter)
        {
            current =  *iter;

            if(!current->getData().getMarked())
            {
                markEdge(current);
                Edge& e = current->getData();
                sortedEdgeList[edgeIndex] = fullEdge(vertex+1,e.getDest(),e.getWeight());
                edgeIndex ++;
            }
        }
    }

    unMarkAllEdges();

    qsort(sortedEdgeList,edgeCount, sizeof(fullEdge),compareEdge);

}


void Graph::unMarkAllEdges()
{
    Natural vertex = 0, edgeIndex=0;
    Node<Edge> *current = nullptr;

    for(vertex=0;vertex<vertexCount;vertex++)
    {
        auto iter = vertexes[vertex].start();
        for(iter;!iter.isEnd();++iter)
        {
            current =  *iter;

            current->getData().unMarkEdge();
        }
    }
}


void Graph::markEdge(Node<Edge>* edge)
{
    if(edge)
    {
        edge->getData().markEdge();

        if(edge->getBrother())
        {
            edge->getBrother()->getData().markEdge();
        }
    }
}


