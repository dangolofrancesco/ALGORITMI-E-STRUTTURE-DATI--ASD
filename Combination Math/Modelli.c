//
// Created by Francesco D'Angolo on 13/01/23.
//

#include "Modelli.h"

//PRINCIPIO DI MOLTIPLICAZIONE
typedef struct {
    int *scelte;
    int num_scelte;
} livello;

livello *LIVELLOfill(int n){
    int i;
    livello *val;
    val = malloc(n*sizeof (livello));
    //riempimento di num_scelte ad ogni cella di val
    for (i=0; i<n; i++)
        val[i].scelte = malloc(val[i].num_scelte*sizeof (int ));
    return val;
}

int princ_molt(int pos, livello *val, int *sol, int n, int cnt){
    int i;
    if (pos>=n){
        //stampa elementi di sol
        return cnt+1;
    }
    //pos: indica posizione nel vettore val
    for (i=0; i<val[pos].num_scelte; i++){
        sol[pos] = val[pos].scelte[i];
        cnt = princ_molt(pos+1, val, sol, n, cnt);
    }
    return cnt;
}

//DISPOSIZIONI SEMPLICI
int disp_semp(int pos, int *val, int *sol, int *mark, int n, int k, int cnt){
    int i;
    if (pos>=k){
        //stampa
        return cnt+1;
    }

    for (i=0; i<n; i++){
        if (mark[i]==0){
            mark[i]=1;
            sol[pos] = val[i];
            cnt = disp_semp(pos+1, val, sol, mark, n, k, cnt);
            //backtrack
            mark[i]=0;
        }
    }
    return cnt;
}

//DISPOSIZIONI RIPETUTE
int disp_rip(int pos, int *val, int *sol, int n, int k, int cnt){
    int i;
    if (pos>=k){
        //stampa
        return cnt+1;
    }

    for (i=0; i<n; i++){
        sol[pos] = val[i];
        cnt = disp_rip(pos+1, val, sol, n, k, cnt);
    }
    return cnt;
}

//PERMUTAZIONI SEMPLICI
int perm_semp(int pos, int *val, int *sol, int *mark, int n, int cnt){
    int i;
    if (pos>=n){
        //stampa
        return cnt+1;
    }

    for (i=0; i<n; i++){
        if (mark[i]==0){
            mark[i]=1;
            sol[pos] = val[i];
            cnt = disp_semp(pos+1, val, sol, mark, n, cnt);
            //backtrack
            mark[i]=0;
        }
    }
    return cnt;
}

//PERMUTAZIONI RIPETUTE
//dist_val[]: vettore ordinato di elementi distinti del multiset (dimensione n_dist)
//mark[]: occorrenze di ciascun elemento
int perm_rip(int pos, int *dist_val, int *sol, int *mark, int n, int cnt, int n_dist){
    int i;
    if (pos>=n){
        //stampa
        return cnt+1;
    }

    for (i=0; i<n_dist; i++){
        if (mark[i]>0){
            mark[i]--;
            sol[pos]=dist_val[i];
            cnt = perm_rip(pos+1, dist_val, sol, mark, n, cnt, n_dist);
            mark[i]++;
        }
    }
    return cnt;
}

//COMBINAZIONI SEMPLICI
int comb_semp(int pos, int *val, int *sol, int n, int k, int cnt, int start){
    int i;
    if (pos>=k){
        //stampa
        return cnt+1;
    }

    for (i=start; i<n; i++){
        sol[pos] = val[i];
        cnt = comb_semp(pos+1,val, sol, n, k, cnt, i+1);
    }
    return cnt;
}

//COMBINAZIONI RIPETUTE
int comb_rip(int pos, int *val, int *sol, int n, int k, int start, int cnt){
    int i;
    if (pos>=k){
        //stampa
        return cnt+1;
    }

    for (i=start; i<n; i++){
        sol[pos]= val[i];
        cnt= comb_rip(pos+1, val, sol, n, k, start, cnt);
        start++;
    }
    return cnt;
}

//----Power-set-----

int powerset1(int pos, int *val, int *sol, int n, int start, int cnt){
    int i;
    if (i==0 || pos>=cnt){
        if (i!=0)
            printf(" ");

    }
}

void findPathR(Graph G, int *path, int PF, int M, int pos, int currV, int *bestP, int *bestV, int start, int *treasure){
    int v, w, gold;
    gold = STsearchGoldByIndex(G->st, start);

    if (start == 0 || M<=0 || PF<=0) {
        currV += *treasure;
        if (start != 0) {
            if (STsearchDepthByindex(G->st, start) == 1)
                currV = (2 * (currV)) / 3;
            else if (STsearchDepthByindex(G->st, start) == 2)
                currV = currV / 2;
            else
                return;
            if (currV > *bestV) {
                *bestV = currV;
                for (v = 0; v < pos; v++)
                    bestP[v] = path[v];
            }
        }
    }


    if (STsearchtreasureByIndex(G->st, start) > *treasure)
        *treasure = STsearchtreasureByIndex(G->st, start);



    ROOMsetGold(G->st, start, 0);
    for  (v=0; v<G->V; v++){
        if (G->madj[start][v]>-1){
            if ((pos==0 && v=0) || (pos!=0 && v>=0)){
                if (PF >= G->madj[start][v]){
                    path[pos] = v;
                    findPathR(G, path, PF-G->madj[start][v], M-1, pos+1, currV+STsearchGoldByIndex(G->st, v), bestP, bestV, v, treasure);
                }
            }
        }
    }

    ROOMsetGold(G->st, start, gold);
    return;
}


void GRAPHbestPath(Graph G, int PF, int M){
    int v, treasure=0, *path, *bestP, bestV;
    path = malloc(M*sizeof(int));
    bestP = malloc(M*sizeof(int));
    for (v=0; v<M; v++){
        path[v] = -1;
        bestP[v] = -1;
    }

    findPathR(G, path, PF, M, 0, 0, bestP, &bestV, 0, &treasure);

    //stampa
}