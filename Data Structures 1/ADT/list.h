//
// Created by Francesco D'Angolo on 27/11/22.
//

#ifndef ADT_LIST_H
#define ADT_LIST_H

#include "Item.h"

typedef struct list *LIST;

void listInsHead (LIST l, Item val);
Item listSearch(LIST l, Key k);
void listDelKey(LIST l, Key k);


#endif //ADT_LIST_H
