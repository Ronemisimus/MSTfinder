#include "unionFind.h"

/**
 * @brief Construct a new Union Find:: Union Find object
 * 
 * @param itemCount - the amount of members in the game
 */
UnionFind::UnionFind(Natural itemCount)
{
    this->parent = new Natural[itemCount];
    this->size = new Natural[itemCount];
    this->active = new bool[itemCount];

    for(Natural i=0;i<itemCount;i++)
        this->active[i]=false;

    this->itemCount = itemCount;
    // there are 0 groups cause all members are inactive
    this->parentCount = 0;
}

/**
 * @brief Destroy the Union Find:: Union Find object
 * delete parent size and activity tracking arrays
 */
UnionFind::~UnionFind()
{
    delete [] parent;
    delete [] size;
    delete [] active;
}


bool UnionFind::validNode(Natural node) const
{
    return VALID(node,0,itemCount);
}

/**
 * @brief find the groups representetive of member "child"
 * 
 * @param child 
 * @return Natural 
 */
Natural UnionFind::Find(Natural child)
{
    // invalid parent at start
    Natural parent = itemCount+1;
    // check if node is valid and active
    if(validNode(child) && this->active[child-1])
    {
        // get parent
        parent = this->parent[child-1];
        // when parent=child we found the groups representetive
        if(parent!=child)
        {
            // recursivly get parent
            parent = Find(parent);
        }

        this->parent[child-1] = parent;
    }
    return parent;
}

/**
 * @brief unites two groups
 * 
 * @param node - parent of group one
 * @param node2  - parent of group 2
 */
void UnionFind::Union(Natural node, Natural node2)
{
    // both node must be in valid range
    if(validNode(node) && validNode(node2) &&
        this->active[node-1] && this->active[node2-1])
        {
            // choose smaller group as child
            Natural parent = this->size[node-1]>this->size[node2-1]? node: node2;
            Natural child = parent==node? node2:node;

            // unite then
            this->parent[child-1] = parent;
            this->size[parent-1] += this->size[child-1];
            // updat parent count
            this->parentCount--;
        }
}

/**
 * @brief initiallizes a new group with one member
 * 
 * @param node - an inactive member from 1-itemCount
 */
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

/**
 * @brief parentCount keeps track of number of groups
 * 
 * @return Natural - the number of groups
 */
Natural UnionFind::getParentCount() const
{
    return this->parentCount;
}

