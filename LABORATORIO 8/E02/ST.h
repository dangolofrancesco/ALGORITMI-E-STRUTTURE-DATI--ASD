//
// Created by Francesco D'Angolo on 02/01/23.
//

#ifndef E02_ST_H
#define E02_ST_H

#include "Item.h"

/*Tabella di simboli come ADT di I classe*/
typedef struct symbtab *ST;

/*creazione e distruzione*/
ST STinit(int maxN);
void STfree(ST st);

/*inserimento e ricerca*/
void STinsert(ST st, Item val);
int STsearch(ST st, KEY k);
int STsearch2(ST st, KEY k);
char *STsearchByIndex(ST st, int index);

/*stampa*/
void STdisplay(FILE *fp, ST st);
void STdisplayByIndex(FILE *fp, ST st, int index);
void STsort(ST st);

int STcount(ST st);

#endif //E02_ST_H
