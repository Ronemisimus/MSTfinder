#include "main.h"

int main(int argc, char* argv[])
{
    Natural n,m,u,v;
    Edge *edges=nullptr;
    
    if( validArgs(argc,argv)  &&  validFile(argv[FILE_ARG], n, m, edges, u, v) )
    {
        Natural mst_weight=0;

        Graph graph(n,m,edges);
        Graph* kruskal_mst = Kruskal(graph,mst_weight,true);
        cout << "Kruskal <" << mst_weight << ">" << "\n";
        Graph* prim_mst = Prim(graph,mst_weight);
        cout << "Prim <" << mst_weight << ">" << "\n";
        if(IsBridge(graph, u, v))
        {
            cout << "No MST" << "\n";
        }
        else
        {
            delete kruskal_mst;
            kruskal_mst = Kruskal(graph,mst_weight,false);
            cout << "Kruskal <" << mst_weight << ">" << "\n";
        }

    }
}