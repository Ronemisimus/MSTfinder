#ifndef NODE
#define NODE

#include <iostream>

#include "edge.h"

template <typename E> class Node;
template <typename E> std::ostream& operator<< (std::ostream& out, Node<E> const& node);

template <typename E> class Node
{
    private:
        E data;
        Node<E>* prev;
        Node<E>* next;
        Node<E>* brotherNode;
    
    public:
        void setBrother(Node<E>* brother);
        void setNext(Node<E>* next);
        void setPrev(Node<E>* prev);
        Node(E data, Node<E>* prev, Node<E>* next, Node<E>* brotherNode):data(data), prev(prev), next(next), brotherNode(brotherNode){}
        ~Node();
        friend std::ostream& operator << <E>(std::ostream& out, Node<E> const& node);
};


#endif
