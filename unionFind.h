#include <iostream>
#include "general.h"

class UnionFind
{

private:
    Natural *parent;
    Natural *size;
    bool *active;
    Natural itemCount;
    Natural parentCount;

    bool validNode(Natural node);

public:
    UnionFind(Natural size);
    ~UnionFind();
    Natural Find(Natural child);
    void Union(Natural node, Natural node2);
    void MakeSet(Natural node);
    Natural getParentCount() const;
};