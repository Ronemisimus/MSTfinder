#include <iostream>

#include "general.h"
#include "edge.h"
#include "graph.h"

using std::cout;

#define FILE_ARG 1

bool validArgs(int argc, char** argv);
bool validFile(char* fileName,Natural& n,Natural& m,Edge*& edges,Natural& u, Natural &v);
Graph* Kruskal(Graph &graph,Natural& mst_weight,bool sortEdges);
Graph* Prim(Graph &graph,Natural& mst_weight);
bool IsBridge(const Graph &graph,Natural u, Natural v);

