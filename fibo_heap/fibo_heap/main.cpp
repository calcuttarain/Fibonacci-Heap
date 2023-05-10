#include <iostream>
#include <vector>
using namespace std;

struct nod{
public:
    int valoare;
    int grad;
    nod *stanga;
    nod *dreapta;
    nod *tata;
    nod *fiu;
    nod()
    {
        valoare = NULL;
        grad = 0;

    }
};

class fibo_heap{
public:
    int nr_radacini = 0;
    int grad_maxim = 0;
    nod *min = new nod();
    
//    fibo_heap& operator = (const fibo_heap &f)
//    {
//        this->nr_radacini = f.nr_radacini;
//        this->min = f.min;
//        return *this;
//    }

    void inserare(int valoare)
    {
        if(this->nr_radacini == 0)
            this->min->valoare = valoare;
        else
        {
            nod *nod_nou = new nod();
            nod_nou->valoare = valoare;
            if(min->stanga != NULL)
            {
                //link nod_stanga_min -> nod_nou
                min->stanga->dreapta = nod_nou;
                //link nod_nou -> nod_stanga_min
                nod_nou->stanga = min->stanga;
            }
            //link nod_nou -> min
            nod_nou->dreapta = min;
            //link min -> nod_nou
            min->stanga = nod_nou;
            if(nod_nou->valoare < min->valoare)
                min = nod_nou;
        }
        this->nr_radacini++;
    }
    
    int getMin() {return this->min->valoare;}
    
    void extragereMin()
    {
        nod *i = new nod();
        nod *j = new nod();
        nod *new_min = new nod();
        
        //daca minimul are fii, ii inserez in lista de radacini
        
        if(min->fiu != NULL)
        {
            //fiii de pe dreapta
            if(min->fiu->dreapta != NULL)
            {
                i = min->fiu->dreapta;
                while(i != NULL)
                {
                    //unlink tata
                    i->tata = NULL;
                    //memorez urmatorul
                    j = i->dreapta;
                    if(min->stanga != NULL)
                    {
                        //link nod_stanga_min -> nod_nou
                        min->stanga->dreapta = i;
                        //link nod_nou -> nod_stanga_min
                        i->stanga = min->stanga;
                    }
                    //link nod_nou -> min
                    i->dreapta = min;
                    //link min -> nod_nou
                    min->stanga = i;
                    i = j;
                }
            }
            //fiii de pe stanga
            if(min->fiu->stanga != NULL)
            {
                i = min->fiu->stanga;
                while(i != NULL)
                {
                    //unlink tata
                    i->tata = NULL;
                    //memorez urmatorul
                    j = i->dreapta;
                    //inserez in radacini
                    if(min->stanga != NULL)
                    {
                        //link nod_stanga_min -> nod_nou
                        min->stanga->dreapta = i;
                        //link nod_nou -> nod_stanga_min
                        i->stanga = min->stanga;
                    }
                    //link nod_nou -> min
                    i->dreapta = min;
                    //link min -> nod_nou
                    min->stanga = i;
                    i = j;
                }
            }
            //inserez fiul in radacini
            min->fiu->tata = NULL;
            if(min->stanga != NULL)
            {
                //link nod_stanga_min -> nod_nou
                min->stanga->dreapta = min->fiu;
                //link nod_nou -> nod_stanga_min
                min->fiu->stanga = min->stanga;
            }
            //link nod_nou -> min
            min->fiu->dreapta = min;
            //link min -> nod_nou
            min->stanga = min->fiu;
        }
        
        //stergerea minimului
        
        //daca e la final de lista
        if(min->dreapta == NULL && min->stanga != NULL)
        {
            new_min = min->stanga;
            i = new_min->stanga;
            
            //cautare noul minim
            while(i != NULL)
            {
                if(i->valoare < new_min->valoare)
                    new_min = i;
                i = i->stanga;
            }
            
            //unlink
            min->stanga->dreapta = NULL;
            min->stanga = NULL;
            min = new_min;
            nr_radacini --;
        }
        
        //daca e la inceput de lista
        else if(min->stanga == NULL && min->dreapta != NULL)
        {
            new_min = min->dreapta;
            i = new_min->dreapta;
            
            //noul min
            while(i != NULL)
            {
                if(i->valoare < new_min->valoare)
                    new_min = i;
                i = i->dreapta;
            }
            
            //unlink
            min->dreapta->stanga = NULL;
            min->dreapta = NULL;
            
            min = new_min;
            nr_radacini --;
        }
        
        //daca e in interiorul listei
        else if(min->stanga != NULL && min->dreapta != NULL)
        {
            //caut in stanga min nou
            new_min = min->stanga;
            i = new_min->stanga;
            while(i != NULL)
            {
                if(i->valoare < new_min->valoare)
                    new_min = i;
                i = i->stanga;
            }
            
            //caut in dreapta min nou
            i = min->dreapta;
            while(i != NULL)
            {
                if(i->valoare < new_min->valoare)
                    new_min = i;
                i = i->dreapta;
            }
            
            //unlink
            min->dreapta->stanga = min->stanga;
            min->stanga->dreapta = min->dreapta;
            min->dreapta = NULL;
            min->stanga = NULL;
            
            min = new_min;
            nr_radacini --;
            }
            
        //daca e singurul din lista
        else if(min->stanga == NULL && min->dreapta == NULL)
        {
            this->nr_radacini = 0;
            min->valoare = NULL;
        }
        
        //reuniune
        if(nr_radacini > 1)
        {
            //grad = h arbore. memorez pointeri la noduri in functie de inaltimea arborilor
            vector <nod*> vector_grade;
            for(int x = 0; x<=grad_maxim; x++)
                vector_grade.push_back(NULL);
            
            //merg pe stanga
            if (min->stanga != NULL)
            {
                i = min->stanga;
                while(i != NULL)
                {
                    //daca nu au mai fost inserate noduri cu gradul nodului curent
                    if(vector_grade[i->grad] == NULL)
                        vector_grade[i->grad] = i;
                    //daca a mai fost inserat un nod cu gradul nodului curent
                    else
                    {
                        if(vector_grade[i->grad]->valoare <= i->valoare)
                        {
                            //legatura cu unul dintre fii.
                            if(i->grad == 0)
                                vector_grade[i->grad]->fiu = i;
                            //daca are deja fiu, il leg de restul fiiilor
                            else
                            {
                                j = vector_grade[i->grad]->fiu;
                                while(j != NULL)
                                    j = j->dreapta;
                                j = i;
                                i->stanga = j;
                                i->dreapta = NULL;
                            }
                            i->tata = vector_grade[i->grad];
                        }
                        else if(i->valoare < vector_grade[i->grad]->valoare)
                        {
                            //legatura cu unul dintre fii.
                            if(i->grad == 0)
                                i->fiu = vector_grade[i->grad];
                            //daca are deja fiu, il leg de restul fiiilor
                            else
                            {
                                j = i->fiu;
                                while(j != NULL)
                                    j = j->dreapta;
                                j = i;
                                vector_grade[i->grad]->stanga = j;
                                vector_grade[i->grad]->dreapta = NULL;
                            }
                            vector_grade[i->grad]->tata = i;
                            vector_grade[i->grad] = i;
                        }
                        //increase grad
                        vector_grade[i->grad]->grad ++;
                        //actualizez grad_maxim
                        if(vector_grade[i->grad]->grad > grad_maxim)
                        {
                            grad_maxim = vector_grade[i->grad]->grad;
                            vector_grade.push_back(NULL);
                        }
                        //mut in alta casuta
                        vector_grade[vector_grade[i->grad]->grad] = vector_grade[i->grad];
                        vector_grade[i->grad] = NULL;
                    }
                    i = i->stanga;
                }
            }
            
            //merg pe dreapta
            if (min->dreapta != NULL)
            {
                i = min->dreapta;
                while(i != NULL)
                {
                    //daca nu au mai fost inserate noduri cu gradul nodului curent
                    if(vector_grade[i->grad] == NULL)
                        vector_grade[i->grad] = i;
                    //daca a mai fost inserat un nod cu gradul nodului curent
                    else
                    {
                        if(vector_grade[i->grad]->valoare <= i->valoare)
                        {
                            //legatura cu unul dintre fii.
                            if(i->grad == 0)
                                vector_grade[i->grad]->fiu = i;
                            //daca are deja fiu, il leg de restul fiiilor
                            else
                            {
                                j = vector_grade[i->grad]->fiu;
                                while(j != NULL)
                                    j = j->dreapta;
                                j = i;
                                i->stanga = j;
                            }
                            i->tata = vector_grade[i->grad];
                        }
                        else if(i->valoare < vector_grade[i->grad]->valoare)
                        {
                            //legatura cu unul dintre fii.
                            if(i->grad == 0)
                                i->fiu = vector_grade[i->grad];
                            //daca are deja fiu, il leg de restul fiiilor
                            else
                            {
                                j = i->fiu;
                                while(j != NULL)
                                    j = j->dreapta;
                                j = i;
                                vector_grade[i->grad]->stanga = j;
                            }
                            vector_grade[i->grad]->tata = i;
                        }
                        //increase grad
                        vector_grade[i->grad]->grad ++;
                        //actualizez grad_maxim
                        if(vector_grade[i->grad]->grad > grad_maxim)
                            grad_maxim = vector_grade[i->grad]->grad;
                        //mut in alta casuta
                        vector_grade[vector_grade[i->grad]->grad] = vector_grade[i->grad];
                        vector_grade[i->grad] = NULL;
                    }
                    i = i->dreapta;
                }
            }
            
            
        }
    }
    
    void display()
    {
        nod *i = min->stanga;
        cout << "Elementele din heap: ";
        while (i != NULL)
        {
            cout << i->valoare << ", ";
            i = i->stanga;
        }
        i = min->dreapta;
        while (i != NULL)
        {
            cout << i->valoare << ", ";
            i = i->dreapta;
        }
        cout << min->valoare << "." << endl;
        cout << "Minimul: " << min->valoare << endl;
        cout << "Numarul radacinilor: " << this->nr_radacini << endl;
    }
};


int main()
{
    fibo_heap fp;

    fp.inserare(2);
    fp.inserare(1);
    fp.inserare(3);
    fp.extragereMin();
    fp.display();
    //pt insertion mai am:
    //linia 282: daca in casuta aia mai e deja un arbore? rezolva cu recursie
    //parcurgere vector_grade, reactualizare radacini
    
    //implementare decrease_value
}

