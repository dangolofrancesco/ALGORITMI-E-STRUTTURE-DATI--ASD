//LAB06 ES01 - FRAMCESCO PIO D'ANGOLO 295068
#include <stdio.h>

typedef struct {
    int inizio, fine, delta;
}tempo_t;

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

void inizializza(FILE *fp, tempo_t *t, int n){
    int i;
    for (i=0; i<n; i++){
        fscanf(fp, "%d %d", &t[i].inizio, &t[i].fine);
        t[i].delta = DELTAdef(t[i]);
    }
}

void stampa(tempo_t *t, int i, int *p){
    if (p[i]==-1){
        printf("(%d, %d) ", t[i].inizio, t[i].fine);
        return;
    }
    stampa(t, p[i], p);
    printf("(%d, %d) ", t[i].inizio, t[i].fine);
}

void sequenzeDP(tempo_t *t, int N){
    int i, j, ris=0, last;
    int opt[N], p[N];

    opt[0] = t[0].delta;
    p[0] = -1;
    for (i=1; i<N; i++){
        opt[i] = t[i].delta;
        p[i] = -1;
        for (j=0; j<i; j++){
            if (!pruning(t[j], t[i]) && opt[i] < t[i].delta+opt[j]){
                opt[i] = t[i].delta + opt[j];
                p[i] = j;
            }
            if (ris <= opt[i]){
                ris = opt[i];
                last = i;
            }
        }
    }
    printf("La sequenza di durata massima è:\n");
    stampa(t, last, p);
    printf("\nLa durata è: %d", ris);
}

int main() {
    FILE *fp;
    int i, n = aperturaFile(&fp);
    tempo_t tab[n];

    inizializza(fp, tab, n);
    sequenzeDP(tab, n);
}
