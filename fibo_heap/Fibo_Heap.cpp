#include "Fibo_Heap.hpp"

void FiboHeap::inserare(int valoare)
{
    if(!min)
    {
        ListaNoduri* lista = new ListaNoduri();
        lista->appendNod(valoare);
        min = lista->cap;
        radacini = lista;
        //delete lista;
    }
    //inserez la stanga minimului O(1) + actualizez min
    else
    {
        Nod* nou = new Nod(valoare);
        radacini->appendNod(nou);
        if(valoare < min->valoare)
            min = nou;
    }
    nr_radacini++;
}

int FiboHeap::getMin()
{
    return min->valoare;
}

void FiboHeap::reuniuneBin() //payback time
{
    std::vector<std::vector<Nod*>> grade(grad_maxim + 1);
    Nod* nod = radacini->cap;
    do {
        grade[nod->grad].push_back(nod);
        nod = nod->stanga;
    } while (nod != radacini->cap);
    int i = 0;
    //parcurg vectorul de grade
    while(i != grade.size())
    {
        //cat timp exista mai multe radacini cu gradul i
        while(grade[i].size() > 1)
        {
            Nod* mn;
            Nod* mx;
            if(grade[i][grade[i].size()-1]->valoare < grade[i][grade[i].size()-2]->valoare)
            {
                mn = grade[i][grade[i].size()-1];
                mx = grade[i][grade[i].size()-2];
            }
            else
            {
                mn = grade[i][grade[i].size()-2];
                mx = grade[i][grade[i].size()-1];
            }
            //sterg pe ala mai mare din radacini
            mx = radacini->popNod(mx);
            mx->tata = mn;
            //il adaug la fii
            ListaNoduri* lista_fii = new ListaNoduri(mn->cap_fii, mn->coada_fii);
            lista_fii->appendNod(mx);
            mn->cap_fii = lista_fii->cap;
            mn->coada_fii = lista_fii->coada;
            
            delete lista_fii;
            mn->grad++;
            grade[i].pop_back();
            grade[i].pop_back();
            if(i+1 >= grade.size())
            {
                grade.push_back({mn});
                grad_maxim ++;
            }
            else
                grade[i+1].push_back(mn);
        }
        i++;
        
    }
    //reactualizez minimul
    nod = radacini->cap;
    do {
        if(nod->valoare < min->valoare)
            min = nod;
        nod = nod->stanga;
    } while (nod != radacini->cap);
}

void FiboHeap::extragereMin()
{
    //daca minimul are fii, ii inserez in lista de radacini
    if(min->cap_fii != nullptr)
    {
        //unlink
        Nod* min_cap_fii = min->cap_fii;
        Nod* min_coada_fii = min->coada_fii;
        ListaNoduri* fii = new ListaNoduri(min_cap_fii, min_coada_fii);
        
        Nod* i = min_cap_fii;
        do {
            i -> tata = nullptr;
            i = i->stanga;
            nr_radacini++;
        } while (i != min_cap_fii);
        
        radacini->unionList(fii);
    }


    radacini->deleteNod(min);
    
    min = radacini->cap;
        
    
    //"reuniune" heap binomial
    if(radacini->cap != nullptr)
        this->reuniuneBin();
}

void FiboHeap::display()
{
    if (radacini->cap == nullptr)
    {
        std::cout << "Heapul nu are radacini!" << std::endl;
        return;
    }
    std::cout << "Minimul: " << getMin() << std::endl;
    Nod* curent = radacini->cap;
    std::cout << "Radacinile: ";
    do
    {
        std::cout << curent->valoare << " ";
        curent = curent->dreapta;
    } while (curent != radacini->cap);
    std::cout << std::endl;
}


