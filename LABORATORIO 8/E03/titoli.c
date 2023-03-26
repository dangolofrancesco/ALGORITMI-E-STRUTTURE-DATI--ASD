//
// Created by Francesco D'Angolo on 06/01/23.
//

#include "titoli.h"

typedef struct node *link;

struct node{
    titolo_t titolo;
    link next;
};

struct titoli_s{
    link h;
    int n;
};

titoli_t LISTinit(){
    titoli_t x = malloc(sizeof *x);
    x->h=NULL;
    x->n=0;
    return x;
}

link newNode(titolo_t titolo, link next){
    link x = malloc(sizeof *x);
    x->titolo = titolo;
    x->next = next;
    return x;
}

link insSorted(KEY titolo, link h){
    link x, p;
    if (h==NULL || KEYcmp(titolo, KEYget(h->titolo))<0)
        return newNode(TITOLOIns(titolo), h);
    for (x=h->next, p=h; x!=NULL && KEYcmp(titolo, KEYget(x->titolo))>0;p=x,  x=x->next);
    p->next = newNode(TITOLOIns(titolo), x);
    return h;
}

void LISTins(titoli_t lista, KEY titolo){
    lista->h = insSorted(titolo, lista->h);
    lista->n++;
}

titolo_t LISTAgetTitolo(titoli_t lista, KEY titolo){
    link x;
    for (x=lista->h; x!=NULL; x=x->next){
        if (KEYcmp(titolo, KEYget(x->titolo))==0)
            return x->titolo;
    }
    return NULL;
}

void LISTstore(FILE *fp, titoli_t list){
    link x;
    for (x=list->h; x!=NULL; x=x->next)
        TITOLOstore(fp, x->titolo);
}
