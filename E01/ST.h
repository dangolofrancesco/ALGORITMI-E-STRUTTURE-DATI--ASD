//
// Created by Francesco D'Angolo on 13/01/23.
//

#ifndef E01_ST_H
#define E01_ST_H

#include "Item.h"

typedef struct symbtble *ST;

ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, char *val);
int STsearch(ST st, KEY val);
KEY STsearchByIndex(ST st, int i);
void STdisplay(ST st);
void STdisplayByIndex(ST st, int i);

#endif //E01_ST_H
