#include <iostream>
#include <string>
#include <sstream>
#include <limits.h>

#include "general.h"
#include "edge.h"
#include "hashMap.h"


template<class V,class K> class heap;
template<class V, class K> std::ostream& operator<<(std::ostream& cout, heap<V,K>& h);

template<class V,class K> class heap
{
private:
    HashMap<V,Natural> currentPlace; // current place of a value
    V* value_arr;// the item array of the heap
    K* key_arr; // the key array of the heap
    Natural itemCount;

    Natural fixHeap(Natural node);// fixes down while assuming the rest is correct except this value
    Natural heapifyUp(Natural node);// fixes up while assuming the rest is correct except this heap
    void swap(Natural& place, Natural& newplace);

public:
    heap(Natural (*hash)(V& key,Natural attempt));
    ~heap();

    void Build(V* values, K* keys, Natural itemCount);
    const V& Top() const;
    const V deleteTop();
    bool isEmpty();
    Natural DecreaseKey(V value, K newKew);

    friend std::ostream& operator<< <V,K> (std::ostream& cout, heap<V,K>& h);
    
    
};