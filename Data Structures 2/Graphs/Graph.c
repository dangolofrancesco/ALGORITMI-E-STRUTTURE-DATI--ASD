//
// Created by Francesco D'Angolo on 27/12/22.
//

#include "Graph.h"



void GRAPHload(FILE *fin){
    int v, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;
    fscanf(fin, "%d", &v);
    G == GRAPHinit(v);

    for (i=0; i<V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }

    while(fscanf(fin,"%s %s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

void GRAPHstore(Graph G, FILE *fout) {
    int i;
    Edge *a;

    a = malloc(G->E * sizeof(Edge));

    GRAPHedges(G, a);

    fprintf(fout, "%d\n", G->V);
    for (i = 0; i < G->V; i++)
        fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));
    for (i = 0; i < G->E; i++)
        fprintf(fout, "%s  %s %d\n",
                STsearchByIndex(G->tab, a[i].v),
                STsearchByIndex(G->tab, a[i].w), a[i].wt);
}

//INSERZIONE E RIMOZIONE DI ARCHI
void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}
void GRAPHremoveE(Graph G, int id1, int id2) {
    removeE(G, EDGEcreate(id1, id2, 0));
}

static Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v=v;
    e.w=w;
    e.wt=wt;
    return e;
}


//MATRICE DI ADIACENZE
/*struct graph{
    int V;
    int E;
    int **madj;

    ST tab;
};*/

/*
//val è il valore d'inizializzazione
static int **MATRIXinit(int r, int c, int val){
    int i, j;
    int **t = malloc(r*sizeof (int *));
    for (i=0; i<r, i++)
        t[i] = malloc(c*sizeof(int ));
    for (i=0; i<r; i++)
        for (j=0; j<c; j++)
            t[i][j] = val;
    return t;
}

static Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v=v;
    e.w=w;
    e.wt=wt;
    return e;
}

Graph GRAPHinit(int V){
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, 0);
    G->tab = STinit(V);
    return G;
}

void GRAPHfree(Graph G) {
    int i;
    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}

//Inserisco arco in matrice
static void  insertE(Graph G, Edge e) {
    //Decomponiamo l'arco nei suoi vertici
    int v = e.v, w = e.w, wt =e.wt;
    //Verifico l'esistenza dell'arco
    //Per non generare eventuali multigrafi
    //SI possono generare cappi
    if (G->madj[v][w] == 0)
        G->E++;
    G->madj[v][w] = 1; grafi pesati-> G->madj[v][w] = wt;
    //Grafi non orientati
    G->madj[w][v] = 1; grafi pesati->G->madj[w][v] = wt;
}

//Dato un vertice per nome, ricavo l'indice
int GRAPHgetIndex(Graph G, char *label) {
    int id;
    id = STsearch(G->tab, label);
    //Se il vertice cercato non esiste,
    //lo inserisco nella ST
    if (id == -1) {
        id = STcount(G->tab);
        STinsert(G->tab, label, id);
    }
    return id;
}

static void  removeE(Graph G, Edge e, int val) {
    int v = e.v, w = e.w;
    if (G->madj[v][w] != 0)
        G->E--;
    G->madj[v][w] = val;
    //Per grafi non orientati
    G->madj[w][v] = val;
}

//Elenco di tutti gli archi del grafo
void  GRAPHedges(Graph G, Edge *a) {
    int v, w, E = 0;
    for (v=0; v < G->V; v++)
        //Grafi non orientati
        //Leggo solo una delle due
        //matrici triangolari
        for (w=v+1; w < G->V; w++)
        //Per grafi orientati
        //Leggo tutta la matrice
        for (w=0; w < G->V; w++)
                if (G->madj[v][w] !=0)
                    a[E++] = EDGEcreate(v, w, G->madj[v][w]);
    return;
}*/

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

//inserimento in testa alla lista
static link NEW(int v, int wt, link next){
    link x= malloc(sizeof *x);
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

static Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v= v;
    e.w = w;
    e.wt = wt;
    return e;
}

Graph GRAPHinit(int V){
    int v;
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->z = NEW(-1, -1, NULL);
    G->ladj = malloc(G->V*sizeof (link));
    for (v=0; v<G->V; v++)
        G->ladj[v] = G->z;
    G->tab = STinit(V);
    return G;
}

void GRAPHfree(Graph G){
    int v;
    link t, next;
    for (v=0; v<G->V; v++){
        for (t=G->ladj[v]; t!=G->z; t=next){
            next = t->next;
            free(t);
        }
    }
    STfree(G->tab);
    free(G->ladj);
    free(G->z);
    free(G);
}

void GRAPHedges(Graph G, Edge *a){
    int v, E=0;
    link t;
    for (v=0; v<G->V; v++){
        for (t=G->ladj[v]; t!=G->z; t=t->next){
            /*if (v<t->v) nei grafi non orientati*/
            a[E++] = EDGEcreate(v, t->v, t->wt);
        }
    }
}

//inserimento arco nella lista di adiacenze
//nessun controllo su cappi
static void insertE(Graph G, Edge e){
    int v=e.v, w=e.w, wt=e.wt;
    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    //Grafo non orientato
    G->ladj[w] = NEW(v, wt, G->ladj[v]);
    G->E++;
}

static void removeE(Graph G, Edge e){
    int v=e.v, w=e.w;
    link x, p;
    for (x=G->ladj[v], p=NULL; x!=G->z; p=x, x=x->next){
        if (x->v==w){
            if (x==G->ladj[v])
                G->ladj[v] = x->next;
            else{
                p->next = x->next;
            }
            break;
        }
    }
    //per grafi non orientati ripetere
    //l'operazione partendo da w
    G->E--;
    free(x);
}

//--------------------- Generazione di Grafi -------------------//

int randV(Graph G){
    return G->V*(rand()/(RAND_MAX + 1.0));
}

//tecnica 1: archi casuali
Graph GRAPHrand1(Graph G, int V, int E) {
    while (G->E < E)
        GRAPHinsertE(G, randV(G), randV(G));
    return G;
}

//tecnica 2: archi con probabilità
Graph GRAPHrand2(Graph G, int V, int E) {
    int i, j;
    double p = 2.0 * E / (V * (V-1));
    for (i = 0; i < V; i++)
        for (j = i+1; j < V; j++)
            if (rand() < p * RAND_MAX)
                GRAPHinsertE(G, i, j);
    return G;
}

//------------------- CAMMINO SEMPLICE E DI HAMILTON ----------------------//

static int pathR(Graph G, int v, int w, int *visited){
    int t;
    if (v==w)
        return 1;

    //scandisco matrice delle adiacenze
    for (t=0; t<G->V; t++){
        if (G->madj[v][t]==1)
            if (visited[t]==0)
                if (pathR(G, t, w, visited)){
                    //STsearchByIndex
                    //stampa cammini in ordine inverso
                    printf("(%s %s) in path\n", STsearch(G->tab, v), STsearch(G->tab, t));
                    return 1;
                }
    }
    return 0;

    //con lista di adiacenze
    link x;
    for (x=G->ladj[v]; x!=NULL; x=x->next)
        if (visited[x]==0)
            if (pathR(G, x->v, w, visited)){
                //STsearchByIndex
                //stampa cammini in ordine inverso
                printf("(%s %s) in path\n", STsearch(G->tab, v), STsearch(G->tab, t));
                return 1;
            }
    return 0;
}


static int pathRH(Graph G, int v, int w, int d, int *visited) {
    //d = intero che indica quanto manca ad un cammino lungo |V|-1
    int t;
    if (v == w) {
        if (d == 0)
            return 1;
        else
            return 0;
    }

    visited[v] = 1;
    for (t = 0 ; t < G->V ; t++)
        if (G->madj[v][t] == 1)
            if (visited[t] == 0)
                if (pathRH(G, t, w, d-1, visited)) {
                    printf("(%s, %s) in path \n",STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, t));
                    return 1;
                }
    visited[v] = 0;
    return 0;
}

void GRAPHpathHorGRAPHpath(Graph G, int id1, int id2){
    int t, found, *visited;

    visited = malloc(G->V*sizeof (int ));
    for (t=0; t<G->V; t++)
        visited[t] = 0;

    if (id1<0 || id2<0)
        return;
    found = pathRH(G, id1, id2, G->V-1, visited);
    if (found==0)
        printf("\n Path not found!\n");
}

//------------------- ALGORITMI DI VISITA -----------------------------


static void simpleDfsR(Graph G, Edge e, int *cnt, int *pre){
    link t;
    int w=e.w;
    pre[w] = (*cnt)++;
    for (t=G->ladj[v]; t!=G->z; t=t->next)
        if (pre[t->v]==-1)
            simpleDfsR(G, EDGEcreate(w, t->v, 0), cnt, pre);
}
void GRAPHsimpleDfs(Graph G, int id){
    int v, cnt=0, *pre;
    pre = malloc(G->V*sizeof (int));
    if (pre==NULL)
        return;
    for (v=0; v<G->V; v++)
        pre[v]=-1;

    simpleDfsR(G, EDGEcreate(id, id, 0), &cnt, pre);

    for (v=0; v<G->V; v++)
        if (pre[v]==-1)
            simpleDfsR(G, EDGEcreate(v, v, 0), &cnt, pre);

    printf("Tabella tempi di scoperta \n");
    for (v=0; v<G->V; v++)
        printf("vertice %s : %d \n", STsearchByIndex(G->tab, v), pre[v]);
}

static void ExdendeDfsR(Graph G, Edge e, int *time, int *pre, int *post, *st){
    link t;
    int w = e.w;
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t=G->ladj[w]; t!=G->z; t=t->next)
        if (pre[t->v]==-1)
            ExdendeDfsR(G, EDGEcreate(w, t->v, 0), time, pre, post, st);
    post[w] = (*time)++;
}

void GRAPHextendedDfs(Graph G, int id){
    int v, time=0, *pre, *post, *st;
    pre = malloc(G->V*sizeof (int ));
    post = malloc(G->V*sizeof (int));
    st = malloc(G->V*sizeof (int));

    for (v=0; v<G->V; v++){
        pre[v] = post[v] = st[v] = -1;
    }

    ExdendeDfsR(G, EDGEcreate(id, id, 0), &time, pre, post, st);
    for (v=0; v<G->V; v++){
        if (pre[v]==-1)
            ExdendeDfsR(G, EDGEcreate(v, v, 0), &time, pre, post, st);
    }
    printf("discovery/endprocessing time labels \n");
    for (v=0; v < G->V; v++)
        printf("%s:%d/%d\n",STsearchByIndex(G->tab,v),pre[v],post[v]);
    printf("resulting DFS tree \n");
    for (v=0; v < G->V; v++)
        printf("%s’s parent: %s \n",STsearchByIndex (G->tab, v),
               STsearchByIndex (G->tab, st[v]));
}

void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st){
    link t;
    int v, w = e.w;
    Edge x;
    //escludiamo arco fittizio
    if (e.v != e.w)
        //arco di tipo T
    printf("(%s, %s):  T \n",STsearchByIndex(G->tab, e.v),STsearchByIndex(G->tab, e.w));
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            dfsR(G, EDGEcreate(w, t->v), time, pre, post, st);
        else {
            v = t->v;
            x = EDGEcreate(w, v);
            //grafi non orientati
            if (pre[w] < pre[v])
                printf("(%s, %s): B\n", STsearchByIndex(G->tab, x.v),
                       STsearchByIndex(G->tab,x.w)) ;
            //grafi orientati
            if (post[v] == -1)
                printf("(%s, %s): B\n", STsearchByIndex(G->tab, x.v),
                       STsearchByIndex(G->tab, x.w));
            else
            if (pre[v] > pre[w])
                printf("(%s,%s):F\n",STsearchByIndex(G->tab, x.v),
                       STsearchByIndex(G->tab, x.w));
            else
                printf("(%s,%s):C\n",STsearchByIndex(G->tab, x.v),
                       STsearchByIndex(G->tab, x.w));
        }
    post[w] = (*time)++;
}

//VISITA IN AMPIEZZA

void bfs(Graph G, Edge e, int *time, int *pre, int *st, int *dist){
    int x;
    QUEUE q= QUEUEinit(1);
    QUEUEput(q, e);
    dist[e.v] = -1;
    while (!QUEUEempty(q))
        //e = QUEUEget(q);
        if (pre[e.w]==-1){
            pre[e.w] == (*time)++;
            st[e.w]= e.v;
            dist[e.w] = dist[e.v]+1;
            for (x=0; x<G->V; x++)
                if (G->madj[e.w][x] ==1)
                    if (pre[x]==-1)
                        QUEUEput(q, EDGEcreate(e.w, x, 1));
        }
}

void GRAPHbfs(Graph G, int id) {
    int v, time=0, *pre, *st, *dist;
    /* allocazione di pre, st e dist */
    for (v=0; v < G->V; v++) {
        pre[v] = -1; st[v] = -1; dist[v] = INT_MAX;
    }
    bfs(G, EDGEcreate(id,id), &time, pre, st, dist);
    printf("\n Resulting BFS tree \n");
    for (v=0; v < G->V; v++)
        if (st[v] != -1)
            printf("%s’s parent is:%s\n",STsearchByIndex(G->tab, v),STsearchByIndex(G->tab, st[v]));
    printf("\n Levelizing \n");
    for (v=0; v < G->V; v++)
        if (st[v] != -1)
            printf("%s: %d \n",STsearchByIndex(G->tab,v),dist[v]);
}

//-------------- Applicazioni degli algoritmi di visita ---------------

//Componenti connesse
void dfsRcc(Graph G, int v, int id, int *cc){
    link t;
    cc[v]=id;
    for (t=G->ladj[v]; t!=G->z; t=t->next)
        if (cc[t->v]==-1)
            dfsRcc(G, t->v, id, cc);
}

int GRAPHcc(Graph G){
    int v, id=0, *cc;
    cc = malloc(G->V*sizeof (int ));
    for (v=0; v<G->V; v++)
        cc[v]=-1;
    for (v=0; v<G->V; v++)
        if (cc[v]==-1)
            dfsRcc(G, v, id++, cc);
    printf("Connected component(s) \n");
    for (v = 0; v < G->V; v++)
        printf("node %s in cc %d\n",STsearchByIndex(G->tab,v),cc[v]);
    return id;
}

//Ordinamento topologico inverso (il grafo è un DAG)
void TSdfsR(Graph G, int v, int *ts, int *pre, int *time){
    link t;
    pre[v]=0;
    //quando abbiamo terminato questo ciclo vuol dire che
    //abbiamo terminato il vertice di partenza
    for (t=G->ladj[v]; t!=G->z; t=t->next)
        if (pre[t->v]==-1)
            TSdfsR(G, t->v, ts, pre, time);
    ts[(*time)++]=v;
}
//DAG reverse topological sort
void DAGrts(Graph G){
    int v, time = 0, *pre, *ts;
    /* allocazione di pre e ts */
    for (v=0; v < G->V; v++) {
        pre[v] = -1;
        ts[v] = -1;
    }
    for (v=0; v < D->V; v++)
        if (pre[v]== -1)
            TSdfsR(D, v, ts, pre, &time);
    printf("DAG nodes in reverse topological order \n");
    for (v=0; v < G->V; v++)
        //Stampa in base ai tempi di completamento
        printf("%s ", STsearchByIndex(D->tab, ts[v]));
    printf("\n");
}


//ordinamento topologico
void TSdfsR2(Graph G, int v, int *ts, int *pre, int *time){
    int w;
    pre[v]=0;
    for (w=0; w<G->V; w++)
        if (G->madj[w][v] != 0)
            if (pre[w]==-1)
                TSdfsR2(G, w, ts, pre, time);
    ts[(*time)++]=v;
}

//----------- Componenti fortemente connesse ---------------------

Graph GRAPHreverse(Graph G){
    int v;
    link t;
    Graph R = GRAPHinit(G->V);
    for (v=0; v<G->V; v++)
        for (t=G->ladj[v]; t!=G->z; t=t->next)
            GRAPHinsertE(R, t->v, v);
    return R;
}

void SCCdfsR(Graph G, int w, int *scc, int *time0, int *time1, int *post){
    link t;
    scc[w]=*time1;
    for (t=G->ladj[w]; t!=G->z; t=t->next)
        if (scc[t->v]!=-1)
            SCCdfsR(G, t->v, scc, time0, time1, post);
    post[(*time0)++]=w;
}

int GRAPHscc(Graph G) {
    int v, time0 = 0, time1 = 0, *sccG, *sccR, *postG, *postR;
    Graph R = GRAPHreverse(G);
    sccG = malloc(G->V * sizeof(int));
    sccR = malloc(G->V * sizeof(int));
    postG = malloc(G->V * sizeof(int));
    postR = malloc(G->V * sizeof(int));
    for (v=0; v < G->V; v++) {
        sccG[v]=-1; sccR[v]=-1; postG[v]=-1; postR[v]=-1;
    }
    //DFS su grafo trasposto
    for (v=0; v<G->V; v++)
        if (sccR[v]!=-1)
            SCCdfsR(R, v, sccR, &time0, &time1, postR);
    time0=0;
    time1=0;
    //DFS su grafo originale
    for (v=G->V-1; v>=0; v--)
        if (sccG[postR[v]]!=-1){
            SCCdfsR(G, v, sccG, &time0, &time1, postG);
            time1++;
        }
    printf("strongly connected components \n");
    for (v = 0; v < G->V; v++)
        printf("node %s in scc %d\n",STsearchByIndex(G->tab,v),sccG[v]);
    return time1;
}

// ------------------- Alberi ricoprenti minimi ----------------------
//ALGORITMO DI PRIM

#define maxWT UINT16_MAX

void mstV(Graph G, int *st, int *wt){
    int v, w, min, *fr = malloc(G->V*sizeof (int ));
    for (v=0; v<G->V; v++){
        st[v]=-1;
        fr[v]=v;
        wt[v] = maxWT;
    }
    st[0]=0;
    wt[0]=0;
    wt[G->V]=maxWT;
    for (min=0; min!=G->V; ){
        v = min;
        st[min] = fr[min];
        for (w=0, min = G->V; w<G->V; w++){
            if (st[w]==-1){
                if (G->madj[v][w]<wt[w]){
                    wt[w] = G->madj[v][w];
                    fr[w] = v;
                }
                if (wt[w]<wt[min])
                    min = w;
            }
        }
    }
}

void GRAPHmstP(Graph G) {
    int v, *st, *wt, weight = 0;
    st = malloc(G->V*sizeof(int));
    wt = malloc((G->V+1)*sizeof(int));
    mstV(G, st, wt);
    printf("\nEdges in the MST: \n");
    for (v=0; v < G->V; v++) {
        if (st[v] != v) {
            printf("(%s-%s)\n",STsearchByIndex(G->tab,st[v]),
                   wrapper
            weight += wt[v];
        }
    }
    printf("\nminimum weight: %d\n", weight);
}

// ---------------- CAMMINI MINIMI ------------------
//ALGORITMO DI DJIKSTRA

void GRAPHspD(Graph G, int id){
    int v;
    link t;
    PQ pq = PQinit(G->V);
    int *st, *d;
    st = malloc(G->V*sizeof (int ));
    d = malloc(G->V*sizeof (int ));

    for (v=0; v<G->V; v++){
        st[v]=-1;
        d[v] = maxWT;
        PQinsert(pq, d[v], v);
    }

    d[id] = 0;
    st[id] = id;
    PQchange(pq, d[id], id);

    while (!PQempty(pq)){
        v = PQextractMin(pq);
        if (d[v] != maxWT)
            for (t=G->ladj[v]; t!= G->z; t=t->next)
                if (d[v]+t->wt < d[t->v]) {
                    d[t->v] = d[v] + t->wt;
                    PQchange(pq, d[t->v], t->v);
                    st[t->v] = v;
                }
    }
    printf("\n Shortest path tree\n");
    for (v = 0; v < G->V; v++)
        printf("parent of %s is %s \n", STsearchByIndex(G->tab, v),
               STsearchByIndex (G->tab, st[v]));
    printf("\n Min.dist. from %s\n", STsearchByIndex(G->tab, s));
    for (v = 0; v < G->V; v++)
        printf("%s: %d\n", STsearchByIndex(G->tab, v), d[v]);
    PQfree(pq);
}

//Algoritmo di Bellman-Ford
void GRAPHspBF(Graph G, int id){
    int v, i, negacycfound;
    link t;
    int *st, *d;

    st = malloc(G->V*sizeof (int ));
    d = malloc(G->V*sizeof (int));

    for (v=0; v<G->V; v++){
        st[v]=-1;
        d[v]= maxWT;
    }
    d[id]=0;
    st[id]=id;

    //ciclo esterno per i passi
    for (i=0; i<G->V-1; i++){
        for (v=0; v<G->V; v++){
            if (d[v]<maxWT)
                for (t=G->ladj[v]; t!=G->z; t=t->next)
                    if (d[t->v]>d[v]+t->wt){
                        d[t->v] = d[v] + t->wt;
                        st[t->v] = v;
                    }
        }
    }
    negacycfound=0;
    //passo ulteriore per verificare
    //ciclo negativo
    for (v=0; v<G->V; v++)
        if (d[v]<maxWT)
            for (t=G->ladj[v]; t!=G->z; t=t->next)
                if (d[t->v]>d[v]+t->wt)
                    negacycfound=1;


    if (negacycfound == 0) {
        printf("\n Shortest path tree\n");
        for (v = 0; v < G->V; v++)
            printf("Parent of %s is %s \n",
                   STsearchByIndex(G->tab, v),
                   STsearchByIndex (G->tab, st[v]));
        printf("\n Min.dist. from %s\n",
               STsearchByIndex (G->tab, s));
        for (v = 0; v < G->V; v++)
            printf("%s: %d\n", STsearchByIndex (G->tab, v), d[v]);
    }
    else
        printf("\n Negative cycle found!\n");
}