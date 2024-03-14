//
// Created by Francesco D'Angolo on 19/01/23.
//

#include "OpenAddressing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*struct symboltable {
    Item *a;
    int N;
    int M;
};

static int STsizeSet(int maxN, float alpha) {
    int primes[16]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
    int i = 0;
    if (maxN < primes[15]*alpha) {
        for (i = 0; i<16; i++)
            if (maxN <= primes[i]*alpha)
                return primes[i];
    }
    else
        printf("Too many entries!\n");
    return -1;
}

ST STinit(int maxN, float alpha) {
    int i;
    ST st = malloc(sizeof(*st));
    st->N = 0;
    st->M = STsizeSet(maxN, alpha);
    if (st->M == -1)
        st = NULL; else {
        st->a = malloc(st->M * sizeof(Item) ); for (i = 0; i < st->M; i++)
            st->a[i] = ITEMsetNull();
    }
    return st;
}

//funzioni di Hash per le stringhe
static int hash(Key v, int M) {
    int h = 0, base = 127;
    for ( ; *v != '\0'; v++)
        h = (base * h + *v) % M;
    return h;
}

int full(ST st, int i) {
    if (ITEMcheckNull(st->a[i]))
        return 0;
    return 1;
}
void STinsert(ST st, Item item) {
    int i = hash(KEYget(&item), st->M);
    while (full(st, i))
        i = (i+1)%st->M; //normalizzazione
    st->a[i] = item;
    st->N++;
}

Item STsearch(ST st, Key k) {
    int i = hash(k, st->M);
    while (full(st, i))
        if (KEYcmp(k, KEYget(&st->a[i]))==0)
            return st->a[i];
        else
            i = (i+1)%st->M;
    return ITEMsetNull();
}*/


struct symboltable {
    Item *a;
    int *status;
    int N;
    int M;
};

static int CheckFull(ST st, int i);
static int CheckDeleted(ST st, int i);

static int CheckFull(ST st, int i) {
    if (st->status[i] == 1)
        return 1;
    return 0;
}

static int CheckDeleted(ST st, int i){
    if (st->status[i] == -1)
        return 1;
    return 0;
}

void STinsert(ST st, Item item) {
    int i = hash(KEYget(&item), st->M);
    while (CheckFull(st, i))
        i = (i+1)%st->M;
    t->a[i] = item;
    st->status[i] = 1;
    st->N++;
}

Item STsearch(ST st, Key k) {
    int i = hash(k, st->M);
    while (CheckFull(st, i)==1 || CheckDeleted(st, i)==1)
        if (KEYcmp(k, KEYget(&st->a[i]))==0)
            return st->a[i];
        else
            i = (i+1)%st->M;
    return ITEMsetNull();
}

void STdelete(ST st, Key k){
    int i = hash(k, st->M);
    while (CheckFull(st, i)==1 || CheckDeleted(st, i)==1)
        if (KEYcmp(k, KEYget(&st->a[i]))==0)
            break;
        else
            i = (i+1) % st->M;
    if (ITEMcheckNull(st->a[i]))
        return;
    st->a[i] = ITEMsetNull();
    st->N--;
    st->status[i]=-1;
}

void STdelete2(ST st, Key k) {
    int j, i = hash(k, st->M); Item tmp;
    while (full(st, i))
        if (KEYcmp(k, KEYget(&st->a[i]))==0)
            break;
        else
            i = (i+1) % st->M;
    if (ITEMcheckNull(st->a[i]))
        return;
    st->a[i] = ITEMsetNull();
    st->N--;
    for (j = i+1; full(st, j); j = (j+1)%st->M, st->N--) {
        tmp = st->a[j];
        st->a[j] = ITEMsetNull(); STinsert(st, tmp);
    }
}