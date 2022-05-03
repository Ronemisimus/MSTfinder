#include "list.h"


#define TYPE int

template class List<TYPE>;
template std::ostream& operator<< (std::ostream& out, List<TYPE>& list);

template <typename E>
Node<E>* List<E>::addData(E& data, Node<E>* brotherNode)
{
    Node<E>* res = new Node<E>;
    res->data=data;
    res->brotherNode = brotherNode;
    res->next = nullptr;
    res->prev = nullptr;
    if(this->head)
    {
        res->next = this->head;
        this->head->prev = res;
    }
    this->head = res;
    return res;
} 

template <typename E>
std::ostream& operator << (std::ostream& out, List<E>& lst)
{
    return out<<(*lst.head);
}

template < typename E> List<E>::~List()
{
    
}
