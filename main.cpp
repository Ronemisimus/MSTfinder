#include "main.h"

int main(int argc, char* argv[])
{
    
    Natural n,m,u,v;
    Edge *edges=nullptr;
    
    bool file_validation, args_validation;

    if ( validArgs(argc,argv) && validFile(argv[FILE_ARG], n, m, edges, u, v) )
    {
        Natural mst_weight=0;

        Graph graph(n,m,edges);
        std::cout << graph;
        Graph* kruskal_mst = Kruskal(graph,mst_weight,true);
        std::cout << "Kruskal <" << mst_weight << ">" << "\n";
        Graph* prim_mst = Prim(graph,mst_weight);
        std::cout << "Prim <" << mst_weight << ">" << "\n";
        if(IsBridge(graph, u, v))
        {
            std::cout << "Kruskal <" << "No MST" << ">" << "\n";
        }
        else
        {
            delete kruskal_mst;
            kruskal_mst = Kruskal(graph,mst_weight,false);
            std::cout << "Kruskal <" << mst_weight << ">" << "\n";
        }

    }
    else
    {
        std::cout << "invalid input\n";
    }
}


bool validFile(const char* fileName,Natural& n,Natural& m,Edge*& edges,Natural& u, Natural &v)
{
    std::ifstream input(fileName,std::ios_base::in);
    bool valid = true;
    if(valid = valid&&input.is_open())
    {
        Natural source, dest, current;
        double weight;
        valid = valid&&input >> n >> m;

        valid = valid && n > 0 && m <= n*(n-1)/2; 

        bool* used = new bool[n*m];

        edges = new Edge[m];

        for(current =0;current<m && valid;current++)
        {
            valid = valid && input >> source >> dest >> weight;

            valid = valid && !used[source*m+dest];

            used[source*m+dest] = used[dest*m+source] = true;

            valid = valid && source >=1 && source <= n && 
                            dest >=1 && dest <= n &&
                            source != dest &&
                            weight == (int)(weight);
            if (valid) edges[current] = Edge(source,dest,weight);
        }

        valid = valid && current == m;

        valid = valid && input >> u >> v;

        valid = valid && u > 1 && u < n &&
                    v > 1 && v < n;

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


Graph* Kruskal(Graph &graph,Natural& mst_weight,bool sortEdges)
{
    return nullptr;
}


Graph* Prim(Graph &graph,Natural& mst_weight)
{
    return nullptr;
}


bool IsBridge(const Graph &graph,Natural u, Natural v)
{
    return false;
}
