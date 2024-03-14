//
// Created by Francesco D'Angolo on 06/01/23.
//

#include "titolo.h"

struct titolo_s{
    KEY cod;
    float max, min;
    BSTquot bst;
};

titolo_t TITOLOIns(KEY key){
    titolo_t t= malloc(sizeof *t);
    t->cod = strdup(key);
    t->max=0;
    t->min=0;
    t->bst = BSTinit();
    return t;
}

BSTquot TITOLOgetBst(titolo_t t){
    return t->bst;
}

KEY KEYget(titolo_t t){
    return t->cod;
}

void TITOLOstore(FILE *fp, titolo_t t){
    fprintf(fp, "%s\n", t->cod);
    BSTvisit(fp, t->bst);
}

int KEYcmp(KEY k1, KEY k2){
    return strcmp(k1, k2);
}

float TITOLOgetMax(titolo_t t){
    return t->max;
}

float TITOLOgetMin(titolo_t t){
    return t->min;
}
