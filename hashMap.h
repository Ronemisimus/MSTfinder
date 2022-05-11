#include "general.h"


template <class K, class V> class HashMap
{
    V* value_arr;
    Natural maxCapacity;
    Natural itemCount;
    Natural (*hash)(K& key,Natural attempt);

    public:
    HashMap(Natural (*hash)(K& key,Natural attempt));
    ~HashMap();
    void MakeEmpty(Natural itemCount);
    bool isEmpty();
    V& operator[](K& key);
};