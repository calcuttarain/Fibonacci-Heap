#ifndef Nod_hpp
#define Nod_hpp

#include <iostream>

class Nod{
public:
    int valoare;
    int grad; //aparent, gradul unui nod n e totuna cu inaltime subarborelui in care e radacina n -> legatura cu Fibonacci
    Nod *stanga;
    Nod *dreapta;
    Nod *tata;
    Nod *fiu;
    
    Nod(int valoare) : valoare(valoare), grad(0), stanga(nullptr), dreapta(nullptr), tata(nullptr), fiu(nullptr) {}

    void display();

};


#endif
