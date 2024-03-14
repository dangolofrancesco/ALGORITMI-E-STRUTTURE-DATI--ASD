//
// Created by Francesco D'Angolo on 06/01/23.
//

#include "quotazione.h"

quotazione_t QUOTsetNull(){
    quotazione_t quot;
    quot.data = DATAsetNull();
    quot.num = 0;
    quot.den = 0;
    return quot;
}

int QUOTcheckNull(quotazione_t q){
    return (q.den==0);
}

void QUOTinsert(quotazione_t *q, float val, int qta){
    q->num += val*((float) qta);
    q->den += qta;
}

float media(quotazione_t q){
    return (q.num/((float) q.den));
}

void QUOTstore(FILE *fp, quotazione_t q){
    if (q.den!=0){
        DATAstore(fp, q.data);
        fprintf(fp, " %.2f\n", media(q));
    }
}

data_t QUOTgetData(quotazione_t q){
    if (QUOTcheckNull(q))
        return DATAsetNull();
    return q.data;
}

float QUOTgetVal(quotazione_t q){
    if (q.den!=0)
        return media(q);
    return -1;
}