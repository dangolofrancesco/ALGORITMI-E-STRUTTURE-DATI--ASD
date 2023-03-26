//
// Created by Francesco D'Angolo on 02/01/23.
//

#include "Graph.h"

typedef struct node *link;

struct node{
    int v;
    int wt;
    link next;
};

struct graph{
    int V;
    int E;
    int **madj;
    link *ladj;
    link z;
};

int **MATRIXinit(int r, int c, int val){
    int i, j;
    int **t = malloc(r*sizeof (int *));
    for (i=0; i<r; i++)
        t[i] = malloc(c*sizeof (int));
    for (i=0; i<r; i++){
        for (j=0; j<c; j++)
            t[i][j] = val;
    }
    return t;
}

link newNode(int v, int wt, link next){
    link x = malloc(sizeof (*x));
    if (x==NULL)
        return NULL;
    x->v=v;
    x->wt=wt;
    x->next=next;
    return x;
}

Graph GRAPHinit(int V){
    int v;
    Graph G = malloc(sizeof (*G));
    if (G==NULL)
        return NULL;
    G->V=V;
    G->E=0;
    G->madj = MATRIXinit(V, V, 0);
    G->z= newNode(-1, -1, NULL);
    G->ladj= malloc(G->V*sizeof (link));
    for (v=0; v<G->V; v++)
        G->ladj[v] = G->z;
    return G;
}


void GRAPHfree(Graph G){
    int i;
    link x, t;
    if (G->ladj!=NULL){
        for (i=0; i<G->V; i++){
            for (x=G->ladj[i]; x!=G->z; x=t){
                t=x->next;
                free(x);
            }
        }
        free(G->ladj);
    }
    if (G->z!=NULL)
        free(G->z);
    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    free(G);
}

Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v=v;
    e.w=w;
    e.wt=wt;
    return e;
}

/*funzioni per matrice di adiacenze*/
void insertE(Graph G, Edge e){
    int v, w, wt;
    v = e.v;
    w = e.w;
    wt = e.wt;
    if (G->madj[v][w]==0)
        G->E++;
    G->madj[v][w] = wt;
    //grafo non orientato e pesato
    G->madj[w][v] = wt;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt){
    insertE(G, EDGEcreate(id1, id2, wt));
}

/*funzione load modificata per il tipo di file in ingresso*/
Graph GRAPHload(FILE *fp, ST st){
    int size, wt, id1, id2;
    char e1[MAXL], e2[MAXL], r1[MAXL], r2[MAXL];
    Graph G;

    /*Inserimento in tabella di simboli i vertici*/
    while (fscanf(fp, "%s %s %s %s %d", e1, r1, e2, r2, &wt)==5) {
        Item x = ITEMload(e1, r1);
        if (STsearch(st, KEYget(&x)) == -1)
            STinsert(st, x);
        x = ITEMload(e2, r2);
        if (STsearch(st, KEYget(&x)) == -1)
            STinsert(st, x);
    }
    STdisplay(stdout, st);

    G = GRAPHinit(STcount(st));
    //doppia lettura del file
    rewind(fp);

    /*Inserimento degli archi nel grafo*/
    while (fscanf(fp, "%s %s %s %s %d", e1, r1, e2, r2, &wt)==5){
        Item x = ITEMload(e1, r1);
        id1 = STsearch(st, KEYget(&x));
        x = ITEMload(e2, r2);
        id2 = STsearch(st, KEYget(&x));
        if (id1!=id2 && id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);
    }

    return G;
}

/*Stampa dei vertici con i relativi archi*/
void GRAPHstore(FILE *fout, Graph G, ST st){
    int i,j;
    for (i=0; i<G->V; i++){
        STdisplayByIndex(fout, st, i);
        printf(":");
        for (j=0; j<G->V; j++){
            if (G->madj[i][j]!=0){
                fprintf(fout, "-->");
                STdisplayByIndex(fout, st, j);
                printf(" ");
            }
        }
        printf("\n");
    }
}

static int adiacentiM(Graph G, int v, int w){
    if (G==NULL)
        return 0;
    if (G->madj==NULL)
        return 0;

    return (G->madj[v][w]>0);
}

int GRAPHcheck3adj(Graph G, int x, int y, int z){
    if (G==NULL)
        return 0;
    if (G->madj==NULL)
        return 0;

    if (adiacentiM(G, x, y)){
        if (adiacentiM(G, x, z)){
            if (adiacentiM(G, y, z))
                return 1;
        }
    }
    return 0;
}

/*Inizializzazione a partire da matrice di adiacenze*/
void LISTinit(Graph G, ST st){
    int v, w;
    G->ladj = realloc(G->ladj, G->V*sizeof (link));
    for (v=0; v<G->V; v++){
        for (w=0; w<G->V; w++){
            if (G->madj[v][w]!=0){
                G->ladj[v] = newNode(w, G->madj[v][w], G->ladj[v]);
            }
        }
    }
}

void LISTdisplay(Graph G, ST st){
    int i;
    link x;
    for (i=0; i<G->V; i++){
        STdisplayByIndex(stdout, st, i);
        for (x=G->ladj[i]; x!=G->z; x=x->next){
            printf("-->");
            STdisplayByIndex(stdout, st, x->v);
        }
        printf("\n");
    }
}