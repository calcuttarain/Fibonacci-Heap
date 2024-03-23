#ifndef Nod_hpp
#define Nod_hpp

#include <iostream>

struct Nod{
    int valoare;
    int grad; //aparent, gradul unui nod n e totuna cu inaltime subarborelui in care e radacina n -> legatura cu Fibonacci
    Nod* stanga;
    Nod* dreapta;
    Nod* tata;
    Nod* cap_fii;
    Nod* coada_fii;
    
    Nod(int valoare) : valoare(valoare), grad(0), stanga(nullptr), dreapta(nullptr), tata(nullptr), cap_fii(nullptr), coada_fii(nullptr) {}
};

class ListaNoduri{
public:
    Nod* cap;
    Nod* coada;

    ListaNoduri() : cap(nullptr), coada(nullptr) {}
    ListaNoduri(Nod* cap, Nod* coada) : cap(cap), coada(coada) {}
    
    void appendNod(int);
    void appendNod(Nod*);
    void deleteNod(Nod*);
    void unionList(ListaNoduri*);
    Nod* popNod(Nod*);
};

#endif
