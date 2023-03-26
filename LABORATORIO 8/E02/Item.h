//
// Created by Francesco D'Angolo on 02/01/23.
//

#ifndef E02_ITEM_H
#define E02_ITEM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXL 31

typedef struct{
    char elab[MAXL];
    char rete[MAXL];
}Item;

typedef char *KEY;

Item ITEMload(char *elab, char *rete);
void ITEMstore(FILE *fp, Item val);
Item ITEMsetNull();
KEY KEYget(Item *val);
int KEYcmp(KEY k1, KEY k2);
void KEYscan(KEY v);

#endif //E02_ITEM_H
