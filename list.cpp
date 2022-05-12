#include "list.h"

// compiler instractions fro code genration of templates
template class List<Natural>;
template std::ostream& operator<< (std::ostream& out, List<Natural>& list);
template class List<Edge>;
template std::ostream& operator<< (std::ostream& out, List<Edge>& list);


/**
 * @brief adds anode to the start of the list containing data
 * 
 * @tparam E 
 * @param data - the contents of the node
 * @param brotherNode - the node linked to it - can be from another list
 * @return Node<E>* - the node inserted to the list for updating the linked node
 */
template <typename E>
Node<E>* List<E>::addData(const E& data, Node<E>* brotherNode)
{
    // create the node
    Node<E>* res = new Node<E>(data,nullptr,nullptr,brotherNode);
    if(this->head)
    {
        // if the list isn't empty connect it at the start
        res->setNext(this->head);
        this->head->setPrev(res);
    }
    // set it at the head of the list
    this->head = res;
    return res;
} 


/**
 * @brief print the list using node print operator
 * 
 * @tparam E 
 * @param out 
 * @param lst - the list to print
 * @return std::ostream& 
 */
template <typename E> std::ostream& operator << (std::ostream& out, List<E>& lst)
{
    if(lst.head)
    {
        return out<<(*lst.head);
    }
    else
    {
        return out<<"empty list";
    }
}


/**
 * @brief moves the iterator to the next node
 * 
 * @tparam E 
 * @return List<E>::CIterator 
 */
template <typename E> typename List<E>::CIterator List<E>::CIterator::operator++ ()
{
    this->curr = ((Node<E>*)(this->curr))->getNext();
    return *this;
}

// same as previous function for second iterator type
template < typename E> typename List<E>::Iterator List<E>::Iterator::operator++ ()
{
    this->curr = this->curr->getNext();
    return *this;
}



/**
 * @brief returns the current iterator pointed data
 * 
 * @tparam E 
 * @return E 
 */
template <typename E> E List<E>::CIterator::operator*() const
{
    return this->curr->getData();
}

// same as previous function for second iterator type
template < typename E> Node<E>* List<E>::Iterator::operator*()
{
    return curr;
}


/**
 * @brief returns an iterator pointing to the end of the list (nullptr)
 * 
 * @tparam E 
 * @return List<E>::CIterator 
 */
template < typename E> typename List<E>::CIterator List<E>::end()
{
    return List<E>::CIterator();
}


/**
 * @brief checks if the iterator is at the end
 * 
 * @tparam E 
 * @return true 
 * @return false 
 */
template <typename E> bool List<E>::CIterator::isEnd() const
{
    return this->curr==nullptr;
}

// same as previous function for second iterator type
template < typename E> bool List<E>::Iterator::isEnd() const
{
    return curr == nullptr;
}


/**
 * @brief returns true if this iterator and the other iterator dont point to the same position
 * 
 */
template <typename E> bool List<E>::CIterator::operator!=(CIterator other) const
{
    return this->curr != other.curr;
}

// same as previous function for second iterator type
template < typename E> bool List<E>::Iterator::operator!=(Iterator other) const
{
    return this->curr != other.curr;
}


/**
 * @brief Destroy the List< E>:: List object
 * uses node destructor
 * @tparam E 
 */
template < typename E> List<E>::~List()
{
    delete this->head;
}


/**
 * @brief returns a const iterator for this list
 * 
 * @tparam E 
 * @return List<E>::CIterator 
 */
template < typename E> typename List<E>::CIterator  List<E>::begin()
{
    return this;
}

// same as previous function for second iterator type
template <typename E> typename List<E>::Iterator List<E>::start()
{
    return Iterator(this);
}


/**
 * @brief removes a node from the list by disconnecting it
 * returns true when successfully returned
 * @tparam E 
 * @param remove - the node to remove
 */
template <typename E> bool List<E>::removeNode(Node<E>* remove)
{
    bool removed = true;
    // head of list case
    if(remove  == this->head)
    {
        this->head=this->head->getNext();
    }
    else if(remove)
    {
        // middle of list case
        remove->getPrev()->setNext(remove->getNext());
        // end of list case
        if(remove->getNext()) remove->getNext()->setPrev(remove->getPrev());
    }
    else{
        // null node
        removed = false;
    }
    return removed;
}
