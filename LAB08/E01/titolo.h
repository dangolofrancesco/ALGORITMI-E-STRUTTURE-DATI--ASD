//
// Created by Francesco D'Angolo on 06/01/23.
//

#ifndef E03_TITOLO_H
#define E03_TITOLO_H

#include "quotazioni.h"
#define MAXL 20

//ADT I CLASSE
typedef struct titolo_s *titolo_t;
typedef char *KEY;

titolo_t TITOLOIns(KEY key);
BSTquot TITOLOgetBst(titolo_t t);
KEY KEYget(titolo_t t);
int KEYcmp(KEY k1, KEY k2);
void TITOLOstore(FILE *fp, titolo_t t);
float TITOLOgetMax(titolo_t t);
float TITOLOgetMin(titolo_t t);
void BSTmaxMinTot(BSTquot bst, float *max, float *min);

#endif //E03_TITOLO_H
