#include "list.h"


template class List<int>;
template std::ostream& operator<< (std::ostream& out, List<int>& list);
//template class List<Edge>;
//template std::ostream& operator<< (std::ostream& out, List<Edge>& list);

template <typename E>
Node<E>* List<E>::addData(E& data, Node<E>* brotherNode)
{
    Node<E>* res = new Node<E>(data,nullptr,nullptr,brotherNode);
    if(this->head)
    {
        res->setNext(this->head);
        this->head->setPrev(res);
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
    delete this->head;
}
