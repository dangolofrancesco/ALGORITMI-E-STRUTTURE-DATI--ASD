//
// Created by Francesco D'Angolo on 07/12/22.
//

#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

typedef struct{

}Item;

/*quasi ADT
static Item *s;
static int N;

void STACKinit(int maxN){
    s = malloc(maxN*sizeof (Item));
    N=0;
}

int STACKempty(){
    return N==0;
}

void STACKpush(Item val){
    s[N++] = val;
}

Item STACKpop(){
    //estrazione dell'ultimo inserito LIFO
    return s[--N];
}*/

struct stack {
    //vettore di Item
    Item *s;
    int N;
};

/*STACK STACKinit(int maxN) {
    STACK sp = malloc(sizeof *sp) ;
    sp->s = malloc(maxN*sizeof(Item));
    sp->N=0;
    return sp;
}

int STACKempty(STACK sp) {
    return sp->N == 0;
}

void STACKpush(STACK sp, Item val) {
    //Inserisco elemento in fondo al vettore
    sp->s[sp->N++] = val;
}

Item STACKpop(STACK sp) {
    //Politica di estrazione LIFO
    return sp->s[--(sp->N)];
}*/

/*typedef struct STACKnode* link;

struct STACKnode {
    Item val;
    link next;
};

static link head;
static int N;

//funzione newNode
static link NEW (Item val, link next){
    link x = (link) malloc(sizeof *x);
    x->val = val; x->next = next;
    return x;
}

void STACKinit(int maxN) {
    head = NULL;
}

int STACKempty() {
    return head == NULL;

} void STACKpush(Item val) {
    head = NEW(val, head);
}

Item STACKpop() {
    Item tmp;
    tmp = head->val;
    link t = head->next;
    free(head);
    head = t;
    return tmp;
}*/

typedef struct STACKnode* link;
struct STACKnode {
    Item val;
    link next;
};

struct stack {
    link head;
    int N;
};

static link NEW (Item val, link next){
    link x = (link) malloc(sizeof *x);
    x->val = val;
    x->next = next;
    return x;
}

STACK STACKinit(int maxN) {
    STACK s = malloc(sizeof *s) ;
    s->head = NULL;
    return s;
}

int STACKempty(STACK s) {
    return s->head == NULL;
}

void STACKpush(STACK s, Item val) {
    s->head = NEW(val, s->head);
}

Item STACKpop (STACK s) {
    Item tmp;
    tmp = s->head->val;
    link t = s->head->next;
    free(s->head);
    s->head = t;
    return tmp;
}