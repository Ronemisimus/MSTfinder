#include "unionFind.h"

UnionFind::UnionFind(Natural itemCount)
{
    this->parent = new Natural[itemCount];
    this->size = new Natural[itemCount];
    this->active = new bool[itemCount];

    for(Natural i=0;i<itemCount;i++)
        this->active[i]=false;

    this->itemCount = itemCount;
    this->parentCount = 0;
}

UnionFind::~UnionFind()
{
    delete [] parent;
    delete [] size;
    delete [] active;
}


bool UnionFind::validNode(Natural node)
{
    return node>0 && node<=itemCount;
}


Natural UnionFind::Find(Natural child)
{
    Natural parent = itemCount+1;
    if(validNode(child) && this->active[child-1])
    {
        parent = this->parent[child-1];
        if(parent!=child)
        {
            parent = Find(parent);
        }

        this->parent[child-1] = parent;
    }
    return parent;
}


void UnionFind::Union(Natural node, Natural node2)
{
    if(validNode(node) && validNode(node2) &&
        this->active[node-1] && this->active[node2-1])
        {
            Natural parent = this->size[node-1]>this->size[node2-1]? node: node2;
            Natural child = parent==node? node2:node;

            this->parent[child-1] = parent;
            this->size[parent-1] += this->size[child-1];
            this->parentCount--;
        }
}


void UnionFind::MakeSet(Natural node)
{
    if(validNode(node))
    {
        this->active[node-1] = true;
        this->size[node-1]=1;
        this->parent[node-1] = node;
        this->parentCount++;
    }
}


Natural UnionFind::getParentCount() const
{
    return this->parentCount;
}

