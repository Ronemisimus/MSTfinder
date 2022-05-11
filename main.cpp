#include "main.h"

int main(int argc, char* argv[])
{
    
    Natural u,v;

    if ( validArgs(argc,argv) && validFile(argv[FILE_ARG], u, v) )
    {
        Natural mst_weight=0, parent_number=0;

        Graph graph = Graph();
        buildGraph(graph,argv[FILE_ARG]);
        std::cout << graph; // temporary
        
        Graph* kruskal_mst = Kruskal(graph,mst_weight, parent_number, true);
        
        std::cout << *kruskal_mst << '\n'; // temporary
        
        if(parent_number == 1)
        {
            std::cout << "Kruskal <" << mst_weight << ">" << "\n";
        }
        else
        {
            std::cout << "Kruskal <" << "No MST" << ">" << "\n";
        }
        delete kruskal_mst;
        
        mst_weight = 0;
        bool connectedGraph = true;
        Graph* prim_mst = Prim(graph,mst_weight,connectedGraph);

        std::cout << *prim_mst << '\n'; // temporary

        if(connectedGraph)
        {
            std::cout << "Prim <" << mst_weight << ">" << "\n";
        }
        else
        {
            std::cout << "Prim <" << "No MST" << ">" << "\n";
        }
        delete prim_mst;
        
        if(IsBridge(graph, u, v))
        {
            std::cout << "Kruskal <" << "No MST" << ">" << "\n";
        }
        else
        {
            mst_weight = 0;
            kruskal_mst = Kruskal(graph,mst_weight, parent_number, false);

            if(parent_number == 1)
            {
                std::cout << "Kruskal <" << mst_weight << ">" << "\n";
            }
            else
            {
                std::cout << "Kruskal <" << "No MST" << ">" << "\n";
            }
            delete kruskal_mst;
        }

    }
    else
    {
        std::cout << "invalid input\n";
    }
}

void buildGraph(Graph& g,char* fileName)
{
    Natural current = 0,n,m, s,d;
    double weight =0;

    std::ifstream input(fileName,std::ios_base::in);

    input >> n >> m;

    g.MakeEmptyGraph(n);
    for(current=0;current<m;current++)
    {
        input >> s >> d >> weight;
        g.AddEdge(s,d,weight);
    }

    input.close();
}

bool validFile(const char* fileName,Natural& u, Natural &v)
{
    bool valid = true;
    Natural n,m;

    std::ifstream input(fileName,std::ios_base::in);
    
    if(valid = valid&&input.is_open())
    {
        Natural s, d, c, current;
        double w;
        valid = valid&&input >> n >> m;

        valid = valid && n > 0 && m <= n*(n-1)/2; 

        for(current =0;current<m && valid;current++)
        {
            valid = valid && input >> s >> d >> w;

            valid = valid && s >=1 && s <= n && 
                            d >=1 && d <= n &&
                            s != d &&
                            w == (int)(w);
        }
        

        valid = valid && current == m;

        valid = valid && input >> u >> v;

        valid = valid && u > 0 && u < n &&
                    v > 0 && v < n;

        input.close();
    }

    return valid;
}


bool validArgs(int argc, char** argv)
{
    if (
        argc == 2 && 
        std::filesystem::exists(argv[1]) && 
        !std::filesystem::is_directory(argv[1])
        )
    {
        return true;
    }
    return false;
}


Graph* Kruskal(Graph &graph,Natural& mst_weight, Natural& parentNumber, bool sortEdges)
{
    Graph* res = new Graph();
    res->MakeEmptyGraph(graph.getVertexCount());
    UnionFind uf = UnionFind(graph.getVertexCount());
    if(sortEdges)
    {
        graph.sortEdgeList();
    }

    fullEdge* lst = graph.getSortedEdgeList();

    Natural i=0;
    for(i =1; i<=graph.getVertexCount();i++)
    {
        uf.MakeSet(i);
    }

    for(i=0;i<graph.getEdgeCount();i++)
    {
        fullEdge& curr = lst[i];
        Natural uParent = uf.Find(curr.getU());
        Natural vParent = uf.Find(curr.getV());
        if(uParent != vParent)
        {
            res->AddEdge(curr.getU(),curr.getV(), curr.getWeight());
            mst_weight += curr.getWeight();
            uf.Union(uParent,vParent);
        }
    }

    parentNumber = uf.getParentCount();
    return res;
}


Natural hash(Natural& vertex, Natural attempt)
{
    return vertex-1;
}

Graph* Prim(Graph &graph,Natural& mst_weight, bool& connectedGraph)
{
    Graph *res = new Graph();
    heap<Natural,int> h = heap<Natural,int>(hash);

    bool* inT = new bool[graph.getVertexCount()];
    int* weights = new int[graph.getVertexCount()];
    Natural* parents = new Natural[graph.getVertexCount()];
    Natural* vertexes = new Natural[graph.getVertexCount()];

    // init MST result
    res->MakeEmptyGraph(graph.getVertexCount());

    // arrays init
    for(Natural i=1;i<graph.getVertexCount();i++)
    {
        vertexes[i] = i+1;
        inT[i]=false;
        weights[i] = INT_MAX;
        parents[i] = 0;
    }
    inT[0] = true;
    vertexes[0] = 1;
    weights[0] = 0;
    parents[0] = 0;

    // heap init
    h.Build(vertexes,weights,graph.getVertexCount());

    while(!h.isEmpty() && connectedGraph)
    {
        Natural u = h.deleteTop();
        Natural v = 0;
        if(weights[u-1]!=INT_MAX)
        {
            inT[u-1] = true;
            for(const Edge& e:*graph.GetAdjList(u))
            {
                v = e.getDest();
                if(!inT[v-1] && e.getWeight() < weights[v-1])
                {
                    weights[v-1] = e.getWeight();
                    parents[v-1] = u;
                    h.DecreaseKey(v,weights[v-1]);
                }
            }
        }
        else
        {
            connectedGraph = false;
        }
    }

    if(connectedGraph)
    {
        for(Natural i=0;i<graph.getVertexCount();i++)
        {
            if(parents[i]!=0)
            {
                res->AddEdge(i+1,parents[i], weights[i]);
                mst_weight += weights[i];
            }
        }
    }

    delete [] vertexes;
    delete [] parents;
    delete [] weights;
    delete [] inT;

    return res;
}


bool IsBridge(const Graph &graph,Natural u, Natural v)
{
    return false;
}
