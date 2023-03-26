 //
// Created by Francesco D'Angolo on 13/01/23.
//

#include "Graph.h"

struct graph_s{
    int V;
    int E;
    int **madj;
    ST st;
};

int **MATRIXinit(int r, int c, int val){
    int i, **madj;
    madj = malloc(r*sizeof (int*));
    if (madj==NULL)
        return NULL;
    for (i=0; i<r; i++)
        madj[i] = malloc(c*sizeof (int ));
    return madj;
}

Graph GRAPHinit(int V){
    Graph G;
    G = malloc(sizeof *G);
    if (G==NULL)
        return NULL;
    G->madj = MATRIXinit(V, V, -1);
    G->st = STinit(V);
    G->V = V;
    G->E = 0;
    return G;
}

void GRAPHfree(Graph G){
    int i;
    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->st);
    free(G);
}

void GRAPHinsertE(Graph G, int v, int w, int wt){
    //GRAFO ORIENTATO
    if (G->madj[v][w]==0)
        G->E++;
    G->madj[v][w] = wt;
}

Graph GRAPHload(FILE *fp){
    int i, v, id1, id2, wt;
    char label1[MAXL], label2[MAXL];
    Graph G;
    fscanf(fp, "%d", &v);
    G = GRAPHinit(v);

    for (i=0; i<v; i++){
        fscanf(fp, "%s ", label1);
        STinsert(G->st, label1);

    }

    while (fscanf(fp, "%s %s %d", label1, label2, &wt)==3){
        id1 = STsearch(G->st, label1);
        id2 = STsearch(G->st, label2);
        if (id1>=0 && id2>=0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

void GRAPHedges(Graph G, Edge *a){
    int v, w, E=0;
    for (v=0; v<G->V; v++)
        for (w=0; w<G->V; w++)
            if (G->madj[v][w]>0){
                a[E++] = EDGEcreate(v, w, G->madj[v][w]);
            }
}

void EDGEstore(Graph G, Edge a){
    printf("%s %s %d\n", STsearchByIndex(G->st, a.v),
           STsearchByIndex(G->st, a.w), a.wt);
}

void GRAPHstore(Graph G){
    int i;
    Edge *a = malloc(G->E*sizeof (Edge));
    GRAPHedges(G, a);

    printf("Numero di vertici: %d\n", G->V);
    for (i=0; i<G->V; i++)
        printf("%s\n", STsearchByIndex(G->st, i));

    printf("Numero di archi: %d\n", G->E);
    for (i=0; i<G->E; i++)
        EDGEstore(G, a[i]);
}

void GRAPHreset(Graph G, Edge *e, int *id, int k){
    int v;
    for (v=0; v<k; v++){
        G->madj[e[id[v]].v][e[id[v]].w] =  e[id[v]].wt;
        G->E++;
    }
}

void GRAPHremoveE(Graph G, Edge e){
    int v=e.v, w=e.w;
    if (G->madj[v][w]>0)
        G->E--;
    G->madj[v][w] = 0;
}

int EDGEsumWt(Edge *e, int *id, int k){
    int i, wt=0;
    for (i=0; i<k; i++){
        wt += e[id[i]].wt;
    }
    return wt;
}

int GRAPHgetV(Graph G){
    return G->V;
}

int GRAPHgetE(Graph G){
    return G->E;
}

/*void dfsR(Graph G, int v, int *pre, int *post, int *time, int *isAcyclic) {
    int w;
    pre[v] = (*time)++;
    for (w = 0; w < G->V; w++)
        if (G->madj[v][w] > 0) {
            if (pre[w] == -1) {
                dfsR(G, w, pre, post, time, isAcyclic);
            } else if (post[w] == -1) {
                printf("L'arco %s %s è B\n", STsearchByIndex(G->st, v), STsearchByIndex(G->st, w));
                *isAcyclic = 0;
            }
        }
    post[v] = (*time)++;
}*/

void dfsR(Graph G, Edge e, int *pre, int *post, int *time, int *isAcyclic){
    int i;
    int w;
    w=e.w;
    pre[w] = (*time)++;
    //dfs con matrice
    for (i=0; i<G->V; i++){
        if (G->madj[w][i]>0){
            if (pre[i]==-1)
                dfsR(G, EDGEcreate(w, i, 0), pre, post, time, isAcyclic);
            else{
                if (post[i]==-1){
                    *isAcyclic = 0;
                }

            }
        }
    }
    post[w] = (*time)++;
}

void GRAPHdfs(Graph G, int *isAcyclic){
    int *pre, *post, v, time = 0;
    if (G == NULL)
        return;
    if (G->madj == NULL)
        return;
    pre = malloc(G->V*sizeof(int));
    post = malloc(G->V*sizeof(int));

    for(v=0;v<G->V;v++){
        pre[v] = -1;
        post[v] = -1;
    }

    for(v=0;v<G->V;v++)
        if (pre[v] == -1)
            //dfsR(G, v, pre, post, &time, isAcyclic);
            dfsR(G, EDGEcreate(v, v, 0), pre, post, &time, isAcyclic);

}

//calcolo distanze massime di un DAG

//ORDINAMENTO TOPOLOGICO DEL DAG
void TSdfs(Graph D, int v, int *pre, int *ts, int *time){
    int w;
    pre[v]=0;
    for (w=0; w<D->V; w++){
        if (D->madj[w][v]>0)
            if (pre[w]==-1)
                TSdfs(D, w, pre, ts, time);
    }
    ts[(*time)++] = v;
}

int *DAGts(Graph D){
    int v, *pre, *ts, time=0;
    pre = malloc(D->V*sizeof (int));
    ts = malloc(D->V*sizeof (int));

    for (v=0; v<D->V; v++){
        pre[v]=-1;
        ts[v]=-1;
    }

    for (v=0; v<D->V; v++){
        if (pre[v]==-1)
            TSdfs(D, v, pre, ts, &time);
    }
    printf("\nOrdinamento topologico del DAG:\n");
    for (v=0; v<D->V; v++){
        printf("%s ", STsearchByIndex(D->st,ts[v] ));
    }
    printf("\n");
    return ts;
}

//ALGORITMO DI DJIKSTRA PER DAG
void DAGmaxpathD(Graph D, int id, int *ts){
    int v, w, s=0;
    int *st, *d;
    Edge e;

    st = malloc(D->V*sizeof (int ));
    d = malloc(D->V*sizeof (int ));

    for (v=0; v<D->V; v++){
        st[v]=-1;
        d[v]=-1;
    }
    d[id] = 0;
    st[id] = id;

    for (v=0; v<D->V; v++){
        for (w=0; w<D->V; w++){
            if (D->madj[v][w]>0)
                if (d[w]<d[v] + D->madj[v][w]){
                    d[w] = d[v] + D->madj[v][w];
                    st[w] = v;
                }
        }
    }
    printf("\nDistanze massime da ogni vertice del DAG:\n");
    for (v=0; v<D->V; v++){
        if (d[v]!=0)
            printf("     --> %s [%d]\n", STsearchByIndex(D->st, v), d[v]);
    }
}

int *GRAPHsources(Graph G){
    int v, w, i=0, *sources, stop=0;
    sources = malloc(G->V*sizeof (int ));
    for (v=0; v<G->V; v++)
        sources[v]=-1;
    for (v=0; v<G->V; v++){
        for (w=0; w<G->V; w++){
            if (G->madj[w][v]>0)
                stop=1;
        }
        if (!stop)
            sources[i++] = v;
    }
    return sources;
}

ST GRAPHgetSt(Graph G){
    return G->st;
}