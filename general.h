#ifndef GENERAL
#define GENERAL

#include <iostream>

typedef unsigned int Natural;

#define VALID(data,x,y) data>x && data<=y

#define FILE_ARG 1

#define KRUSKAL_ERROR "Kruskal <" << "No MST" << ">" << "\n"
#define PRIM_ERROR "Prim <" << "No MST" << ">" << "\n";
#define INPUT_ERROR "invalid input\n"

enum class Color
{
    WHITE,
    GRAY,
    BLACK
};

#endif
