#include <edge.h>


template <typename E>

struct Node
{
    E data;
    Node* next;
};

template <typename E>
class List
{
private:
    Node<E> *head;
public:
    List(/* args */);
    ~List();

    void addData(E data);
};