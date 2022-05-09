#include "heap.h"

template class heap<int,int>;
template std::ostream& operator<< (std::ostream& cout, heap<int,int>& h);

template <class V, class K> heap<V,K>::heap()
{
    itemCount = 0;
    value_arr = nullptr;
    key_arr = nullptr;
}


template <class V, class K> heap<V,K>::~heap()
{
    
}


template <class V, class K> void heap<V,K>::swap(Natural& place, Natural& newplace)
{
    K temp = key_arr[place];
    V v_temp = value_arr[place];
    key_arr[place] = key_arr[newplace];
    value_arr[place] = value_arr[newplace];
    key_arr[newplace] = temp;
    value_arr[newplace] = v_temp;
}

template <class V, class K> Natural heap<V,K>::fixHeap(Natural node)
{
    Natural final_loc = node;
    if(node<itemCount/2)
    {
        Natural son = 2*node+1, son2 = 2*node+2;
        K min = key_arr[son] < key_arr[son2]? key_arr[son]: key_arr[son2];
        Natural minIndex = min==key_arr[son2]? son2:son;
        
        if(min<key_arr[node])
        {
            swap(node,minIndex);
            final_loc = minIndex;
        }
        if(final_loc!=node)final_loc = fixHeap(final_loc);
    }
    return final_loc;
}


template <class V, class K> Natural heap<V,K>::heapifyUp(Natural node)
{
    Natural final_loc = node;
    if(node>0)
    {
        Natural parent = (node-1)/2;
        if(key_arr[node]<key_arr[parent])
        {
            swap(node,parent);
            final_loc = parent;
        }

        if(final_loc!=node)final_loc = heapifyUp(final_loc);
    }
    return final_loc;
}


template <class V, class K> void heap<V,K>::Build(V* values, K* keys, Natural itemCount)
{
    this->itemCount = itemCount;
    value_arr = values;
    key_arr = keys;

    for(Natural i=itemCount/2-1;i>0;i--)
    {
        fixHeap(i);
    }
    fixHeap(0);
}


template <class V, class K> const V& heap<V,K>::Top() const
{
    return value_arr[0];
}


template <class V, class K> const V heap<V,K>::deleteTop()
{
    const V ans  = value_arr[0];

    value_arr[0] = value_arr[itemCount-1];
    key_arr[0] = key_arr[itemCount-1];

    fixHeap(0);
    itemCount--;
    return ans;
}


template <class V, class K> bool heap<V,K>::isEmpty()
{
    return itemCount==0;
}


template <class V, class K> bool heap<V,K>::DecreaseKey(Natural place, K newKew)
{
    this->key_arr[place] = newKew;

    Natural newPlace = fixHeap(place);

    if(newPlace == place)
    {
        newPlace = heapifyUp(place);
    }

    return newPlace;
}

template<class V, class K> std::ostream& operator<<(std::ostream& cout, heap<V,K>& h)
{
    std::stringstream ss;
    if(h.itemCount>0)
    {
        ss << "[" << h.value_arr[0] << "," << h.key_arr[0] << "]";

        for(Natural i=1;i<h.itemCount;i++)
        {
            ss << " - [" << h.value_arr[i] << "," << h.key_arr[i] << "]";
        }
    }

    return cout << ss.str();
}
