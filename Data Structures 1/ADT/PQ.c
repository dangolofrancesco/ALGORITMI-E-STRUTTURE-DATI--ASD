//
// Created by Francesco D'Angolo on 08/12/22.
//

#include "PQ.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct PQnode *link;
struct PQnode{
    Item val;
    link next;
};
struct pqueue {
    link head;
};

link NEW(Item val, link next) {
    link x = malloc(sizeof *x);
    x->val = val;
    x->next = next;
    return x;
}

PQ PQinit(int maxN) {
    PQ pq = malloc(sizeof *pq) ;
    pq->head = NULL;
    return pq;
}

int PQempty(PQ pq) {
    return pq->head == NULL;
}

Item PQshowMax(PQ pq) {
    //l'elemento a priorità massima è in testa
    return pq->head->val;
}

void PQdisplay(PQ pq) {
    link x;
    for (x=pq->head; x!=NULL; x=x->next)
        ITEMdisplay(x->val);
    return;
}

void PQinsert (PQ pq, Item val) {
    link x, p;
    Key k = KEYget(val);
    //inserimento in testa
    if (pq->head==NULL || KEYless(KEYget(pq->head->val),k)) {
        pq->head = NEW(val, pq->head);
        return;
    }
    //iniziamo dal secondo in lista
    for(x=pq->head->next, p=pq->head; x!=NULL && KEYless(k,KEYget(x->val)); p=x, x=x->next);
        p->next = NEW(val, x);
    return;
}

Item PQextractMax(PQ pq) {
    Item tmp;
    link t;
    if (PQempty(pq)) {
        printf("PQ empty\n");
        return ITEMsetvoid();
    }
    tmp = pq->head->val;
    t = pq->head->next;
    free(pq->head);
    pq->head = t;
    return tmp;
}

void PQchange (PQ pq, Item val) {
    link x, p;
    if (PQempty(pq)) {
        printf("PQ empty\n");
        return; }
    for(x=pq->head, p=NULL; x!=NULL; p=x, x=x->next) {
        if (ITEMeq(x->val, val)){
            if (x==pq->head)
                pq->head = x->next;
            else
                p->next = x->next;
            free(x);
            break;
        }
    }
    PQinsert(pq, val);
    return;
}