//
// Created by Francesco D'Angolo on 09/01/23.
//

#ifndef GRAFO_UF_H
#define GRAFO_UF_H

#include "Graph.h"

typedef struct graph *Graph;

void  UFinit(int N);
int   UFfind(int p, int q);
void  UFunion(int p, int q);

#endif //GRAFO_UF_H
