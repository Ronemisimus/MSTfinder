#include "main.h"

int main(int argc, char* argv[])
{
    
    Natural n,m,u,v;
    
    Natural *source = nullptr;
    Natural *dest = nullptr;
    int *weight = nullptr;
    
    bool file_validation, args_validation;

    if ( validArgs(argc,argv) && validFile(argv[FILE_ARG], n, m, u, v, source, dest, weight) )
    {
        Natural mst_weight=0;

        Graph graph = Graph();
        buildGraph(graph,n,m,source,dest,weight);
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
        delete [] source;
        delete [] dest;
        delete [] weight;
    }
}

void buildGraph(Graph& g,Natural n,Natural m,Natural*& source,Natural*& dest,int*& weight)
{
    Natural current = 0;
    g.MakeEmptyGraph(n);
    for(current=0;current<m;current++)
    {
        g.AddEdge(source[current],dest[current],weight[current]);
    }
    delete [] source;
    delete [] dest;
    delete [] weight;
}

bool validFile(const char* fileName,Natural& n,Natural& m,Natural& u, Natural &v,Natural*& source,Natural*& dest,int*& weight)
{
    std::ifstream input(fileName,std::ios_base::in);
    bool valid = true;
    if(valid = valid&&input.is_open())
    {
        Natural s, d, c, current;
        double w;
        valid = valid&&input >> n >> m;

        valid = valid && n > 0 && m <= n*(n-1)/2; 

        if(valid)
        { 
            source = new Natural[m];
            dest = new Natural[m];
            weight = new int[m];
        }
        for(current =0;current<m && valid;current++)
        {
            valid = valid && input >> s >> d >> w;

            valid = valid && s >=1 && s <= n && 
                            d >=1 && d <= n &&
                            s != d &&
                            w == (int)(w);
            if (valid)
            {
                source[current] = s;
                dest[current] = d;
                weight[current] = (int)w;
            }
        }

        valid = valid && current == m;

        valid = valid && input >> u >> v;

        valid = valid && u > 0 && u < n &&
                    v > 0 && v < n;

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
