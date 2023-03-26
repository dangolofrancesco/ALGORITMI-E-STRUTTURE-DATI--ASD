//
// Created by Francesco D'Angolo on 13/01/23.
//

#include "ST.h"

struct symbtble{
    Item *id;
    int N;
    int maxN;
};

ST STinit(int maxN){
    int i;
    ST st = malloc(sizeof *st);
    st->id = malloc(maxN*sizeof (Item));
    if (st->id==NULL)
        return NULL;
    for(i=0; i<maxN; i++)
        st->id[i] = ITEMsetNull();
    st->maxN = maxN;
    st->N = 0;
    return st;
}

int STcount(ST st){
    return st->N;
}

void STfree(ST st){
    int i;
    free(st->id);
    free(st);
}

void STinsert(ST st, char *val){
    int i = st->N;
    st->id[i] = ITEMload(val);
    st->N++;
}

int STsearch(ST st, KEY val){
    int i;
    for (i=0; i<st->N; i++)
        if (KEYcmp(st->id[i].id, val)==0)
            return i;
    return -1;
}

KEY STsearchByIndex(ST st, int i){
    return st->id[i].id;
}

void STdisplayByIndex(ST st, int i){
    printf("%s\n", st->id[i].id);
}

void STdisplay(ST st){
    int i;
    printf("%d\n", st->maxN);
    for (i=0; i<st->N; i++){
        printf("%s\n", st->id[i].id);
    }
}


