//
// Created by Francesco D'Angolo on 28/11/22.
//

#ifndef ADT_SET_H
#define ADT_SET_H

#include "Item.h"

typedef struct set *SET;

SET SETinit(int maxN);
void SETfree(SET s);
void SETfill(SET s, Item val);
int SETsearch(SET s, Key k);
SET SETunion(SET s1, SET s2);
SET SETintersection(SET s1, SET s2); int SETsize(SET s);
int SETempty(SET s);
void SETdisplay(SET s);

#endif //ADT_SET_H
