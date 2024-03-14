//
// Created by Francesco D'Angolo on 08/12/22.
//

#ifndef MAIN_C_PQ_H
#define MAIN_C_PQ_H
#include "Item.h"

typedef struct pqueue *PQ;

PQ PQinit(int maxN);
int PQempty(PQ pq);
void PQinsert(PQ pq, Item data);
Item PQextractMax(PQ pq);
Item PQshowMax(PQ pq);
void PQdisplay(PQ pq);
void PQchange(PQ pq, Item data);

#endif //MAIN_C_PQ_H
