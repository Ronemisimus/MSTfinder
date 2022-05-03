#ifndef NODE
#define NODE

#include <iostream>
template <typename E> class Node;
template <typename E> std::ostream& operator<< (std::ostream& out, Node<E>& node);

template <typename E> class Node
{
    public:
    E data;
    Node<E>* prev;
    Node<E>* next;
    Node<E>* brotherNode;

    friend std::ostream& operator << <E>(std::ostream& out, Node<E>& node);
};


#endif