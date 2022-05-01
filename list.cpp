#include "list.h"

template class List<Edge>;

template <typename E> void List<E>::addData(E data)
{
    Node<E> *first = new Node<E>;
    first->data = data;
    if(head)
    {    
        first->next = head;
    }
    else
    {
        first->next = nullptr;
    }
    this->head = first;
}