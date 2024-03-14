//
// Created by Francesco D'Angolo on 02/01/23.
//

#ifndef E02_GRAPH_H
#define E02_GRAPH_H

#include "ST.h"

/*Grafo non orientato e pesato*/
typedef struct edge{
    int v;
    int w;
    int wt;
}Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph G);

void GRAPHinsertE(Graph G, int id1, int id2, int wt);
Graph GRAPHload(FILE *fp, ST st);
void GRAPHstore(FILE *fout, Graph G, ST st);
int GRAPHcheck3adj(Graph G, int x, int y, int z);
void LISTinit(Graph G, ST st);
void LISTdisplay(Graph G, ST st);
#endif //E02_GRAPH_H
