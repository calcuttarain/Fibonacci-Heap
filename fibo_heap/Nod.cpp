#include "Nod.hpp"

void ListaNoduri::appendNod(int valoare)
{
    Nod* nou = new Nod(valoare);

    if (cap == nullptr)
    {
        cap = nou;
        coada = nou;
        cap->stanga = coada;
        coada->dreapta = cap;
    }
    else 
    {
        coada->stanga = nou;
        nou->dreapta = coada;
        nou->stanga = cap;
        cap->dreapta = nou;
        coada = nou;
    }
}

void ListaNoduri::appendNod(Nod* nou)
{
    if (cap == nullptr)
    {
        cap = nou;
        coada = nou;
        cap->stanga = coada;
        coada->dreapta = cap;
    }
    else
    {
        coada->stanga = nou;
        nou->dreapta = coada;
        nou->stanga = cap;
        cap->dreapta = nou;
        coada = nou;
    }
}

void ListaNoduri::unionList(ListaNoduri * lista) 
{
    if (cap == nullptr) 
    {
        cap = lista->cap;
        coada = lista->coada;
    } 
    else if (lista->cap != nullptr)
    {
        coada->dreapta = lista->cap;
        lista->cap->stanga = coada;
        coada = lista->coada;
        coada->dreapta = cap;
        cap->stanga = coada;
    }

    delete lista;
}

void ListaNoduri::deleteNod(Nod* nod)
{
    if(cap == coada)
    {
        cap = nullptr;
        coada = nullptr;
    }
    else if (nod == cap)
    {
        cap = cap->dreapta;
        cap->stanga = coada;
        coada->dreapta = cap;
    }
    else if (nod == coada)
    {
        coada = coada->stanga;
        coada->dreapta = cap;
        cap->stanga = coada;
    } 
    else
    {
        nod->dreapta->stanga = nod->stanga;
        nod->stanga->dreapta = nod->dreapta;
    }
    delete nod;
}

Nod* ListaNoduri::popNod(Nod* nod)
{
    if(cap == coada)
    {
        cap = nullptr;
        coada = nullptr;
    }
    if (nod == cap)
    {
        cap = cap->stanga;
        cap->dreapta = coada;
        
        coada->stanga = cap;
    }
    else if (nod == coada)
    {
        coada = coada->dreapta;
        coada->stanga = cap;
        cap->dreapta = coada;
    }
    else
    {
        nod->dreapta->stanga = nod->stanga;
        nod->stanga->dreapta = nod->dreapta;
    }
    return nod;
}

