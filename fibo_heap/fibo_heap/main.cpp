#include <iostream>
#include <stdlib.h>
using namespace std;

struct nod{
public:
    int valoare;
    int grad;
    nod *stanga;
    nod *dreapta;
    nod *tata;
    nod *fiu;
};

class fibo_heap{
public:
    int nr_radacini = 0;
    nod *min = new nod();

    void inserare(int valoare)
    {
        if(this->nr_radacini == 0)
            this->min->valoare = valoare;
        else
        {
            nod *nod_nou = new nod();
            nod_nou->valoare = valoare;
            nod_nou->stanga = min->stanga;
            nod_nou->dreapta = min;
            min->stanga = nod_nou;
            if(nod_nou->valoare < min->valoare)
                min = nod_nou;
        }
        this->nr_radacini++;
    }
    
    int getMin() {return this->min->valoare;}
    
//    void extragereMin()
//    {
//        nod *i = new nod();
//        if(min->fiu != NULL)
//        {
//            if(min->dreapta == NULL)
//                min->stanga = NULL;
//
//        }
//    }
    
    void display()
    {
        nod *i = min->stanga;
        cout << min->valoare << endl;
        while (i != NULL)
        {
            cout << i->valoare << endl;
            i = i->stanga;
        }
        i = min->dreapta;
        while (i != NULL)
        {
            cout << i->valoare << endl;
            i = i->dreapta;
        }
        cout << "min: " << min->valoare << endl;
        cout << "nr rad: " << this->nr_radacini << endl;
    }
};


int main()
{
    fibo_heap fp;
    fp.inserare(3);
    fp.inserare(-4);
    fp.inserare(3);
    fp.inserare(1);
    fp.display();
}
