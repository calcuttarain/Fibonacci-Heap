#ifndef Fibo_Heap_hpp
#define Fibo_Heap_hpp

#include <iostream>
#include <vector>
#include "Nod.hpp"

class FiboHeap{
public:
    int nr_radacini;
    int grad_maxim;
    Nod* min;
    ListaNoduri* radacini;
    
public:
    FiboHeap() : nr_radacini(0), grad_maxim(0), min(nullptr) , radacini(nullptr){}
    
    void inserare(int);
    void inserare(Nod*);
    
    int getMin();
    
    void reuniuneBin();
    
    void extragereMin();
    
    void display();
};

#endif /* Fibo_Heap_hpp */
