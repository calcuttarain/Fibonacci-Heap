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
    //facem un vector de grad_max+1 elemente in care stocam referinta la subarbore pe pozitia corespunzatoare intaltimii lui
    std::vector<Nod*> grade(grad_maxim + 1, nullptr);
    int locuri_ocupate = 1;
    grade[min->grad] = min;
    Nod* i = min->stanga;
    //practic, reuniunea e gata atunci cand fiecare radacina e in acel vector de grade (cand fiecare radacina are inaltimea diferita)
    while(locuri_ocupate != this->nr_radacini)
    {
        //si acum efectiv fac cu i doar!!!
        while(grade[i->grad]) //cat timp se tot unesc arbori
        {
            //aici scriu ce se intampla cand i da de o alta radacina pe grade[i->grad] + la final decrementez radacinile
            Nod* fiu_i;
            //care e mai mic
            if(i->valoare < grade[i->grad]->valoare)
                fiu_i = grade[i->grad];
            else
            {
                fiu_i = i;
                i = grade[i->grad];
            }
            
            //acum il scoatem din lista de radacini pe cel mai mare -> aici ar putea fi o pb si la stergerea minimului !ba nu, doar daca radacinile au un sg element(cred)
            Nod* f_stanga = fiu_i->stanga;
            Nod* f_dreapta = fiu_i->dreapta;
            if(!f_stanga)
                f_stanga->dreapta = f_dreapta;
            if(!f_dreapta)
                f_dreapta->stanga = f_stanga;
            
            //daca e inaltimea 0 => fiul va fi primul din lista circulara dublu-inlantuita
            if(i->grad == 0)
            {
                fiu_i->tata = i;
                i->fiu = fiu_i; //asta nu mai tb daca h != 0
                fiu_i->stanga = fiu_i;
                fiu_i->dreapta = fiu_i;
            }
            //altfel il inserez la stanga fiului 1
            else
            {
                fiu_i->tata = i;
                Nod* stanga_fiu_mare = i->fiu->stanga;
                i->fiu->stanga = fiu_i;
                fiu_i->dreapta = i->fiu;
                fiu_i->stanga = stanga_fiu_mare;
                stanga_fiu_mare->dreapta = fiu_i;
            }
            i->grad ++;
        }
        grade[i->grad] = i;
        locuri_ocupate ++;
        i = i->stanga;
    }
    
}

void FiboHeap::extragereMin()
{
    //std::cout << "Minimul extras are valoarea " << getMin() << std::endl;
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
    if(nr_radacini > 1)
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

//cum lista e circulara, sa am grija sa nu pastrez min cand il scot ptc am referinta de la el la el (oare e o pb?)
//nu merge extragere_min pt o sg radacina
