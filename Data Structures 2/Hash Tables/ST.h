//
// Created by Francesco D'Angolo on 19/01/23.
//

#ifndef TABELLE_DI_HASH_ST_H
#define TABELLE_DI_HASH_ST_H

#include "Item.h"

typedef struct symboltable *ST;

ST STinit(int maxN, float r);
void STinsert(ST st, Item val);
Item STsearch(ST st, Key k);
void STdelete(ST st, Key k);
void STdisplay(ST st);
void STfree(ST st);
int STcount(ST st);
int STempty(ST st);

#endif //TABELLE_DI_HASH_ST_H
