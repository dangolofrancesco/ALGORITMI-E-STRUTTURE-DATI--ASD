#include <stdio.h>
#include <stdlib.h>

#define MAX 4

typedef enum{
    zaffiro, smeraldo, rubino, topazio
}e_tipo;

typedef struct {
    //tipo di pietra
    e_tipo tipo;
    //numero e valore di ogni pietra
    int n, val;
    int c_rip;
}Item;

typedef struct{
    e_tipo *sol;
    int n, val;
}sol_t;

typedef struct {
    //vettore di pietre (mark)
    Item *pietre;
    sol_t c_sol, best_sol;
    int max_rip, n_max, max_val;
    int c_rip, n_zaf, n_smer;
}tab_t;

int aperturaFile(FILE **fp);
void set(FILE *fp, tab_t *tab);
void wrapper(tab_t t);
void aggiornaBest(tab_t t);
void disp_rip(int pos, tab_t t );

int main() {
    FILE *fp;
    int n, i;
    tab_t tab;

    n = aperturaFile(&fp);
    for (i=0; i<1; i++){
        set(fp, &tab);
    }
    for (i=0; i<1; i++){
        //wrapper(tab);
        printf("%d %d %d %d\n", tab.pietre[0].n, tab.pietre[1].n, tab.pietre[2].n, tab.pietre[3].n);
        wrapper(tab);
    }

}

int aperturaFile(FILE **fp){
    int i;
    FILE *ff = fopen("../test_set.txt", "r");
    if (ff == NULL){
        printf("Error opening file");
        return -1;
    }
    fscanf(ff, "%d", &i);
    *fp = ff;
    return i;
}

void set(FILE *fp, tab_t *tab){
    tab_t t;
    int i;
    t.pietre = (Item*) malloc(MAX*sizeof (*t.pietre));
    t.n_max = t.best_sol.n = t.c_rip = t.best_sol.val = 0;
    for (i=0; i<MAX; i++){
        fscanf(fp, "%d", &t.pietre[i].n);
        t.pietre[i].tipo = i;
        t.n_max += t.pietre[i].n;
        t.pietre[i].c_rip=0;
    }
    for (i=0; i<MAX; i++){
        fscanf(fp, "%d", &t.pietre[i].val);
        t.max_val = t.max_val + t.pietre[i].n*t.pietre[i].val;
    }
    fscanf(fp, "%d", &t.max_rip);
    *tab = t;
}

void wrapper(tab_t t){

    t.c_sol.sol = (e_tipo *) malloc(t.n_max*sizeof (*t.c_sol.sol));
    t.c_sol.val=t.c_sol.n=0;
    t.c_rip = 0;
    disp_rip(0, t);

    printf("%d", t.best_sol.val);

}

void disp_rip(int pos, tab_t t ){
    int i, found=0;

    if (t.c_sol.val> t.best_sol.val && t.pietre[zaffiro].c_rip <=t.pietre[smeraldo].c_rip)
        aggiornaBest(t);

    for (i=0; i<MAX; i++){
        if (t.pietre[i].n>0 && (t.c_rip+1)<t.max_rip){
            if (pos==0)
                found=1;
            if (pos!=0 && t.pietre[i].tipo==1){
                if (t.c_sol.sol[pos-1] == 1 || t.c_sol.sol[pos-1] == 3)
                    found=1;
            }
            if (pos!=0 && t.pietre[i].tipo==2){
                if (t.c_sol.sol[pos-1] == 1 || t.c_sol.sol[pos-1] == 3)
                    found=1;
            }
            if (pos!=0 && t.pietre[i].tipo==3){
                if (t.c_sol.sol[pos-1] == 2 || t.c_sol.sol[pos-1] == 4)
                    found=1;
            }
            if (pos!=0 && t.pietre[i].tipo==4){
                if (t.c_sol.sol[pos-1] == 2 || t.c_sol.sol[pos-1] == 4)
                    found=1;
            }

            if (found==1){
                t.pietre[i].n--;
                t.c_sol.sol[i] = t.pietre[i].tipo;
                t.c_sol.val += t.pietre[i].val;
                t.c_sol.n++;
                t.pietre[i].c_rip++;
                if (pos!=0 && t.pietre[i].tipo == t.pietre[i-1].tipo){
                    t.c_rip++;
                }else
                    t.c_rip = 1;
                disp_rip(pos+1, t);
                t.pietre[i].n++;
                found = 0;
            }
        } else if (t.c_sol.val> t.best_sol.val && t.pietre[zaffiro].c_rip <=t.pietre[smeraldo].c_rip)
            aggiornaBest(t);
    }
}

void aggiornaBest(tab_t t){
    int i, n= t.c_sol.n;
    t.best_sol.val = t.c_sol.val;
    t.best_sol.n = n;
    t.best_sol.sol = (e_tipo *) malloc(n*sizeof (*t.best_sol.sol));
    for (i=0; i<n; i++)
        t.best_sol.sol[i] = t.c_sol.sol[i];
}