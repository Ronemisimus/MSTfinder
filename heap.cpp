#include "heap.h"

// compiler declerations for code genretion for these types of data
template class heap<int,int>;
template std::ostream& operator<< (std::ostream& cout, heap<int,int>& h);
template class heap<Natural,int>;
template std::ostream& operator<< (std::ostream& cout, heap<Natural,int>& h);


/**
 * @brief Construct a new heap<V,K>::heap object
 * @tparam V - the value of the heap
 * @tparam K - the keys of the heap
 * @param hash is a function recieving a value object refrence and an 
 * atempt number and returns an index for the mapping,
 * basiclly a hashmap hashing function
 */
template <class V, class K> heap<V,K>::heap(Natural (*hash)(V& key,Natural attempt)):currentPlace(HashMap<V,Natural>(hash))
{
    // at first we just create the object
    itemCount = 0;
    value_arr = nullptr;
    key_arr = nullptr;
}


/**
 * @brief Destroy the heap<V,K>::heap object
 * delete any memmory allocated
 * @tparam V 
 * @tparam K 
 */
template <class V, class K> heap<V,K>::~heap()
{
    if(value_arr) delete [] value_arr;
    if(key_arr) delete [] key_arr;
}


/**
 * @brief the this function swaps two values in the heap in all data tracking parts of the heap
 * (ex. the key_arr, the hashmap)
 * @tparam V
 * @tparam K 
 * @param place - the place to switch 
 * @param newplace - the place to switch with
 */
template <class V, class K> void heap<V,K>::swap(Natural& place, Natural& newplace)
{
    // switch keys
    K temp = key_arr[place];
    key_arr[place] = key_arr[newplace];
    key_arr[newplace] = temp;
    
    // switch values
    V v_temp = value_arr[place];
    value_arr[place] = value_arr[newplace];
    value_arr[newplace] = v_temp;
    
    // update map
    currentPlace[value_arr[place]] = place;
    currentPlace[value_arr[newplace]] = newplace;
}


/**
 * @brief fix the heap down while assuming both child nodes are valid heaps
 * 
 * @tparam V 
 * @tparam K 
 * @param node - the node in the wrong place
 * @return Natural - the new location of the node
 */
template <class V, class K> Natural heap<V,K>::fixHeap(Natural node)
{
    Natural final_loc = node;
    // leaf nodes are already a valid heap
    if(node<itemCount/2)
    {
        // get child nodes indexes
        Natural son = 2*node+1, son2 = 2*node+2;
        K min;
        // save the smaller key - make sure not to access outside of array
        if(son2<itemCount) min = key_arr[son] < key_arr[son2]? key_arr[son]: key_arr[son2];
        else min = key_arr[son];
        // save that keys index
        Natural minIndex = min==key_arr[son]? son:son2;
        
        // if a key is smaller we need to swap them
        if(min<key_arr[node])
        {
            swap(node,minIndex);
            final_loc = minIndex;
        }
        // if we swaped that means we still need to fix the heap in lower levels
        if(final_loc!=node)final_loc = fixHeap(final_loc);
    }
    return final_loc;
}


/**
 * @brief find the location of an item that is in the wrong place 
 * but bellow it and above it the heap is valid
 * @tparam V 
 * @tparam K 
 * @param node - the node in the wrong place
 * @return Natural - the new location of the node
 */
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


/**
 * @brief build a heap according to floyds algorithm
 * 
 * @tparam V 
 * @tparam K 
 * @param values - the values to include
 * @param keys - the keys for each value
 * @param itemCount - the amount of values stored
 */
template <class V, class K> void heap<V,K>::Build(V* values, K* keys, Natural itemCount)
{
    //  initiallize the hashmap to the given amount of values
    this->currentPlace.MakeEmpty(itemCount);
    //  initiallize the heap to the given amount of values
    this->itemCount = itemCount;
    value_arr = new V[itemCount];
    key_arr = new K[itemCount];

    // copy the values and keys to new value and key arrays
    for(Natural i=0;i<itemCount;i++)
    {
        value_arr[i] = values[i];
        key_arr[i] = keys[i];
        // initiallize the hashmap
        currentPlace[values[i]] = i;
    }

    // fix the heaps from leafs to root
    for(Natural i=itemCount/2-1;i>0;i--)
    {
        fixHeap(i);
    }
    fixHeap(0);
}


/**
 * @brief reads the top value without removing it
 * 
 * @tparam V 
 * @tparam K 
 * @return const V& - refrence to the value
 */
template <class V, class K> const V& heap<V,K>::Top() const
{
    return value_arr[0];
}


/**
 * @brief returns the top value and removes it from the heap
 * 
 * @tparam V 
 * @tparam K 
 * @return const V - the value itself
 */
template <class V, class K> const V heap<V,K>::deleteTop()
{
    // save the value
    const V ans  = value_arr[0];
    
    // swap it with the last one
    Natural place = 0;
    Natural place2 = itemCount-1;
    swap(place, place2);

    // update itemCount
    itemCount--;

    // fix the heap - so the new root finds it's place
    fixHeap(0);

    return ans;
}


/**
 * @brief returns true if the heap is empty
 */
template <class V, class K> bool heap<V,K>::isEmpty()
{
    return itemCount==0;
}


/**
 * @brief updates value's key to the new key and fixes the heap
 * according to new key
 * @param value - the value to update
 * @param newKew - the new key
 * @return Natural - the new position of the value
 */
template <class V, class K> Natural heap<V,K>::DecreaseKey(V value, K newKew)
{
    // take the current place of the value
    Natural place = currentPlace[value];
    
    // update the key
    this->key_arr[place] = newKew;

    // fix the heap down from the value
    Natural newPlace = fixHeap(place);

    // if the value moved down then the heap is correct
    if(newPlace == place)
    {
        // fix the heap up from the value
        newPlace = heapifyUp(place);
    }

    return newPlace;
}


/**
 * @brief prints the heap to "cout" stream
 * @param cout - the output stream
 * @param h - the heap
 * @return std::ostream& - the same stream for output chains 
 */
template<class V, class K> std::ostream& operator<<(std::ostream& cout, heap<V,K>& h)
{
    //  create a string stream
    std::stringstream ss;
    if(h.itemCount>0)
    {
        // print every item to string
        ss << "[" << h.value_arr[0] << "," << h.key_arr[0] << "]";
        for(Natural i=1;i<h.itemCount;i++)
        {
            ss << " - [" << h.value_arr[i] << "," << h.key_arr[i] << "]";
        }
    }

    // print the result string to cout
    return cout << ss.str();
}

