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
        Graph* prim_mst = Prim(graph,mst_weight);
        
        std::cout << "Prim <" << mst_weight << ">" << "\n";
        
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


Graph* Prim(Graph &graph,Natural& mst_weight)
{
    return nullptr;
}


bool IsBridge(const Graph &graph,Natural u, Natural v)
{
    return false;
}
