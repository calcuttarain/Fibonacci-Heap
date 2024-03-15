#ifndef Fibo_Heap_hpp
#define Fibo_Heap_hpp

#include <iostream>
#include <vector>
#include "Nod.hpp"

class FiboHeap{
private:
    int nr_radacini;
    int grad_maxim;
    Nod* min;
    
public:
    FiboHeap() : nr_radacini(0), grad_maxim(0), min(nullptr) {}
    
    void inserare(int valoare);
    void inserare(Nod *nod);
    
    int getMin();
    
    void reuniuneBin();
    
    void extragereMin();
    
    void display();
    
    ~FiboHeap();
    
//    FiboHeap& reuniune(FiboHeap &f)
//    {
//        Nod* i = f.min;
//        Nod* j = f.min;
//        this->nr_radacini ++;
//        while(i->stanga != NULL)
//        {
//            i = i->stanga;
//            nr_radacini ++;
//        }
//        while(j->dreapta != NULL)
//        {
//            j = j->dreapta;
//            nr_radacini ++;
//        }
//        if(this->min->stanga != NULL)
//        {
//            min->stanga->dreapta = i;
//            i->stanga = min->stanga;
//        }
//        min->dreapta = j;
//        j->stanga = min;
//        if(f.min->valoare < min->valoare)
//        {
//            int aux = f.min->valoare;
//            f.min->valoare = min->valoare;
//            min->valoare = aux;
//        }
//        return *this;
//    }
};

#endif /* Fibo_Heap_hpp */
