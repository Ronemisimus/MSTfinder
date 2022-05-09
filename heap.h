#include <iostream>
#include <string>
#include <sstream>

#include "general.h"

template<class V,class K> class heap;
template<class V, class K> std::ostream& operator<<(std::ostream& cout, heap<V,K>& h);

template<class V,class K> class heap
{
private:
    V* value_arr;// the item array of the heap
    K* key_arr; // the key array of the heap
    Natural itemCount;

    Natural fixHeap(Natural node);// fixes down while assuming the rest is correct except this value
    Natural heapifyUp(Natural node);// fixes up while assuming the rest is correct except this heap
    void swap(Natural& place, Natural& newplace);

public:
    heap();
    ~heap();

    void Build(V* values, K* keys, Natural itemCount);
    const V& Top() const;
    const V deleteTop();
    bool isEmpty();
    bool DecreaseKey(Natural place, K newKew);

    friend std::ostream& operator<< <V,K> (std::ostream& cout, heap<V,K>& h);
    
    
};