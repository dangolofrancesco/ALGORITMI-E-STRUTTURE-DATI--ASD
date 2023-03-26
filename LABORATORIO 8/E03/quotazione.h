//
// Created by Francesco D'Angolo on 06/01/23.
//

#ifndef E03_QUOTAZIONE_H
#define E03_QUOTAZIONE_H

#include "data.h"

typedef struct quotazione_s{
    data_t data;
    float num;
    int den;
}quotazione_t;

quotazione_t QUOTsetNull();
int QUOTcheckNull(quotazione_t q);
void QUOTinsert(quotazione_t *q, float val, int qta);
float media(quotazione_t q);
void QUOTstore(FILE *fp, quotazione_t q);
data_t QUOTgetData(quotazione_t q);
float QUOTgetVal(quotazione_t q);

#endif //E03_QUOTAZIONE_H
