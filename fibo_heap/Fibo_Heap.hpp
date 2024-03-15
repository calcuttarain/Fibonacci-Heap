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
    
//    void display()
//    {
//        if(nr_radacini > 0)
//        {
//            Nod *i = min->stanga;
//            cout << "\tRadacinile din heap: ";
//            while (i != NULL)
//            {
//                cout << i->valoare << ", ";
//                i = i->stanga;
//            }
//            i = min->dreapta;
//            while (i != NULL)
//            {
//                cout << i->valoare << ", ";
//                i = i->dreapta;
//            }
//            cout << min->valoare << "." << endl;
//            if(grad_maxim > 0)
//            {
//                cout << "\tArborii: " << endl;
//                Nod*i = min->stanga;
//                while(i != NULL)
//                {
//                    i->display();
//                    i = i->stanga;
//                }
//                i = min->dreapta;
//                while(i != NULL)
//                {
//                    i->display();
//                    i = i->dreapta;
//                }
//                min->display();
//            }
//            cout << "\tMinimul: " << min->valoare << endl;
//            cout << "\tNumarul radacinilor: " << this->nr_radacini << endl;
//        }
//        else cout << "Hipul este gol." << endl;
//    }
    
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
