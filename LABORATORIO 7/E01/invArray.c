//
// Created by Francesco D'Angolo on 14/12/22.
//
#include "invArray.h"

struct invArray_s{
    inv_t *vettInv;
    int nInv;
    int maxInv;
};

invArray_t invArray_init(int maxN){
    invArray_t invArray;
    invArray = (invArray_t) malloc(sizeof (struct invArray_s));
    invArray->vettInv = malloc(maxN*sizeof (inv_t));
    invArray->maxInv = maxN;
    invArray->nInv = 0;
    return invArray;
}

void invArray_read(FILE *fp, invArray_t invArray){
    int i;
    for (i=0; i<invArray->maxInv; i++){
        inv_read(fp, &(invArray->vettInv[i]));
        stat_read(fp, &(invArray->vettInv[i].stat));
    }
    invArray->nInv = i;
}

