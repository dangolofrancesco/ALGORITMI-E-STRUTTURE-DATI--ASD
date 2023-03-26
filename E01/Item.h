//
// Created by Francesco D'Angolo on 13/01/23.
//

#ifndef E01_ITEM_H
#define E01_ITEM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXL 31

typedef struct{
    char id[MAXL];
}Item;

typedef char *KEY;

Item ITEMload(char *val);
void ITEMstore(Item val);
Item ITEMsetNull();
KEY KEYget(Item *val);
int KEYcmp(KEY k1, KEY k2);
void KEYscan(KEY v);

#endif //E01_ITEM_H
