#include "Node.h"

#define TYPE int

template class Node<TYPE>;
template std::ostream& operator<< (std::ostream& out, Node<TYPE>& node);

template <typename E>
std::ostream& operator<< (std::ostream& out, Node<E>& node)
{
    if(node.next)
    {
        return out << node.data << "<->" << *(node.next);
    }
    else
    {
        return out << node.data << "<->|";
    }
}