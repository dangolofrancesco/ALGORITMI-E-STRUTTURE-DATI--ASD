//
// Created by Francesco D'Angolo on 16/12/22.
//

#include "Heap.h"
#include "Item.h"

struct heap{
    Item *A;
    int heapsize;
};

//calcoliamo indice dei filgi
int LEFT(int i) { return (i*2 + 1); }
int RIGHT(int i) { return (i*2 + 2); }
int PARENT(int i) { return ((i-1)/2); }

Heap HEAPinit(int maxN){
    Heap h;
    h = malloc(sizeof (*h));
    h->A = malloc(maxN*sizeof (Item));
    h->heapsize=0;
    return h;
}

void HEAPfree(Heap h){
    free(h->A);
    free(h);
};

//Funzione per inserire i valori. Viene aggiunto
//un elemento in fondo al vettore e viene
//incrementato heapsize.
//Non necessariamente il risultato sarà un heap,
//in quanto non è garantito il rispetto della
//proprietà funzionale
void HEAPfill(Heap h, Item val){
    int i;
    i = h->heapsize++;
    h->A[i] = val;
    return;
}

void HEAPdisplay(Heap h){
    int i;
    for (i=0; i<h->heapsize; i++)
        ITEMstore(h->A[i]);
}

void Swap(Heap h, int i, int largest){

}
void HEAPify(Heap h, int i){
    int l, r, largest;
    l = LEFT(i);
    r = RIGHT(i);
    // l<h->>heapsize: indica se il figlio esiste, altrimenti ho una foglia
    if ((l<h->heapsize) && KEYcompare(KEYget(h->A[l]), KEYget(h->A[i]))==1)
        largest=l;
    else
        largest=i;
    if ((r<h->heapsize) && KEYcompare(KEYget(h->A[r]), KEYget(h->A[i]))==1)
        largest=r;
    if (largest!=i){
        //scambio i con largest
        Swap(h, i, largest);
        HEAPify(h, largest);
    }
}

void HEAPbuild(Heap h){
    int i;
    for (i=PARENT(h->heapsize-1); i>=0; i--)
        HEAPify(h, i);
}

void HEAPsort(Heap h){
    int i, j;
    HEAPbuild(h);
    j = h->heapsize;
    for (i=h->heapsize-1; i>0; i--){
        Swap(h, 0, i);
        h->heapsize--;
        HEAPify(h, 0);
    }
    h->heapsize=j;
}