#include "main.h"

/**
 * this program finds weights of MST in undirected graphs
 * the graph should be in a file
 * 
 * Usage: ./main graph.txt
 *  
 * the file should contain:
 * 1. 2 numbers: n - number of vertexes, m - number of edges
 * 2. a list of valid edges, each in the form u v w:
 *      * u - a vertex between 1-n
 *      * v - a vertex between 1-n
 *      * w - weight of edge (whole numbers)
 * 3. 2 numbers u v:
 *  this is an edge to remove from the graph - does not have to be an edge in the previous list
 * 
 * the program runs kruskal once
 * then prim
 * then removes the edge and runs kruskal
 * 
 * @author Ronen Margolin
 */
int main(int argc, char* argv[])
{
    
    Natural u,v; // edge to remove

    if ( validArgs(argc,argv) && validFile(argv[FILE_ARG], u, v) ) // check in put and read file - also gets u,v
    {

        Graph graph = Graph();
        buildGraph(graph,argv[FILE_ARG]);
        
        runKruskal(graph,true);
        
        runPrim(graph);
        

        if(IsBridge(graph, u, v))
        {
            std::cout << KRUSKAL_ERROR;
        }
        else
        {
            graph.RemoveEdge(u,v);
            runKruskal(graph,false);
        }

    }
    else
    {
        std::cout << INPUT_ERROR;
    }
}


/**
 * @brief runs prim on given graph and outputs the result
 * 
 * @param g - the graph to run prim on
 * @param sort - if tre a list of edges will be created and sorted
 */
void runKruskal(Graph& g, bool sort)
{
    // this is the resulting weight of found mst
    Natural mst_weight = 0;
    // this is the number of parents left in the unionfind. if its 1 then the graph was connected
    Natural parentNumber=0;

    // run the algorithm
    Graph* kruskal_mst = Kruskal(g,mst_weight, parentNumber, sort);

    // output the correct message
    if(parentNumber == 1)
    {
        std::cout << "Kruskal <" << mst_weight << ">" << "\n";
    }
    else
    {
        std::cout << KRUSKAL_ERROR;
    }
    // clear the MST
    delete kruskal_mst;
}


/**
 * @brief runs prim on given graph and outputs the result
 * 
 * @param g - the graph to run on
 */
void runPrim(Graph& g)
{
    // the weight of the resulting MST
    Natural mst_weight = 0;
    // will stay true if the graph is connected
    bool connectedGraph = true;

    // run prim
    Graph* prim_mst = Prim(g,mst_weight,connectedGraph);
    
    // output result
    if(connectedGraph)
    {
        std::cout << "Prim <" << mst_weight << ">" << "\n";
    }
    else
    {
        std::cout << PRIM_ERROR;
    }
    // clear the MST
    delete prim_mst;
}


/**
 * @brief builds the graph in a valid file
 * 
 * @param g - the result graph - an output parameter
 * @param fileName - the name of the file
 */
void buildGraph(Graph& g,char* fileName)
{
    /**
     * current - the number of edge being added
     * n - number of vertexes
     * m - the total number of edges
     * s - the source vertex of an edge
     * d - the destenation vertex of an edge
     * weight - the weight of an edge
     */
    Natural current = 0, n, m, s, d;
    double weight =0;

    std::ifstream input(fileName,std::ios_base::in);

    // read the amount of edges and vertexes
    input >> n >> m;

    // initiallize the graph
    g.MakeEmptyGraph(n);
    for(current=0;current<m;current++)
    {
        // read an edge and add it
        input >> s >> d >> weight;
        g.AddEdge(s,d,weight);
    }

    input.close();
}


/**
 * @brief fully checks an exisiting file for a valid graph and an edge to remove from it
 * 
 * @param fileName 
 * @param u - this outputs the edge to remove in stage 3
 * @param v 
 * @return true  - if the file contains a valid graph
 */
bool validFile(const char* fileName,Natural& u, Natural &v)
{
    // will stay true if the file is valid
    bool valid = true;
    // the graph size
    Natural n,m;

    std::ifstream input(fileName,std::ios_base::in);
    
    if(valid = valid&&input.is_open())
    {
        /**
         * s - source vertex
         * d - destenation vertex
         * w - the weight of an edge
         * current - the edge index
         */
        Natural s, d, current;
        double w;
        
        valid = valid&&input >> n >> m;

        valid = valid && m <= n*(n-1)/2; // number of edges should not be bigger then the number of vertex pairs 

        for(current =0;current<m && valid;current++)
        {
            valid = valid && input >> s >> d >> w;

            valid = valid && VALID(s,0,n) && 
                            VALID(d,0,n) &&
                            s != d &&
                            w == (int)(w);
            // checks every vertex is in a valid range and no edge is from edge to itself
            // also checks weight is a natural number or 0
        }
        

        // amount of edges should match the reported one
        valid = valid && current == m;

        // read the edge to remove in step 3
        valid = valid && input >> u >> v;
        
        // make sure its valid
        valid = valid && VALID(u,0,n) &&
                        VALID(v,0,n) &&
                        u!=v;

        input.close();
    }

    return valid;
}


/**
 * @brief 
 * 
 * @param argc - arguments from main
 * @param argv - arguments from main
 * @return true - if the arguments passed contain a valid file path
 */
bool validArgs(int argc, char** argv)
{
    if (
        argc == 2 && 
        std::filesystem::exists(argv[FILE_ARG]) && 
        !std::filesystem::is_directory(argv[FILE_ARG]) // should not be a directory
        )
    {
        return true;
    }
    return false;
}


/**
 * @brief 
 * 
 * @param graph - the graph to run on - input
 * @param mst_weight - the mst weight of the result graph - output
 * @param parentNumber - the number of connected elements in the graph - output
 * @param sortEdges - if true, an edge array will be created and sorted
 * @return Graph* - the result MST - must be deleted by caller
 */
Graph* Kruskal(Graph &graph,Natural& mst_weight, Natural& parentNumber, bool sortEdges)
{
    // initiallize the MST
    Graph* res = new Graph();
    res->MakeEmptyGraph(graph.getVertexCount());

    // initiallize the union find
    UnionFind uf = UnionFind(graph.getVertexCount());
    
    // get the sorted edge list from input graph
    if(sortEdges)
    {
        graph.sortEdgeList();
    }
    fullEdge* lst = graph.getSortedEdgeList();

    // initiallize every group in the union
    Natural i=0;
    for(i =1; i<=graph.getVertexCount();i++)
    {
        uf.MakeSet(i);
    }

    // scan edge list
    for(i=0;i<graph.getEdgeCount();i++)
    {
        // for every edge check if it closes a circle
        fullEdge& curr = lst[i];
        Natural uParent = uf.Find(curr.getU());
        Natural vParent = uf.Find(curr.getV());

        // if not then added it to the MST
        if(uParent != vParent)
        {
            // add it to MST
            res->AddEdge(curr.getU(),curr.getV(), curr.getWeight());
            // update the weight
            mst_weight += curr.getWeight();
            // update connected groups of vertexes
            uf.Union(uParent,vParent);
        }
    }

    // save number of connected elements and return the MST
    parentNumber = uf.getParentCount();
    return res;
}


/**
 * @brief perfect hash function for the heap's hashmap
 * because all vertexes are from 1 to n and we have exacly n spaces in map
 * (we check that all vertexes are valid at the start)
 * @param vertex - the vertex to get index for
 * @param attempt - the attempt number - not relevant
 * @return Natural - the index in the hashmap
 */
Natural hash(Natural& vertex, Natural attempt)
{
    return vertex-1;
}


/**
 * @brief runs prim's MST algorithm
 * 
 * @param graph - the input graph
 * @param mst_weight - the resulting MST weight - output
 * @param connectedGraph - true if the input graph is connected
 * @return Graph* - the result MST - must be deleted by caller
 */
Graph* Prim(Graph &graph,Natural& mst_weight, bool& connectedGraph)
{
    // initiallize the result MST
    Graph *res = new Graph();
    res->MakeEmptyGraph(graph.getVertexCount());

    // create nessecery arrays:
    // true if (i+1)'th vertex is in the MST
    bool* inT = new bool[graph.getVertexCount()];
    // the weight of the edge conecting (i+1)'th vertex to MST
    int* weights = new int[graph.getVertexCount()];
    // the parent vertex of (i+1)'th vertex
    Natural* parents = new Natural[graph.getVertexCount()];
    // an array of vertexes as values for the heap i'th vertex is in (i-1)'th cell
    Natural* vertexes = new Natural[graph.getVertexCount()];

    // arrays init
    for(Natural i=1;i<graph.getVertexCount();i++)
    {
        // all vertexes except one should have:
        // 1. null parents (0 is invalid)
        parents[i] = 0;
        // 2. their vertex name
        vertexes[i] = i+1;
        // 3. they are not in the MST yet
        inT[i]=false;
        // 4. they have no connecting edge yet so weight is infinity
        weights[i] = INT_MAX;
    }
    // this vertex starts the MST so it's in the tree from the start
    inT[0] = true;
    // it's name is 1
    vertexes[0] = 1;
    // it needs no edge to connect so its weight is zero
    weights[0] = 0;
    // it has no parent so its parent is 0 (invalid)
    parents[0] = 0;

    // heap init
    heap<Natural,int> h = heap<Natural,int>(hash);
    h.Build(vertexes,weights,graph.getVertexCount());

    while(!h.isEmpty() && connectedGraph)
    {
        Natural u = h.deleteTop(); // get the vertex with smallest edge conecting it to MST
        Natural v = 0;
        if(weights[u-1]!=INT_MAX)
        {
            inT[u-1] = true; // insert it to the tree - its parent and weight was set before
            for(const Edge& e:*graph.GetAdjList(u))
            {
                v = e.getDest(); // check every neighbor
                // if its not in the tree and it's weight is the smallest from all neighbors we will save it
                if(!inT[v-1] && e.getWeight() < weights[v-1])
                {
                    // save weight and parent of best neighbor
                    weights[v-1] = e.getWeight();
                    parents[v-1] = u;
                    // update the heap
                    h.DecreaseKey(v,weights[v-1]);
                }
            }
        }
        else // if no connecting edge was found for u it means the graph isn't connected
        {
            connectedGraph = false;
        }
    }

    if(connectedGraph)
    {
        // if the graph is connected an mst was found and we build it
        // it's not necessary for mst weight but its nice for testing
        for(Natural i=0;i<graph.getVertexCount();i++)
        {
            if(parents[i]!=0)
            {
                // add edge to MST
                res->AddEdge(i+1,parents[i], weights[i]);

                // sum up the MST weight
                mst_weight += weights[i];
            }
        }
    }

    // clean up
    delete [] vertexes;
    delete [] parents;
    delete [] weights;
    delete [] inT;

    return res;
}


/**
 * @brief returns true if (u,v) is a bridge in the graph
 * 
 * @param graph - the input graph
 * @param u - the edge vertexes
 * @param v - the edge vertexes
 */
bool IsBridge(const Graph &graph,Natural u, Natural v)
{
    // will be true if (u,v) is bridge
    bool bridge = false;
    // no point to check if it isn't in the graph
    if(graph.IsAdjacent(u,v))
    {
        // we mark the edge to make DFS's visit no use it
        Node<Edge>* res = graph.getEdge(u,v);
        Graph::markEdge(res);

        // we run DFS from u and try to reach v without using (u,v)
        bridge = dfsConnected(graph, u, v);
    }
    return bridge;
}


/**
 * @brief runs partial DFS - to see if (u,v) - a marked edge is a bridge 
 * 
 * @param g - the input graph
 * @param u - the edge vertexes
 * @param v 
 * @return true - if (u,v) is a bridge
 */
bool dfsConnected(const Graph& g, Natural u, Natural v)
{
    bool res = false;
    // initiallize color array
    Color* color = new Color[g.getVertexCount()];
    for(Natural i=0;i<g.getVertexCount();i++)
    {
        color[i]= Color::WHITE;
    }

    // run visit from u
    visit(g,u,color);

    if(color[v-1]==Color::WHITE) 
    {
        // v is unreachable from u without (u,v)
        res = true;
    }

    // clean up
    delete [] color;

    return res;
}


/**
 * @brief DFS's visit with a slight change of skiping marked edges
 * 
 * @param g - the input graph
 * @param u - the vertex to start from
 * @param color - the color array
 */
void visit(const Graph& g, Natural u, Color* color)
{
    color[u-1] = Color::GRAY; // mark as visited
    for(const Edge& e:*g.GetAdjList(u))
    {   // for each neighbor check if we should visit it and the edge to it isn;t marked
        Natural v = e.getDest();
        if(color[v-1]==Color::WHITE && !e.getMarked())
        {
            // visit the neighbor
            visit(g,v,color);
        }
    }
    // we visited all neighbors
    color[u-1] = Color::BLACK;
}

