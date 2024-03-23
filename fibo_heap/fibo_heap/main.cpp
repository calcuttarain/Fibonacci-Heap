#include <iostream>
#include "Fibo_Heap.hpp"
using namespace std;

bool ok;

int main()
{
    FiboHeap F;
    F.inserare(5);
    F.inserare(3);
    F.inserare(1);
    F.inserare(8);
    F.inserare(9);
    F.extragereMin();
    F.extragereMin();
    F.extragereMin();
    F.extragereMin();
    F.extragereMin();
    F.display();
    
}

