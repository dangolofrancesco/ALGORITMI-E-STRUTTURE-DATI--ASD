//
// Created by Francesco D'Angolo on 27/12/22.
//

#ifndef GRAFO_GRAPH_H
#define GRAFO_GRAPH_H

#include <stdlib.h>
#include "ST.h"
#include "stdio.h"

#include "queue.h"
#include "PQ.h"
#include "Graph.h"
#define MAXC 100

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
void GRAPHload(FILE *fin);
void GRAPHstore(Graph G, FILE *fout);
int GRAPHgetIndex(Graph G, char *label);
void GRAPHinsertE(Graph G, int id1, int id2; int wt; );
void GRAPHremoveE(Graph G, int id1, int id2);
void GRAPHedges(Graph G, Edge *a);
int GRAPHpath(Graph G, int id1, int id2);
void GRAPHpathH(Graph G, int id1, int id2);
void GRAPHbfs(Graph G, int id);
void GRAPHdfs(Graph G, int id);
int GRAPHcc(Graph G);
int GRAPHscc(Graph G);

#endif //GRAFO_GRAPH_H
