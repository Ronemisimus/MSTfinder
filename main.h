#ifndef MAIN
#define MAIN

#include "general.h"
#include "edge.h"
#include "graph.h"
#include "unionFind.h"
#include "heap.h"

#include <filesystem>
#include <fstream>
#include <limits.h>

#define FILE_ARG 1

enum class Color
{
    WHITE,
    GRAY,
    BLACK
};

void runKruskal(Graph& g, bool sort);
void runPrim(Graph& g);
bool validArgs(int argc, char** argv);
bool validFile(const char* fileName,Natural& u, Natural &v);
Graph* Kruskal(Graph &graph,Natural& mst_weight, Natural& parentNumber, bool sortEdges);
Graph* Prim(Graph &graph,Natural& mst_weight, bool& connectedGraph);
bool IsBridge(const Graph &graph,Natural u, Natural v);
void buildGraph(Graph& g,char* fileName);
bool dfsConnected(const Graph& g, Natural u, Natural v);
void visit(const Graph& g, Natural u, Color* color);

#endif
