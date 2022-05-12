#include "graph.h"


/**
 * @brief Construct a new Graph:: Graph object
 * only creates the object - must call make empty after
 */
Graph::Graph():vertexCount(0), edgeCount(0)
{
    this->vertexes=nullptr;
    this->sortedEdgeList = nullptr;
}


/**
 * @brief Destroy the Graph:: Graph object
 * clears any allocations
 */
Graph::~Graph()
{
    if(this->vertexes) delete [] this->vertexes;
    if(this->sortedEdgeList) delete [] this->sortedEdgeList;
}


/**
 * @brief prints the graph using list print operator
 * 
 * @param out - the stream
 * @param g - the graph
 * @return std::ostream& - same steam for chains 
 */
std::ostream& operator<<(std::ostream& out, Graph& g)
{
    std::stringstream ss;
    for (Natural current = 0; current < g.vertexCount; current++)
    {
        ss << (current+1) << " : " << g.vertexes[current] << '\n';
    }

    return out << ss.str();   
}


/**
 * @brief  - checks that a vertex name is in a valid range  
 */
bool Graph::validVertex(Natural u) const
{
    return VALID(u,0,vertexCount);
}


/**
 * @brief initiallize the graph to n vertexes
 * 
 * @param n - amount of vertexes
 */
void Graph::MakeEmptyGraph(Natural n)
{
    // clear any previous allocations
    if(vertexCount!=0)
    {
        if(vertexes!=nullptr) delete [] vertexes;
        if(sortedEdgeList!=nullptr) delete [] sortedEdgeList;
    }

    // create edge lists
    vertexes = new List<Edge>[n];
    this->sortedEdgeList = nullptr;

    // update vertex count
    this->vertexCount = n;
    this->edgeCount = 0;
}


/**
 * @brief returns true if v adjacent to u in the graph
 * 
 * @param u 
 * @param v  
 */
bool Graph::IsAdjacent(Natural u, Natural v) const
{
    bool adj = false;
    bool validInput = validVertex(u) && validVertex(v);
    if(vertexes && validInput)
    {
        List<Edge>* adjlst = this->GetAdjList(u);
        
        // scan neighbors to find v
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


/**
 * @brief returns the node of the edge from u to v
 * 
 * @param u 
 * @param v 
 * @return Node<Edge>* - make sure to not delete neighbors when deleting
 */
Node<Edge>* Graph::getEdge(Natural u, Natural v) const
{
    Node<Edge>* res = nullptr;
    
    // scan neighbors of u to find v
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


/**
 * @brief returns a list of neighbor edges
 * 
 * @param u - the vertex who's neighbors we want
 * @return List<Edge>* 
 */
List<Edge>* Graph::GetAdjList(Natural u) const
{
    if(vertexes!=nullptr && validVertex(u))
    {
        return &vertexes[u-1];
    }  

    return nullptr;
}


/**
 * @brief add edge from u to v and from v to u and link them
 * 
 * @param u - edge parameters
 * @param v 
 * @param weight 
 */
void Graph::AddEdge(Natural u, Natural v, int weight)
{
    if( validVertex(u) && validVertex(v) )
    {
        // update edgeCount
        edgeCount++;
        Edge data(v, weight);
        // insert edge in one direction
        Node<Edge>* res = vertexes[u-1].addData(data,nullptr);
        data = Edge(u,weight);
        // insert in other direction and link them
        res->setBrother(vertexes[v-1].addData(data,res));
    }
}


/**
 * @brief removes an edge between u and v
 * @returns true if edge removed successfully
 * @param u 
 * @param v 
 */
bool Graph::RemoveEdge(Natural u, Natural v)
{
    bool removed = false;
    if( validVertex(u) && validVertex(v) && IsAdjacent(u,v) )
    {
        Node<Edge>* res = nullptr, *temp = nullptr;

        // search neighbors of u for v and save the node
        auto iter = vertexes[u-1].start();
        for(iter;!iter.isEnd();++iter)
        {
            temp = *iter;
            if(temp->getData().getDest()==v) res=temp;
        }

        // get brother node
        Node<Edge>* bro = res->getBrother();
        
        // removes both nodes
        removed = vertexes[u-1].removeNode(res) && vertexes[v-1].removeNode(bro);

        //disconnect the nodes
        res->setNext(nullptr);
        res->setPrev(nullptr);
        bro->setNext(nullptr);
        bro->setPrev(nullptr);

        // delete them
        delete res;
        delete bro; 

        // if edges are sorted we fix them
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
                // when we find the edge we move the items one back to delete the item
                if(found!=edgeCount && i<edgeCount-1)
                {
                    sortedEdgeList[i] = sortedEdgeList[i+1];
                }
            }
        }
        // update edge count
        edgeCount--;       
    }

    return removed;
}


// getters

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


/**
 * @brief compare edge to edge according to weight
 * only for qsort
 * @param a 
 * @param b 
 * @return int 
 */
int compareEdge(const void* a, const void* b)
{
    const fullEdge* e1 = (const fullEdge*) a;
    const fullEdge* e2 = (const fullEdge*) b;

    return *e1 < *e2;
}


/**
 * @brief creates and sorts a list of fulledge items
 * 
 */
void Graph::sortEdgeList()
{
    sortedEdgeList = new fullEdge[edgeCount];

    Natural vertex = 0, edgeIndex=0;
    Node<Edge> *current = nullptr;

    // iterates all edges
    for(vertex=0;vertex<vertexCount;vertex++)
    {
        auto iter = vertexes[vertex].start();
        for(iter;!iter.isEnd();++iter)
        {
            current =  *iter;
            // only insets unmarked edges to avoid duplicates
            if(!current->getData().getMarked())
            {
                // marks edge from both sides
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


/**
 * @brief clears any marked edges
 * 
 */
void Graph::unMarkAllEdges()
{
    Natural vertex = 0, edgeIndex=0;
    Node<Edge> *current = nullptr;

    // iterate all edges
    for(vertex=0;vertex<vertexCount;vertex++)
    {
        auto iter = vertexes[vertex].start();
        for(iter;!iter.isEnd();++iter)
        {
            current =  *iter;

            // unmark
            current->getData().unMarkEdge();
        }
    }
}


/**
 * @brief mark edge pointed by this node
 * this is a static function
 * @param edge - a node of an edge from a graph
 */
void Graph::markEdge(Node<Edge>* edge)
{
    if(edge)
    {
        // mark from both directions
        edge->getData().markEdge();

        if(edge->getBrother())
        {
            edge->getBrother()->getData().markEdge();
        }
    }
}

