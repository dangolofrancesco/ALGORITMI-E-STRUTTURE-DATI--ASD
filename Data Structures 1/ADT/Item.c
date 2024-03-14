//
// Created by Francesco D'Angolo on 27/11/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include <string.h>
#define MAX 30

static char buf[MAX];

//TIPOLOGIA 4: campo name dinamico
struct item{
    char *name;
    int num;
};

//Funzioni comuni a tipologie 3 e 4
Key KEYget(Item val){
    return (val->name);
}

int KEYcompare(Key k1, Key k2){
    return (strcmp(k1,k2));
}

void ITEMshow(Item val){
    printf("%s %d", val->name, val->num);
}

int ITEMless(Item val1, Item val2){
    return (strcmp(KEYget(val1), KEYget(val2))<0);
}


//ITEMnew e ITEMfree per tipologia 4
Item ITEMnew(){
    Item val = (Item) malloc(sizeof (struct item));
    if (val==NULL)
        return ITEMsetvoid();
    val->name = NULL;
    val->num = 0;
    return val;
}

void ITEMfree(Item val){
    if (val->name!=NULL)
        free(val->name);
    free(val);
}

static char buf[MAX];

//versione 2: Riceve Item (puntatore) già creato per riferimento
Item ITEMscan(Item val){
    scanf("%s %d", buf, &val->num);
    val->name = strdup(buf);
}