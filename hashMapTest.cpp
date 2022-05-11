#include <iostream> 

#include "hashMap.h"

Natural hash(int& value, Natural attermt)
{
    return (Natural)value;
}

int main()
{
    HashMap<int,Natural> h=HashMap<int,Natural>(hash);

    h.MakeEmpty(8);

    int values[] = {1,2,3,4,5,6,7,8};

    h[values[0]] = 2;
    h[values[1]] = 1;
    h[values[2]] = 0;

    std::cout << h[values[0]] << " " << h[values[1]] << " " << h[values[2]] <<'\n';
}