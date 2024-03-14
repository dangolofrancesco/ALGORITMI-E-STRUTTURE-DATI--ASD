//
// Created by Francesco D'Angolo on 06/01/23.
//

#include "data.h"

data_t DATAsetNull(){
    data_t data;
    data.anno=0;
    data.mese=0;
    data.giorno=0;
    return data;
}

data_t DATAload(char *s){
    data_t data;
    sscanf(s, "%d/%d/%d", &data.anno, &data.mese, &data.giorno);
    return data;
}

time_t TIMEload(char *s){
    time_t time;
    sscanf(s, "%d:%d", &time.h, &time.m);
    return time;
}

int DATAcmp(data_t d1, data_t d2){
    if (d1.anno != d2.anno)
        return (d1.anno-d2.anno);
    if (d1.mese != d2.mese)
        return (d1.mese - d2.mese);
    if (d1.giorno != d2.giorno)
        return (d1.giorno-d2.giorno);
    return 0;
}

void DATAstore(FILE *fp, data_t data){
    fprintf(fp, "%d/%d/%d\n", data.anno, data.mese, data.giorno);
}

void TIMEstore(FILE *fp, time_t time){
    fprintf(fp, " %d:%d ", time.h, time.m);
}

