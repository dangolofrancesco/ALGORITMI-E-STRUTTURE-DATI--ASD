#include <stdio.h>
#include <stdlib.h>

typedef enum{
    zaffiro, rubino, topazio, smerlado, fine
}tipo_t;

typedef struct{
    tipo_t tipo;
    int n;
}pietra_t;

typedef struct{
    tipo_t *buf;
    int n;
}sol_t;

typedef struct {
    pietra_t *mark;
    sol_t c_sol, b_sol;
    int n_max, c_lung;
}tab_t;

int aperturaFile(FILE **fp){
    int i;
    FILE *ff = fopen("../test1.txt", "r");
    if (ff == NULL){
        printf("Error opening file");
        return -1;
    }
    fscanf(ff, "%d", &i);
    *fp = ff;
    return i;
}

void inizializza(FILE *fp, tab_t *t){
    int i;
    tab_t tab;
    tab.mark = (pietra_t *) malloc(fine*sizeof (pietra_t));
    tab.n_max = tab.c_lung = 0;
    tab.c_sol.buf = tab.b_sol.buf = NULL;
    for (i=0; i<fine; i++){
        fscanf(fp, "%d ", &tab.mark[i].n);
        tab.n_max += tab.mark[i].n;
        tab.mark[i].tipo = i;
    }
    *t = tab;
}

int disp_rip(int pos, tab_t *t){
    int i, j, found=0;

    if (pos>=t->c_sol.n){
        t->b_sol.n = t->c_sol.n;
        if (t->b_sol.buf != NULL)
            free(t->b_sol.buf);
        t->b_sol.buf = (tipo_t *) malloc(t->c_sol.n*sizeof (tipo_t));
        for (j=0; j<t->c_sol.n; j++)
            t->b_sol.buf[j] = t->c_sol.buf[j];
        return 1;
    }


    for (i=0; i<fine; i++){
        tipo_t prec = t->c_sol.buf[pos-1];
        if (t->mark[i].n>0){
            if (pos==0)
                found = 1;
            if (pos!=0 && t->mark[i].tipo == zaffiro){
                if (prec == zaffiro || prec == topazio)
                    found = 1;
            }
            if (pos!=0 && t->mark[i].tipo == rubino){
                if (prec == zaffiro || prec == topazio)
                    found = 1;
            }
            if (pos!=0 && t->mark[i].tipo == topazio){
                if (prec == smerlado || prec == rubino)
                    found = 1;
            }
            if (pos!=0 && t->mark[i].tipo == smerlado){
                if (prec == smerlado || prec == rubino)
                    found = 1;
            }
        }

        if (found==1){
            t->mark[i].n--;
            t->c_sol.buf[pos] = t->mark[i].tipo;
            if(disp_rip(pos+1, t))
                return 1;
            t->mark[i].n++;
            found=0;
        }
    }
    return 0;
}

void stampa(tab_t *t){
    int i;
    printf("Collana massima di lunghezza %d\n", t->b_sol.n);
}

void free1d(tab_t *t){
    free(t->mark);
    free(t->c_sol.buf);
    free(t->b_sol.buf);
}

void wrapper(tab_t *t){
    int found=0, i;

    t->c_sol.buf = (tipo_t*) malloc(t->n_max*sizeof (tipo_t));
    if (t->c_sol.buf == NULL){
        printf("Errore allocazione");
        exit(1);
    }
    for (i=0; i<t->n_max; i++)
        t->c_sol.buf[i] = fine;

    for (t->c_sol.n=t->n_max; t->c_sol.n>=1 && found==0; t->c_sol.n--){
        found = disp_rip(0, t);
    }

    stampa(t);
    free1d(t);
}

int main() {
    FILE *fp;
    int n, i, j, d;
    tab_t tab;

    n = aperturaFile(&fp);
    for (i=0; i<n; i++){
        inizializza(fp, &tab);
        printf("Test #%d\n", i+1);
        printf("ZAFFIRO %d, RUBINO %d, TOPAZIO %d, SMERALDO %d, TOT:%d\n",
               tab.mark[0].n, tab.mark[1].n, tab.mark[2].n, tab.mark[3].n, tab.n_max);
        wrapper(&tab);
    }
    fclose(fp);
}
