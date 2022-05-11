#include "hashMap.h"

template class HashMap<int,Natural>;

template class HashMap<Natural,Natural>;

template <class K, class V> void HashMap<K,V>::MakeEmpty(Natural itemCount) {
    if(value_arr) delete [] value_arr;

    this->maxCapacity = itemCount;
    this->itemCount = 0;
    value_arr = new V[maxCapacity];
}

template <class K, class V> HashMap<K,V>::HashMap(Natural (*hash)(K& key,Natural attempt))
{
    this->hash = hash;
    this->value_arr = nullptr;
    this->itemCount = 0;
    this->maxCapacity = 0;
}


template <class K, class V> HashMap<K,V>::~HashMap()
{
    if(value_arr) delete [] value_arr;
}


template <class K, class V> bool HashMap<K,V>::isEmpty()
{
    return this->itemCount == 0;
}


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