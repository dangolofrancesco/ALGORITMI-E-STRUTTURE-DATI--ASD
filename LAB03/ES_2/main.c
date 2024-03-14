// LAB03 ES_2 - FRANCESCO PIO D'ANGOLO
#include <stdio.h>
#include <stdlib.h>
#define FILENAME "../brani.txt"
#define MAX 255


typedef struct{
    char **scelte;
    int n_scelte;
}Livello;

int apertura_file(FILE **fp);
void riempimento(Livello **val, FILE *fp, int n);
void malloc2d(char ***sol, int n);
int princ_molt(int pos, Livello *val, char **sol, int n, int cnt);
void free2d(char **v, int n);

int main() {
    int n, pos=0, cnt=0;
    FILE *fp;
    Livello *val;

    // vettore perché vogliamo solo enumerare, a ogni passo il vettore verrà sovrascritto
    char **sol;
    n = apertura_file(&fp);
    riempimento(&val, fp, n);
    malloc2d(&sol,n);

    cnt = princ_molt(pos, val, sol, n, cnt);
    // cnt = produttoria delle proposte di ogni amico
    // (secondo il principio di moltiplicazione utilizzato in questo esercizio)
    printf("\nIl numero totale di playlist possibili è %d", cnt);

    free(val);
    free2d(sol, n);
    return 0;
}

int apertura_file(FILE **fp){
    int n;
    FILE *fp1 = fopen(FILENAME, "r");
    if (fscanf(fp1,"%d", &n)!=1)
        printf("Errore");
    *fp = fp1;
    return n;
}

void riempimento(Livello **val,FILE *fp, int n){
    int i,j;
    Livello *v1;
    v1 = (Livello *) malloc(n*sizeof (Livello));
    for (i=0;i<n;i++){
        fscanf(fp,"%d", &(v1[i].n_scelte));
        v1[i].scelte = (char **) malloc(v1[i].n_scelte*sizeof (char *));
        for (j=0;j<v1[i].n_scelte;j++){
            v1[i].scelte[j] = (char *) malloc(MAX*sizeof (char ));
            fscanf(fp, "%s", v1[i].scelte[j]);
        }
    }
    *val = v1;
}

void malloc2d(char ***sol, int n){
    char **s1;
    int i;
    s1 = (char **) malloc(n* sizeof (char *));
    for (i=0;i<n;i++)
        s1[i] = (char *) malloc(MAX*sizeof (char ));
    *sol = s1;
}

int princ_molt(int pos, Livello *val, char **sol, int n, int cnt){
    int i;
    if (pos>=n){
        printf("Playlist %d:\n", cnt+1);
        for(i=0;i<n;i++)
            printf("%s ", sol[i]);
        printf("\n");
        return cnt+1;
    }

    for (i=0;i<val[pos].n_scelte;i++){
        sol[pos] = val[pos].scelte[i];
        cnt = princ_molt(pos+1, val, sol, n, cnt);
    }
    return cnt;
}

void free2d(char **v, int n){
    int i;
    for (i=0;i<n;i++)
        free(v[i]);
    free(v);
}