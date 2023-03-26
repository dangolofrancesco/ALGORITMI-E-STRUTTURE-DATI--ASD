//
// Created by Francesco D'Angolo on 25/11/22.
//

#ifndef E03_PERSONAGGI_H
#define E03_PERSONAGGI_H

#include <stdio.h>
#include "inventario.h"

#define MAX 50
#define MAXEQ 8

typedef struct nodoPg_t *linkPg, personaggio_t;

typedef struct {
    int inUso;
    inv_t *vettEq[MAXEQ];
}tabEq_t;

//per ogni personaggio
typedef struct{
    char *codice;
    char *nome;
    char *classe;
    tabEq_t equip;
    stat_t stat;
}pg_t;

struct nodoPg_t{
    //campo val
    pg_t campi;
    linkPg next;
};

typedef struct {
    linkPg head;
    linkPg tail;
    int nPg;
}tabPg_t;

tabPg_t *allocaPg();
void liberaPg(tabPg_t *pg);
int insertPg(char *nomeFile, tabPg_t *tabPg);
void deletePg(tabPg_t *tabPg);
linkPg ricerca(tabPg_t *tabPg, char *codice);
void aggiungiEq(tabPg_t *tabPg, tabInv_t *tabInv);
void rimuoviEq(tabPg_t *tabPg, tabInv_t *tabInv);
void calcolaStat(linkPg pg);
void stampaPg(linkPg pg);
void stampaEq(tabInv_t *tabInv, linkPg x);

#endif //E03_PERSONAGGI_H
