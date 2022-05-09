#include <iostream>

#include "general.h"

using std::ostream;

/* template<class T> class heap;
template<class T> ostream& operator<<(ostream& cout, heap<T>* h);
 */
template<class V,class K> class heap
{
private:
    V* value_arr;// the item array of the heap
    K* key_arr; // the key array of the heap
    Natural itemCount;

    int heapifyDown(int node);// fixes down while assuming the rest is correct except this value
    int heapifyUp(int node);// fixes up while assuming the rest is correct except this heap
    bool compare(const T* t1, const T* t2);// returns true if t1>t2
    void remove(int remove);// removes from middle of the heap while fixing it

public:
    heap();
    ~heap();

    void Build(V* values, K* keays, Natural itemCount);
    const V& Top() const;
    const V deleteTop();
    bool isEmpty();
    bool DecreaseKey(Natural place, K newKew);
    
    
};