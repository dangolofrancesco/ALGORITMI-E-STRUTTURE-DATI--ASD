//
// Created by Francesco D'Angolo on 06/01/23.
//

#ifndef E03_QUOTAZIONI_H
#define E03_QUOTAZIONI_H

#include "quotazione.h"

typedef struct BSTquot_s *BSTquot;

BSTquot BSTinit();
int BSTcount(BSTquot bst);
int BSTempty(BSTquot bst);
void BSTinsertLeaf(data_t data, float val, int qta, BSTquot bst);
quotazione_t BSTsearch(BSTquot bst, data_t data);
void BSTvisit(FILE *fp, BSTquot bst);

void BSTmaxmin(BSTquot bst, data_t d1, data_t d2, float *max, float *min);

#endif //E03_QUOTAZIONI_H
