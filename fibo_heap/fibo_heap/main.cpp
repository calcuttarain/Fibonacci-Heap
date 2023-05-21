#include <iostream>
#include <vector>
using namespace std;

struct nod{
public:
    int valoare;
    int grad = 0;
    nod *stanga;
    nod *dreapta;
    nod *tata;
    nod *fiu;
    nod()
    {
        valoare = -1;
        grad = 0;
    }
    void delete_nod()
    {
        valoare = NULL;
        grad = NULL;
        stanga = NULL;
        dreapta = NULL;
        tata = NULL;
        fiu = NULL;
    }
    nod* operator = (const nod *n)
    {
        this->valoare = n->valoare;
        this->grad = n->grad;
        this->stanga = n->stanga;
        this->dreapta = n->dreapta;
        this->tata = n->tata;
        this->fiu = n->fiu;
        return this;
    }
    void display()
    {
        if(grad == 0)
            cout << "Nodul " << valoare << " nu are fii" << endl;
        else
        {
            cout << "Nodul " << valoare << " are urmatorii fii: ";
            nod* i = fiu;
            while(i != NULL)
            {
                cout << i->valoare << " ";
                i = i->dreapta;
            }
            cout << endl;
            i = fiu->dreapta;
            while(i != NULL)
            {
                i->display();
                i = i->dreapta;
            }
        }
    }
};

class fibo_heap{
public:
    int nr_radacini = 0;
    int grad_maxim = 0;
    nod *min = new nod();
    
    fibo_heap()
    {
        nr_radacini = 0;
        grad_maxim = 0;
    }
    
    fibo_heap(const fibo_heap &fh)
    {
        nr_radacini = fh.nr_radacini;
        grad_maxim = fh.grad_maxim;
        min = fh.min;
    }
    
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
    
    void inserare(nod *n)
    {
        if(this->nr_radacini == 0)
            this->min = n;
        else
        {
            if(min->stanga != NULL)
            {
                //link nod_stanga_min -> nod_nou
                min->stanga->dreapta = n;
                //link nod_nou -> nod_stanga_min
                n->stanga = min->stanga;
            }
            //link nod_nou -> min
            n->dreapta = min;
            //link min -> nod_nou
            min->stanga = n;
            if(n->valoare < min->valoare)
                min = n;
        }
        this->nr_radacini++;
    }
    
    int getMin() {return this->min->valoare;}
    
    void delete_fh()
    {
        nr_radacini = 0;
        grad_maxim = 0;
        delete min;
    }
    
    void extragereMin()
    {
        nod *i = new nod();
        nod *j = new nod();
        //nod *new_min = new nod();
        
        cout << "\tMinimul extras are valoarea " << min->valoare << endl;
        //daca minimul are fii, ii inserez in lista de radacini
        if(min->fiu != NULL)
        {
            //unlink tata
            min->fiu->tata = NULL;
            if(min->grad == 1)
            {
                min->fiu->dreapta = min->dreapta;
                min->fiu->stanga = min->stanga;
                min = min->fiu;
                nr_radacini ++;
            }
            else
            {
                i = min->fiu;
                while (i->dreapta != NULL)
                {
                    //unlink tata
                    i->tata = NULL;
                    i = i->dreapta;
                    //incrementez nr radacini pt fii
                    nr_radacini ++;
                }
                
                //decrementez nr radacini pt min
                nr_radacini --;
                //legare lista dublu-inlantuita frati de stanga min + stergere min
                if(min->stanga == NULL)
                {
                    if(min->dreapta != NULL)
                    {
                        i->dreapta = min->dreapta;
                        min->dreapta->stanga = i;
                    }
                    min = i;
                }
                else{
                    if(min->dreapta != NULL)
                    {
                        min->dreapta->stanga = i;
                        i->dreapta = min->dreapta;
                    }
                    min->fiu->stanga = min->stanga;
                    min->stanga = min->fiu;
                    min = i;
                }
            }
        }
        
        else{
            if (min->dreapta == NULL && min->stanga == NULL)
                delete min;
            else if (min->dreapta != NULL && min->stanga != NULL)
            {
                min->dreapta->stanga = min->stanga;
                min->stanga->dreapta = min->dreapta;
                j = min->dreapta;
                min = j;
                
            }
            else if(min->dreapta != NULL && min->stanga == NULL)
            {
                min->dreapta->stanga = NULL;
                j = min->dreapta;
                delete min;
                min = j;
            }
            else if(min->dreapta == NULL && min->stanga != NULL)
            {
                min->stanga->dreapta = NULL;
                j = min->stanga;
                delete min;
                min = j;
            }
            nr_radacini --;
        }
        //"reuniune" heap binomial
        if(nr_radacini > 1)
        {
            //grad = h arbore. memorez pointeri la noduri in functie de inaltimea arborilor
            vector <nod*> vector_grade;
            for(int x = 0; x <= grad_maxim; x++)
                vector_grade.push_back(NULL);
            vector_grade[min->grad] = min;
            nod* min1 = min->dreapta;
            //merg pe stanga
            if (min->stanga != NULL)
            {
                i = min->stanga;
                while(i != NULL)
                {
                    nod* si = i->stanga;
                    nod* radacina = i;
                    j = vector_grade[i->grad];
                    radacina->dreapta = NULL;
                    radacina->stanga = NULL;
                    while (j != NULL)
                    {
                        if(j->valoare < radacina->valoare)
                        {
                            nod *aux = new nod();
                            nod *aux1 = new nod();
                            if(j->grad == 0)
                                j->fiu = radacina;
                            else
                            {
                                aux = j->fiu;
                                while (aux->dreapta != NULL)
                                    aux = aux->dreapta;
                                aux->dreapta = radacina;
                                radacina->stanga = aux;
                            }
                            radacina->tata = j;
                            //?
                            aux1 = radacina;
                            radacina = j;
                            j = aux1;
                        }
                        else
                        {
                            if(radacina->grad == 0)
                                radacina->fiu = j;
                            else
                            {
                                nod* aux = radacina->fiu;
                                while (aux->dreapta != NULL)
                                    aux = aux->dreapta;
                                aux->dreapta = j;
                                j->stanga = aux;
                            }
                            j->tata = radacina;
                        }
                        vector_grade[radacina->grad] = NULL;
                        radacina->grad ++;
                        j = vector_grade[radacina->grad];
                    }
                    radacina->dreapta = NULL;
                    radacina->stanga = NULL;
                    if(radacina->grad == vector_grade.size())
                        vector_grade.push_back(NULL);
                    vector_grade[radacina->grad] = radacina;
                    i = si;
                }
            }
            //merg pe dreapta
            if (min1 != NULL)
            {
                i = min1;
                while(i != NULL)
                {
                    nod* di = i->dreapta;
                    nod* radacina = i;
                    j = vector_grade[i->grad];
                    radacina->dreapta = NULL;
                    radacina->stanga = NULL;
                    while (j != NULL)
                    {
                        if(j->valoare < radacina->valoare)
                        {
                            nod *aux = new nod();
                            nod *aux1 = new nod();
                            if(j->grad == 0)
                                j->fiu = radacina;
                            else
                            {
                                aux = j->fiu;
                                while (aux->dreapta != NULL)
                                    aux = aux->dreapta;
                                aux->dreapta = radacina;
                                radacina->stanga = aux;
                            }
                            radacina->tata = j;
                            //?
                            aux1 = radacina;
                            radacina = j;
                            j = aux1;
                        }
                        else
                        {
                            if(radacina->grad == 0)
                                radacina->fiu = j;
                            else
                            {
                                nod* aux = radacina->fiu;
                                while (aux->dreapta != NULL)
                                    aux = aux->dreapta;
                                aux->dreapta = j;
                                j->stanga = aux;
                            }
                            j->tata = radacina;
                        }
                        vector_grade[radacina->grad] = NULL;
                        radacina->grad ++;
                        j = vector_grade[radacina->grad];
                    }
                    radacina->dreapta = NULL;
                    radacina->stanga = NULL;
                    if(radacina->grad == vector_grade.size())
                        vector_grade.push_back(NULL);
                    vector_grade[radacina->grad] = radacina;
                    i = di;
                }
            }
            //reconstruiesc heapul inserand fiecare arbore
            nr_radacini = 0;
            grad_maxim = 0;
            //min = NULL;
            grad_maxim = int(vector_grade.size());
            for(int i = 0; i < vector_grade.size(); i++)
            {
                if(vector_grade[i] != NULL)
                {
                    if(this->nr_radacini == 0)
                    {
                        min = vector_grade[i];
                        if(min->grad > 1)
                        {
                            nod* aux = min->fiu;
                            while(aux->dreapta != min && aux->dreapta != NULL)
                                aux = aux->dreapta;
                            if (aux->dreapta == min)
                                aux->dreapta = NULL;
                        }
                    }
                    else
                    {
                        if(min->stanga != NULL)
                        {
                            //link nod_stanga_min -> nod_nou
                            min->stanga->dreapta = vector_grade[i];
                            //link nod_nou -> nod_stanga_min
                            vector_grade[i]->stanga = min->stanga;
                        }
                        //link nod_nou -> min
                        vector_grade[i]->dreapta = min;
                        //link min -> nod_nou
                        min->stanga = vector_grade[i];
                        if(vector_grade[i]->valoare < min->valoare)
                            min = vector_grade[i];
                    }
                    nr_radacini ++;
                }
            }
        }
    }
    
    void display()
    {
        if(nr_radacini > 0)
        {
            nod *i = min->stanga;
            cout << "\tRadacinile din heap: ";
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
            if(grad_maxim > 0)
            {
                cout << "\tArborii: " << endl;
                nod*i = min->stanga;
                while(i != NULL)
                {
                    i->display();
                    i = i->stanga;
                }
                i = min->dreapta;
                while(i != NULL)
                {
                    i->display();
                    i = i->dreapta;
                }
                min->display();
            }
            cout << "\tMinimul: " << min->valoare << endl;
            cout << "\tNumarul radacinilor: " << this->nr_radacini << endl;
        }
        else cout << "Hipul este gol." << endl;
    }
    
    fibo_heap& reuniune(fibo_heap &f)
    {
        nod* i = f.min;
        nod* j = f.min;
        this->nr_radacini ++;
        while(i->stanga != NULL)
        {
            i = i->stanga;
            nr_radacini ++;
        }
        while(j->dreapta != NULL)
        {
            j = j->dreapta;
            nr_radacini ++;
        }
        if(this->min->stanga != NULL)
        {
            min->stanga->dreapta = i;
            i->stanga = min->stanga;
        }
        min->dreapta = j;
        j->stanga = min;
        if(f.min->valoare < min->valoare)
        {
            int aux = f.min->valoare;
            f.min->valoare = min->valoare;
            min->valoare = aux;
        }
        return *this;
    }
};


int main()
{
    fibo_heap fp, f;
    fp.inserare(1);
    fp.inserare(2);
    fp.inserare(3);
    fp.extragereMin();
    f.inserare(4);
    f.inserare(5);
    f.inserare(6);
    f.extragereMin();
    fp.reuniune(f);
    fp.display();
//    fp.inserare(2);
//    fp.inserare(1);
//    fp.inserare(3);
//    fp.inserare(4);
//    fp.inserare(0);
//    fp.inserare(6);
//    fp.extragereMin();
//    fp.inserare(5);
//    fp.extragereMin();
//    fp.inserare(8);
//    fp.inserare(9);
//    fp.extragereMin();
//    fp.extragereMin();
//    fp.extragereMin();
//    fp.extragereMin();
//    //fp.extragereMin();
//    fp.display();
}

