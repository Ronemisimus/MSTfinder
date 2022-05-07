#ifndef LIST
#define LIST

#include <iostream>

#include "Node.h"

template <class E> class List;
template <class E> std::ostream& operator << (std::ostream& out, List<E>& lst);

template <typename E>
class List
{
private:
    Node<E> *head;
public:
    List():head(nullptr){}
    ~List();
    Node<E>* addData(const E& data, Node<E>* brotherNode);
    friend std::ostream& operator << <E>(std::ostream& out, List<E>& lst);
};

#endif