//
// Created by Francesco D'Angolo on 08/12/22.
//

#ifndef MAIN_C_ST_H
#define MAIN_C_ST_H

#include "Item.h"

typedef struct symboltable *ST;

ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, Item val);
Item STsearch(ST st, Key k);
void STdelete(ST st, Key k);
Item STselect(ST st, int r);
void STdisplay(ST st);
Key STsearchByIndex(ST st, int id);

#endif //MAIN_C_ST_H

