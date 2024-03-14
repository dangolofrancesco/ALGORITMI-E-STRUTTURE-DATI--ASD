//
// Created by Francesco D'Angolo on 09/01/23.
//

#include "UF.h"

typedef struct node *link;

struct node{
    int v;
    int wt;
    link next;
};

struct graph{
    int V;
    int E;
    link *ladj;
    int **madj;
    ST tab;
    //nodo sentinella
    link z;
};

//Algoritmo di Kruskal
static int *id, *sz;

void UFinit(int N) {
    int i;
    id  = malloc(N*sizeof(int));
    sz  = malloc(N*sizeof(int));
    for(i=0; i<N; i++) {
        id[i] = i; sz[i] = 1;
    }
}

static int find(int x) {
    int i = x;
    while (i!= id[i]) i = id[i];
    return i;
}
int UFfind(int p, int q) {
    return(find(p) == find(q));
}

void UFunion(int p, int q) {
    int i = find(p), j = find(q);
    if (i == j) return;
    if (sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
    }
    else {
        id[j] = i;
        sz[i] += sz[j];
    }
}

int mstE(Graph G, Edge *mst, Edge *a){
    int i, k;
    GRAPHedges(G, a);
    sort(a, 0, G->E-1); //algoritmo di sorting secondo peso crescente
    UFinit(G->V);
    for (i=0, k=0; i<G->E && k<G->V-1; i++)
        if (!UFfind(a[i].v, a[i].w)){
            UFunion(a[i].v, a[i].w);
            mst[k++] = a[i];
        }
    return k;
}

void GRAPHmstK(Graph G) {
    int i, k, weight = 0;
    Edge *mst = malloc((G->V-1) * sizeof(Edge));
    Edge *a = malloc(G->E * sizeof(Edge));
    k = mstE(G, mst, a);
    printf("\nEdges in the MST: \n");
    for (i=0; i < k; i++) {
        printf("(%s - %s) \n", STsearchByIndex(G->tab, mst[i].v),
               STsearchByIndex(G->tab, mst[i].w));
        weight += mst[i].wt;
    }
    printf("minimum weight: %d\n", weight);
}

