#include <iostream>
#include <vector>
#include "Fibo_Heap.hpp"
using namespace std;


int main()
{
    FiboHeap F;
    F.inserare(5);
    F.inserare(3);
    F.inserare(1);
    F.inserare(8);
    F.extragereMin();
    F.display();
}

