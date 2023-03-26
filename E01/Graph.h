//
// Created by Francesco D'Angolo on 13/01/23.
//

#ifndef E01_GRAPH_H
#define E01_GRAPH_H

#include "ST.h"

typedef struct edge{
    int v;
    int w;
    int wt;
}Edge;

typedef struct graph_s *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
void GRAPHinsertE(Graph G, int v, int w, int wt);
Graph GRAPHload(FILE *fp);
void GRAPHstore(Graph G);
Edge EDGEcreate(int v, int w, int wt);
void EDGEstore(Graph G, Edge a);
void GRAPHedges(Graph G, Edge *a);
int EDGEsumWt(Edge *e, int *id, int k);
void GRAPHdfs(Graph G, int *isAcyclic);
int GRAPHgetV(Graph G);
int GRAPHgetE(Graph G);
ST GRAPHgetSt(Graph G);
void GRAPHremoveE(Graph G, Edge e);
void GRAPHreset(Graph G, Edge *e, int *id, int k);
int *DAGts(Graph D);
void DAGmaxpathD(Graph D, int id, int *ts);
int *GRAPHsources(Graph G);
#endif //E01_GRAPH_H
