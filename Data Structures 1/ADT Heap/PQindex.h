//
// Created by Francesco D'Angolo on 17/12/22.
//

#ifndef ADT_HEAP_PQINDEX_H
#define ADT_HEAP_PQINDEX_H

typedef struct pqueue *PQ;

PQ PQinit(int maxN);
void PQfree(PQ pq);
int PQempty(PQ pq);
int PQsize(PQ pq);
void PQinsert(PQ pq, int index, int prio); int PQshowMax(PQ pq);
int PQextractMax(PQ pq);
void PQdisplay(PQ pq);
void PQchange(PQ pq, int index, int prio);

#endif //ADT_HEAP_PQINDEX_H
