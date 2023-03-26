//
// Created by Francesco D'Angolo on 02/01/23.
//

#include "ST.h"

struct symbtab{
    Item *a;
    int size;
    int maxN;
};

ST STinit(int maxN){
    ST st;
    int i;
    st = malloc(sizeof (struct symbtab));
    if (st==NULL){
        printf("Errore di allocazione\n");
        return NULL;
    }
    st->a = malloc(maxN*sizeof (Item));
    if (st->a == NULL){
        printf("Errore di allocazione\n");
        free(st);
        return NULL;
    }
    for (i=0; i<maxN; i++)
        st->a[i] = ITEMsetNull();
    st->maxN=maxN;
    st->size=0;
    return st;
}

void STfree(ST st){
    free(st->a);
    free(st);
}

/*inserimento ordinato per effettuare ricerca dicotomica*/
void STinsert(ST st, Item x) {
    int i = st->size++;
    if (st->size > st->maxN) {
        st->a = realloc(st->a, (2*st->maxN)*sizeof(Item));
        if (st->a == NULL){
            printf("Errore di allocazione di memoria\n");
            free(st);
            return;
        }
        st->maxN = 2*st->maxN;
    }
    while( (i>0) && KEYcmp(KEYget(&x), KEYget(&st->a[i-1]))<0) {
        st->a[i] = st->a[i-1];
        i--;
    }
    st->a[i] = x;
}

/*Ad ogni inserimento verifico se l'elemento da inserire è già presente
 * Quindi utilizzo un vettore ordinato per la tabella di simboli
 * per ridurre la complessità della ricerca, inoltre
 * con i grafi bisogna sempre effettuare una ricerca dell'indice*/
int searchR(ST st, int l, int r, KEY k){
    int m;
    m = (l+r)/2;
    if (l>r)
        return -1;
    if (KEYcmp(k, KEYget(&(st->a[m])))==0)
        return m;
    if (l==r)
        return -1;
    if (KEYcmp(k, KEYget(&(st->a[m])))<0)
        return searchR(st, l, m-1, k);
    else
        return searchR(st, m+1, r, k);
}

int STsearch(ST st, KEY k){
    int i;
    return searchR(st, 0, st->size-1, k);
}

char *STsearchByIndex(ST st, int index){
    return st->a[index].elab;
}

void STdisplay(FILE *fp, ST st){
    int i;
    for (i=0; i<st->size; i++)
        fprintf(fp, "%s\n", st->a[i].elab);
}

void STdisplayByIndex(FILE *fp, ST st, int index){
    fprintf(fp, "%s", st->a[index].elab);
}

int STcount(ST st) {
    return st->size;
}




