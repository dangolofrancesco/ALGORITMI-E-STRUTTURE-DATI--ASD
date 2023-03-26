#include "Graph.h"


void comb_semp(Graph G, int pos, int *sol, Edge *edges, int n, int k, int start, int *stop, int *bsol, int *bWt){
    int v, isAcyclic=1, solWt;
    if (pos>=k){
        for (v=0; v<k; v++){
            GRAPHremoveE(G, edges[sol[v]]);
        }
        solWt = EDGEsumWt(edges, sol, k);
        GRAPHdfs(G, &isAcyclic);

        if (isAcyclic){
            *stop = 1;
            if (solWt > *bWt){
                *bWt = solWt;
                for (v=0; v<k; v++)
                    bsol[v] = sol[v];
            }
        }
        GRAPHreset(G, edges, sol, k);
        return;
    }
    for (v=start; v<n; v++){
        sol[pos] = v;
        comb_semp(G, pos+1, sol, edges, n, k, v+1, stop, bsol, bWt);
    }
}

void DAGcreate(Graph G){
    int i, j, stop=0, bWt=0;
    int *sol, *bSol;
    int a=1;
    int V = GRAPHgetV(G), E = GRAPHgetE(G);
    int limit = E-(V-1);
    if (limit<=0){
        printf("Non ci sono archi da eliminare");
	GRAPHdfs(G, &a);
        if (a==1)
            printf("Il Grafo è già un DAG\n");
        return;
    }
    Edge *edges = malloc(E*sizeof (Edge));
    GRAPHedges(G, edges);
    bSol = malloc(E*sizeof (int ));

    for (i=1; i<=limit && !stop; i++){
        sol = malloc(i*sizeof (int));
        comb_semp(G, 0, sol, edges, E, i, 0, &stop, bSol, &bWt);
    }

    printf("Archi rimossi %d:\n", i-1);
    for (j=0; j<i-1; j++){
        EDGEstore(G, edges[bSol[j]]);
        //rimozione archi dal grafo
        GRAPHremoveE(G, edges[bSol[j]]);
    }
}



int main() {
    FILE *fp = fopen("../grafo4.txt", "r");
    Graph G;
    int a=1, *ts;
    int v=0, *sources;

    G = GRAPHload(fp);
    GRAPHdfs(G, &a);
    DAGcreate(G);

    printf("\nDAG:\n");
    GRAPHstore(G);
    ts = DAGts(G);

    sources = GRAPHsources(G);
    while (sources[v]!=-1){
        printf("\nSorgente: %s", STsearchByIndex(GRAPHgetSt(G), sources[v]));
        DAGmaxpathD(G, sources[v], ts);
        v++;
    }
}

