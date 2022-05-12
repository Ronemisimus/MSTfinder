#include "hashMap.h"

template class HashMap<int,Natural>;

template class HashMap<Natural,Natural>;


/**
 * @brief initiallizes the hashmap
 * @param itemCount - the amount of values in the mapping at max
 */
template <class K, class V> void HashMap<K,V>::MakeEmpty(Natural itemCount) {
    if(value_arr) delete [] value_arr;

    this->maxCapacity = itemCount;
    this->itemCount = 0;
    value_arr = new V[maxCapacity];
}


/**
 * @brief Construct a new Hash Map< K, V>:: Hash Map object
 * this only creates the object, must call make empty after
 * @param hash - the hashing function
 */
template <class K, class V> HashMap<K,V>::HashMap(Natural (*hash)(K& key,Natural attempt))
{
    this->hash = hash;
    this->value_arr = nullptr;
    this->itemCount = 0;
    this->maxCapacity = 0;
}


/**
 * @brief Destroy the Hash Map< K, V>:: Hash Map object
 * 
 * @tparam K 
 * @tparam V 
 */
template <class K, class V> HashMap<K,V>::~HashMap()
{
    // clears the allocated memmory
    if(value_arr) delete [] value_arr;
}


/**
 * @brief returns true if amount of items currently mapped is 0
 *   
 */
template <class K, class V> bool HashMap<K,V>::isEmpty()
{
    return this->itemCount == 0;
}


/**
 * @brief allows access to the mapping with keys
 * 
 * @param key - the key to use for access
 * @return V& - the value mapped for the key - using refrence for access in both directions
 */
template <class K, class V> V& HashMap<K,V>::operator[](K& key)
{
    Natural attempt = 0;
    Natural index = hash(key, attempt);
    if(index>=maxCapacity)
    {
        throw "invalid hash function";
    }
    if(itemCount>=maxCapacity)
    {
        throw "no space left in hash map";
    }
    // assumes perfect hash function cause there is one for my usecase
    return value_arr[index];
}

