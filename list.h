#include <iostream>

#include "Node.h"

template <class E> class List;
//template <class E> std::ostream& operator << (std::ostream& out, List<E>& lst);

template <typename E>
class List
{
private:
    Node<E> *head;
public:
    List(/* args */);
    ~List();
    //Node<E>* addData(E& data, Node<E>* brotherNode);
    //friend std::ostream& operator << (std::ostream& out, List<E>& lst);
};
