#include "heap.h"

#include <iostream>

Natural hash(int& value, Natural attempt)
{
    return (Natural)value-1;
}

int main()
{
    
    heap<int,int> h = heap<int,int>(hash);
    
    int values[] = {1,2,3,4,5,6,7};
    //            0 1  2 3  4  5  6
    int keys[] = {5,2,-7,4,10,-3,-1};

    h.Build(values,keys,7);

    std::cout << h << "\n";

    h.DecreaseKey(4, -2);
    
    std::cout << h << "\n";

    std::cout << h.Top() << "\n";

    h.deleteTop();

    std::cout << h << '\n';

    std::cout << h.isEmpty() << '\n';

}