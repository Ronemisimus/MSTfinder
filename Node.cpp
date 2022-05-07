#include "Node.h"

template class Node<int>;
template std::ostream& operator<< (std::ostream& out, Node<int> const& node);
template class Node<Edge&>;
template std::ostream& operator<< (std::ostream& out, Node<Edge&> const& node);

template <typename E>
std::ostream& operator<< (std::ostream& out, Node<E> const& node)
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

template <typename E> Node<E>::~Node()
{
    delete this->next;
}

template <typename E> void Node<E>::setBrother(Node<E>* bro)
{
    this->brotherNode = bro;
}

template <typename E> void Node<E>::setNext(Node<E>* next)
{
    this->next = next;
}


template <typename E> void Node<E>::setPrev(Node<E>* prev)
{
    this->prev = prev;
}

