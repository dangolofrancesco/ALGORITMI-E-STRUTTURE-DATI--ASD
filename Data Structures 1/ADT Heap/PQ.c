//
// Created by Francesco D'Angolo on 16/12/22.
//


#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"
#include "Item.h"
#include "Heap.h"

struct pqueue{
    Item *A;
    int heapsize;
};


static LEFT(int i) { return (i*2 + 1); }
static RIGHT(int i) { return (i*2 + 2); }
static PARENT(int i) { return ((i-1)/2); }

PQ PQinit(int maxN){
    PQ pq = malloc(sizeof (*pq));
    pq->A = malloc(maxN*sizeof (Item));
    pq->heapsize=0;
    return pq;
}

void PQfree(PQ pq){
    free(pq->A);
    free(pq);
}

int PQempty(PQ pq){
    return pq->heapsize==0;
}

int PQsize(PQ pq){
    return pq->heapsize;
}

void PQdisplay(PQ pq){
    int i;
    for (i=0; i<pq->heapsize; i++)
    ITEMstore(pq->A[i]);
}

void PQinsert(PQ pq, Item val){
    int i;
    i = pq->heapsize++;
    while ((i>=1) && KEYcompare(KEYget(pq->A[PARENT(i)]), KEYget(val))==-1){
        pq->A[i]=pq->A[PARENT(i)];
        i = PARENT(i);
    }
    pq->A[i] = val;
    return;
}

void Swap(Heap h, int i, int largest){

}

Item PQextractMax(PQ pq){
    Item val;
    Swap(pq, 0, pq->heapsize-1);
    val = pq->A[pq->heapsize-1];
    pq->heapsize--;
    HEAPify(pq,0);
    return val;
}



void PQchange(PQ pq, Item val){
    int i, found=0, pos;
    for (i=0; i<pq->heapsize && found==0; i++){
        //Oppure con NAMEcmp e NAMEget se la ricerca è sul nome
        if (KEYcompare(KEYget(pq->A[i]), KEYget(val))==0){
            found=1;
            pos=i;
        }
    }

    if (found==1) {
        while (pos >= 1 && KEYcompare(KEYget(pq->A[PARENT(pos)]), KEYget(val)) == -1) {
            pq->A[pos] = pq->A[PARENT(pos)];
            pos = PARENT(pos);
        }
        pq->A[pos] = val;
        HEAPify(pq, pos);
    }
    else
        printf("Key not found!\n");
    return;
}