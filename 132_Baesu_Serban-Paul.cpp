#include <iostream>
#include<fstream>
#include<vector>

using namespace std;

ifstream f("mergeheap.in");
ofstream g("mergeheap.out");

class Nod
{
public:
    int valoare;
    Nod* copil;
    Nod* frate;

    Nod(int valoare){
        this->valoare = valoare;
        this->copil = NULL;
        this->frate = NULL;
    }

    ~Nod()
    {
        if(copil != NULL){
            delete copil;
            copil = NULL;
        }
        if(frate != NULL){
            delete frate;
            frate = NULL;
        }
    }
};

class PairingHeap
{
public:
    Nod* radacina;

    PairingHeap(){this->radacina = NULL;}
    PairingHeap(Nod* radacina){this->radacina = radacina;}
    PairingHeap(int x){this->radacina = new Nod(x);}

    void inserare(int x);
    void reuniune(PairingHeap& h);
    int stergere_max();

    ~PairingHeap(){}
};

void PairingHeap :: inserare(int x)
{
        if(this->radacina == NULL)
            this->radacina = new Nod(x);

        else{
            PairingHeap b(x);
            this->reuniune(b);
        }
    }

void PairingHeap :: reuniune(PairingHeap& h)
{
    if(this->radacina == NULL)
        *this = h;
    else if(this->radacina->valoare > h.radacina->valoare){
        h.radacina->frate = this->radacina->copil;
        this->radacina->copil = h.radacina;
    }
    else{
        this->radacina->frate = h.radacina->copil;
        h.radacina->copil = this->radacina;
        *this = h;
    }
    h.radacina = NULL;
}


int PairingHeap::stergere_max()
{
    int maxim = this->radacina->valoare;

    if (this->radacina->copil == NULL) {
        delete this->radacina;
        this->radacina = NULL;
    }
    else {
        vector<PairingHeap> subPairingHeaps;
        Nod* nod_curent = this->radacina->copil;

        while (nod_curent != NULL) {
            Nod* next_nod = nod_curent->frate;
            nod_curent->frate = NULL;
            subPairingHeaps.push_back(PairingHeap(nod_curent));
            nod_curent = next_nod;
        }

        this->radacina = subPairingHeaps[0].radacina;
        for (int i = 1; i < subPairingHeaps.size(); i++)
            this->reuniune(subPairingHeaps[i]);
    }

    return maxim;
}

int main()
{
    PairingHeap h[101];
    int n, q;
    f>>n>>q;
    for(int i=0; i<q; i++){
        int j, k, m;
        f>>j;
        switch(j)
        {
            case 1:{
                f>>k>>m;
                h[k].inserare(m);
                break;
            }
            case 2:{
                f>>k;
                g<<h[k].stergere_max()<<endl;
                break;
            }
            case 3:{
                f>>k>>m;
                h[k].reuniune(h[m]);
                break;
            }
        }
    }

    return 0;
}
