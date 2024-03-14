//LAB04 E01 - FRANCESCO PIO D'ANGOLO 295068
#include <stdio.h>
#include <stdlib.h>

#define FILENAME "../grafo.txt"

typedef struct{
    int u;
    int v;
}archi_t;


int leggiFile(archi_t **archi, int **val){
    int n, e, i;
    archi_t *a1;
    int *v1;
    FILE *fp= fopen(FILENAME, "r");
    if (fp==NULL)
        return 0;
    fscanf(fp,"%d %d",&n, &e);

    //allocazione archi
    a1 = (archi_t *) malloc(e*sizeof *a1);
    if (a1==NULL)
        return 0;
    for (i=0;i<e;i++)
        fscanf(fp, "%d %d", &a1[i].u, &a1[i].v);
    *archi = a1;

    //allocazione vertici
    v1 = (int *) malloc(n*sizeof *v1);
    if (v1==NULL)
        return 0;
    for (i=0; i<n; v1[i]=i, i++);
    *val = v1;

    fclose(fp);
    return n;
}

int controllo(int *sol,archi_t *archi, int pos, int e){
    int i, j, ok, cnt=0;
    //per tutti gli archi almeno uno dei vertici appartiene a sol
    for (i=0; i<e; i++){
        ok = 0;
        for (j=0;j<pos && ok==0;j++){
            if (archi[i].u==sol[j] || archi[i].v == sol[j])
                ok=1;
        }
        if (ok==1)
            cnt++;
        else
            return 0;
    }
    if (cnt==e){
        return 1;
    }
}

//VERTEX COVER CON POWERSET
int powerset_r(int *val, int *sol, archi_t *archi, int n, int j, int pos, int start, int e){
    int cnt=0, i;
    //utilizzo pos==j
    if (pos==j && controllo(sol, archi, pos, e)==1){
        printf("{ ");
        for (i=0;i<j;i++)
            printf("%d ", sol[i]);
        printf("}\n");
        return 1;
    }

    for (i=start; i<n;i++){
        sol[pos] = val[i];
        cnt += powerset_r(val, sol, archi, n, j, pos+1, i+1, e);
    }
    return cnt;
}

int powerSet(int *val, int *sol, archi_t *archi, int n, int e){
    int cnt=0, j;
    //non inserisco insieme vuoto
    for (j=0;j<=n;j++){
        cnt+= powerset_r(val, sol, archi, n, j, 0, 0, e);
    }
    return cnt;
}



int main() {
    archi_t *archi;
    int *val, *sol;
    int n, i, cnt;
    n = leggiFile(&archi, &val);
    sol = calloc(n, sizeof *sol);
    cnt = powerSet(val, sol, archi, n, n);
}
