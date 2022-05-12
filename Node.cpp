#include "Node.h"

// these statements tell the compiler to generate code for these types (one for testing and one for main program)
template class Node<Natural>;
template std::ostream& operator<< (std::ostream& out, Node<Natural> const& node);
template class Node<Edge>;
template std::ostream& operator<< (std::ostream& out, Node<Edge> const& node);


/**
 * @brief print oporator overload - type of node must have aprint oporator too
 * 
 * @tparam E - the Node type
 * @param out - the stream to output to
 * @param node - the node to print
 * @return std::ostream& - same stream for chained output
 */
template <typename E>
std::ostream& operator<< (std::ostream& out, Node<E> const& node)
{
    if(node.next)
    {
        // recursivly print list
        return out << node.data << "<->" << *(node.next);
    }
    else
    {
        // print the final node
        return out << node.data << "<->|";
    }
}


/**
 * @brief Destroy the Node< E>:: Node object
 * also destroys the next nodes
 * @tparam E 
 */
template <typename E> Node<E>::~Node()
{
    delete this->next;
}


// setters:

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


//getters:

template <typename E> Node<E>* Node<E>::getNext()
{
    return this->next;
}


template <typename E> Node<E>* Node<E>::getPrev()
{
    return this->prev;
}


template <typename E> Node<E>* Node<E>::getBrother()
{
    return this->brotherNode;
}

template <typename E> E& Node<E>::getData()
{
    return this->data;
}
        

