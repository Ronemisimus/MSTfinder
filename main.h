#ifndef MAIN
#define MAIN

#include "general.h"
#include "edge.h"
#include "graph.h"

#include <filesystem>
#include <fstream>

#define FILE_ARG 1

bool validArgs(int argc, char** argv);
bool validFile(const char* fileName,Natural& n,Natural& m,Natural& u, Natural &v,Natural*& source,Natural*& dest,int*& weight);
Graph* Kruskal(Graph &graph,Natural& mst_weight,bool sortEdges);
Graph* Prim(Graph &graph,Natural& mst_weight);
bool IsBridge(const Graph &graph,Natural u, Natural v);
void buildGraph(Graph& g,Natural n,Natural m,Natural*& source,Natural*& dest,int*& weight);

#endif
