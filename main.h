#ifndef MAIN
#define MAIN

#include "general.h"
#include "edge.h"
#include "graph.h"

#include <filesystem>
#include <fstream>

#define FILE_ARG 1

bool validArgs(int argc, char** argv);
bool validFile(const char* fileName,Natural& n,Natural& m,Edge*& edges,Natural& u, Natural &v);
Graph* Kruskal(Graph &graph,Natural& mst_weight,bool sortEdges);
Graph* Prim(Graph &graph,Natural& mst_weight);
bool IsBridge(const Graph &graph,Natural u, Natural v);

#endif
