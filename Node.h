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

#ifdef TYPE

template class Node<TYPE>;
template std::ostream& operator<< (std::ostream& out, Node<TYPE>& node);

template <typename E>
std::ostream& operator<< (std::ostream& out, Node<E>& node)
{
    if(node.next)
    {
        return out << node.data << "<->" << node.next;
    }
    else
    {
        return out << node.data << "<->|";
    }
}
#endif