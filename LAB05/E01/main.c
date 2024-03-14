//LAB05 ES01 - FRANCESCO PIO D'ANGOLO 295068
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int inizio, fine, delta;
}tempo_t;

typedef struct {
    tempo_t *val, *sol, *b_sol, *cb_sol;
    int c_val, b_val, b_pos;
}att;

int aperturaFile(FILE **fp){
    int n;
    FILE *ff = fopen("../att.txt", "r");
    if (ff==NULL){
        printf("Errore apertura file");
        return 1;
    }
    fscanf(ff, "%d", &n);
    *fp = ff;
    return n;
}

int pruning(tempo_t t1, tempo_t t2){
    return (t1.inizio<t2.fine && t2.inizio<t1.fine);
}

int DELTAdef(tempo_t t1){
    return (t1.fine-t1.inizio);
}

void inizializza(FILE *fp, att *t, int n){
    int i;
    t->val = malloc(n* sizeof (tempo_t));

    for (i=0; i<n; i++){
        fscanf(fp, "%d %d", &t->val[i].inizio, &t->val[i].fine);
        t->val[i].delta = DELTAdef(t->val[i]);
    }
}

void powerset(int pos, int k, int start, int N, att *t){
    int i, j;
    if (pos>=k){
        for (j=0; j<pos; j++)
            t->c_val += t->sol[j].delta;
        if (t->c_val>=t->b_val){
            for (j=0; j<pos; j++){
                t->b_sol[j].inizio = t->sol[j].inizio;
                t->b_sol[j].fine = t->sol[j].fine;
            }
            t->b_val = t->c_val;
            t->b_pos = pos;
        }
        t->c_val = 0;
        return;
    }

    for (i=start; i<N; i++){
        if (pos == 0){
            t->sol[pos] = t->val[i];
            powerset(pos+1, k, i+1, N, t);
        }
        if (pos!=0 && !pruning(t->sol[pos-1], t->val[i])){
            t->sol[pos] = t->val[i];
            powerset(pos+1, k, i+1, N, t);
        }
    }
}

void free_att(att *v){
    free(v->val);
    free(v->sol);
    free(v->b_sol);
}

void wrapper(int N, att *v){
    int i;
    v->c_val = 0;
    v->b_val = 0;
    v->b_pos = 0;
    v->b_sol = calloc(N, sizeof (tempo_t));
    v->sol = (tempo_t *) malloc(N*sizeof (tempo_t));
    for (i=1; i<=N; i++){
        powerset(0, i, 0, N, v);
    }

    for (i=0; i<v->b_pos; i++){
        printf("%d %d\n", v->b_sol[i].inizio, v->b_sol[i].fine);
    }
    printf("La massima durata è %d", v->b_val);


}

int main() {
    FILE *fp;
    int i, n = aperturaFile(&fp);
    att tab;
    inizializza(fp, &tab, n);
    wrapper(n, &tab);

    free_att(&tab);
}
