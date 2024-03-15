#include "Fibo_Heap.hpp"

void FiboHeap::inserare(int valoare)
{
    Nod* nod = new Nod(valoare);
    //lista dublu inlantuita circulara
    if(!min)
    {
        min = nod;
        nod->stanga = nod;
        nod->dreapta = nod;
    }
    //inserez la stanga minimului O(1) + actualizez min
    else
    {
        if(!min->stanga)
            min->stanga = nod;
        else
        {
            Nod* stanga_min = min->stanga;
            nod->dreapta = min;
            nod->stanga = min->stanga;
            min->stanga = nod;
            nod->stanga = stanga_min;
        }
        if(min->valoare > nod->valoare)
            min = nod;
    }
    nr_radacini++;
}

void FiboHeap::inserare(Nod* nod)
{
    if(!min)
    {
        min = nod;
        nod->stanga = nod;
        nod->dreapta = nod;
    }
    else
    {
        if(!min->stanga)
            min->stanga = nod;
        else
        {
            Nod* stanga_min = min->stanga;
            nod->dreapta = min;
            nod->stanga = min->stanga;
            min->stanga = nod;
            nod->stanga = stanga_min;
        }
        if(min->valoare > nod->valoare)
            min = nod;
    }
    nr_radacini++;
}

int FiboHeap::getMin()
{
    return min->valoare;
}

void FiboHeap::reuniuneBin() //payback time
{
    //facem un vector de grad_max+1 elemente in care stocam referinta la arbore pe pozitia corespunzatoare lui
    std::vector<Nod*> grade(grad_maxim + 1, nullptr);
    Nod* i = min;
    do {
        if(!grade[i->grad])
            grade[i->grad] = i;
        //        else
        //        {
        //            Nod* arb1 = grade[i->grad];
        //            Nod* arb2 = i;
        //            //daca nu are fii
        //            if(!i->grad)
        //            {
        //                if(arb1->valoare < arb2->valoare)
        //                {
        //                    //link tata-fiu
        //                    arb1->fiu = arb2;
        //                    arb2->tata = arb1;
        //                    //il scot din lista de radacini
        //                    Nod* stanga_arb2 = arb2->stanga;
        //                    Nod* dreapta_arb2 = arb2->dreapta;
        //                    stanga_arb2->dreapta = dreapta_arb2;
        //                    dreapta_arb2->stanga = stanga_arb2;
        //                    arb2->stanga = nullptr;
        //                    arb2->dreapta = nullptr;
        //                    //update vector grade
        //                    grade[0] = nullptr;
        //                    grade[1]
        //                }
        //                else
        //                {
        //                    arb2->fiu = arb1;
        //                    arb1->tata = arb2;
        //
        //                    Nod* stanga_arb1 = arb1->stanga;
        //                    Nod* dreapta_arb1 = arb1->dreapta;
        //                    stanga_arb1->dreapta = dreapta_arb1;
        //                    dreapta_arb1->stanga = stanga_arb1;
        //                    arb1->stanga = nullptr;
        //                    arb1->dreapta = nullptr;
        //
        //                }
        //
        //            }
        //        }
        
        
    } while (i != min);
    
}

void FiboHeap::extragereMin()
{
    std::cout << "\tMinimul extras are valoarea " << getMin() << std::endl;
    //daca minimul are fii, ii inserez in lista de radacini
    if(min->fiu)
    {
        //unlink
        Nod* min_fiu = min->fiu;
        min_fiu->tata = nullptr;
        min->fiu = nullptr;
        
        if(min->grad == 1)
        {
            this->inserare(min_fiu);
        }
        else
        {
            Nod* i = min_fiu;
            //aici foloseste faptul ca listele sunt circulare
            while (i->stanga != min_fiu)
            {
                //bye tata
                i->tata = nullptr;
                i = i->stanga;
                nr_radacini ++;
            }
            nr_radacini --;
            //iau toata lista dublu inlantuita si o inserez la stanga minimului
            Nod *min_stanga = min->stanga;
            min->stanga = i;
            i->dreapta = min;
            min_fiu->stanga = min_stanga;
            if(min_stanga)
                min_stanga->dreapta = min_fiu;
        }
    }
    
    //sterg minimul
    Nod* temp = min;
    Nod* min_dreapta = min->dreapta;
    min = min->stanga;
    min->dreapta = min_dreapta;
    min_dreapta->stanga = min;
    delete temp;
    
    //"reuniune" heap binomial
    this->reuniuneBin();
}

void FiboHeap::display()
{
    std::cout << "Minimul: " << this->getMin() << std::endl;
    std::cout << "Radacini: ";
    Nod* i = min;
    do {
        std::cout << i->valoare << " ";
        i = i->stanga;
    } while (i != min);
}
