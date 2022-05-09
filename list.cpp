#include "list.h"


template class List<Natural>;
template std::ostream& operator<< (std::ostream& out, List<Natural>& list);
template class List<Edge>;
template std::ostream& operator<< (std::ostream& out, List<Edge>& list);


template <typename E>
Node<E>* List<E>::addData(const E& data, Node<E>* brotherNode)
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


template <typename E> std::ostream& operator << (std::ostream& out, List<E>& lst)
{
    return out<<(*lst.head);
}


template <typename E> typename List<E>::CIterator List<E>::CIterator::operator++ ()
{
    this->curr = ((Node<E>*)(this->curr))->getNext();
    return *this;
}


template <typename E> E List<E>::CIterator::operator*() const
{
    return this->curr->getData();
}


template <typename E> bool List<E>::CIterator::isEnd() const
{
    return this->curr==nullptr;
}


template <typename E> bool List<E>::CIterator::operator!=(CIterator other) const
{
    return this->curr != other.curr;
}


template < typename E> List<E>::~List()
{
    delete this->head;
}


template < typename E> typename List<E>::CIterator  List<E>::begin()
{
    return this;
}


template < typename E> typename List<E>::CIterator List<E>::end()
{
    return List<E>::CIterator();
}

template < typename E> typename List<E>::Iterator List<E>::Iterator::operator++ ()
{
    this->curr = this->curr->getNext();
    return *this;
}


template < typename E> Node<E>* List<E>::Iterator::operator*()
{
    return curr;
}


template < typename E> bool List<E>::Iterator::isEnd() const
{
    return curr == nullptr;
}


template < typename E> bool List<E>::Iterator::operator!=(Iterator other) const
{
    return this->curr != other.curr;
}

template <typename E> typename List<E>::Iterator List<E>::start()
{
    return Iterator(this);
}


template <typename E> bool List<E>::removeNode(Node<E>* remove)
{
    bool removed = true;
    if(remove  == this->head)
    {
        this->head=this->head->getNext();
    }
    else if(remove)
    {
        remove->getPrev()->setNext(remove->getNext());
        if(remove->getNext()) remove->getNext()->setPrev(remove->getPrev());
    }
    else{
        removed = false;
    }

    return removed;
}
