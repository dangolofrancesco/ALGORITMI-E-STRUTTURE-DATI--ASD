//
// Created by Francesco D'Angolo on 06/01/23.
//

#ifndef E03_DATA_H
#define E03_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//QUASI ADT
typedef struct data_s{
    int anno;
    int mese;
    int giorno;
}data_t;

typedef struct time_s{
    int h;
    int m;
}time_t;

data_t DATAsetNull();
data_t DATAload(char *s);
time_t TIMEload(char *s);
int DATAcmp(data_t d1, data_t d2);
void DATAstore(FILE *fp, data_t data);
void TIMEstore(FILE *fp, time_t time);


#endif //E03_DATA_H
