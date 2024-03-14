//
// Created by Francesco D'Angolo on 16/12/22.
//

#ifndef ADT_HEAP_PQ_H
#define ADT_HEAP_PQ_H



typedef struct pqueue *PQ;

PQ PQinit(int maxN);
void PQfree(PQ pq);
int PQempty(PQ pq);
void PQinsert(PQ pq, Item val);
Item PQextractMax(PQ pq);
Item PQshowMax(PQ pq);
void PQdisplay(PQ pq);
int PQsize(PQ pq);
void PQchange(PQ pq, Item val);
void HEAPify(PQ pq, int i);

#endif //ADT_HEAP_PQ_H
