#ifndef LIST
#define LIST

#include <iostream>
#include <iterator>

#include "Node.h"

template <class E> class List;
template <class E> std::ostream& operator << (std::ostream& out, List<E>& lst);

template <typename E>
class List
{
private:
    Node<E> *head;

    class CIterator
    {
        private:
            Node<E>* curr;
        public:
            CIterator(): curr(nullptr){}
            CIterator(const List<E>* lst): curr(lst->head){}
            CIterator operator++ ();
            E operator*() const;
            bool isEnd() const;
            bool operator!=(CIterator other) const;
    };

    class Iterator
    {
        private:
            Node<E>* curr;
        public:
            Iterator(): curr(nullptr){}
            Iterator(const List<E>* lst): curr(lst->head){}
            Iterator operator++ ();
            Node<E>* operator*();
            bool isEnd() const;
            bool operator!=(Iterator other) const;
    };

public:
    List():head(nullptr){}
    ~List();
    Node<E>* addData(const E& data, Node<E>* brotherNode);
    bool removeNode(Node<E>* remove);
    CIterator begin();
    CIterator end();

    Iterator start();

    friend std::ostream& operator << <E>(std::ostream& out, List<E>& lst);
};

#endif