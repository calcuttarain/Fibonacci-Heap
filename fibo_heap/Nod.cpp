#include "Nod.hpp"

void Nod::display() //reluat, arat la fiecare nod fiii pe nivele
{
    if(grad == 0)
        std::cout << "Nodul " << valoare << " nu are fii" << std::endl;
    else
    {
        std::cout << "Nodul " << valoare << " are urmatorii fii: ";
        Nod* i = fiu;
        while(i != NULL)
        {
            std::cout << i->valoare << " ";
            i = i->dreapta;
        }
        std::cout << std::endl;
        i = fiu->dreapta;
        while(i != NULL)
        {
            i->display();
            i = i->dreapta;
        }
    }
}
