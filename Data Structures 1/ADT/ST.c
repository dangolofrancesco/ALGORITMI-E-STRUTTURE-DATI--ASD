//
// Created by Francesco D'Angolo on 08/12/22.
//

#include "ST.h"
#include "stdlib.h"
#include "stdio.h"

int GETindex(Key k) {
    int i=0, b=26;
    for (; *k!='0'; k++){
        i = (b*i + (*k-((int) 'A')));
    }
    return i;
}

/*struct symbtab {
    Item *a;
    int maxN;
    int size;
};

ST STinit(int maxN) {
    ST st; int i;
    st = malloc(sizeof(*st));
    st->a = malloc(maxN * sizeof(Item) );
    for (i = 0; i < maxN; i++)
        st->a[i] = ITEMsetvoid();
    st->maxN = maxN;
    st->size = 0;
    return st;
}


int STcount(ST st) {
    return st->size;
}

void STfree(ST st) {
    free(st->a);
    free(st);
}

void STdisplay(ST st){
    int i;
    for (i = 0; i < st->size; i++)
        ITEMstore(st->a[i]);
}

void STdelete(ST st, Key k) {
    int i, j=0;
    //È responsabilità del client cancellare solo
    //dopo aver accertato che la chiave è presente
    while (KEYcmp(KEYget(&st->a[j]), k)!=0)
        j++;
    //scalare tutti gli elementi successivi alla posizione j
    for (i = j; i < st->size-1; i++)
        st->a[i] = st->a[i+1];
    st->size--;
}

void STinsert(ST st, Item val) {
    int i = st->size;
    if (st->size >= st->maxN) {
        st->a=realloc(st->a,(2*st->maxN)*sizeof(Item));
        if (st->a == NULL)
            return;
        st->maxN = 2*st->maxN;
    }
    st->a[i] = val;
    st->size++;
}
Item STsearch(ST st, Key k) {
    int i;
    if (st->size == 0)
        return ITEMsetvoid();
    for (i = 0; i < st->size; i++)
        if (KEYcmp(k, KEYget(&st->a[i]))==0)
            return st->a[i];
    return ITEMsetvoid();
}

//---------------------- Vettore ordinato ------------------------

void STinsert(ST st, Item val) {
    int i = st->size++;
    if (st->size > st->maxN) {
        st->a=realloc(st->a,(2*st->maxN)*sizeof(Item));
        if (st->a == NULL)
            return;
        st->maxN = 2*st->maxN;
    }
    //while dell'insertion sort (controllo all'indietro)
    while((i>0)&&KEYcmp(KEYget(&val),KEYget(&st->a[i-1]))==-1){
        st->a[i] = st->a[i-1];
        i--; }
    st->a[i] = val;
}

//IN VETTORE ORDINATO HA SENSO
Item STselect(ST st, int r) {
    return st->a[r];
}


//Ricerca dicotomica in vettore ordinato
Item searchR(ST st, int l, int r, Key k) {
    int m;
    m = (l + r)/2;
    if (l > r)
        return ITEMsetvoid();
    if (KEYcmp(k,KEYget(&st->a[m]))==0)
        return st->a[m];
    if (l == r)
        return ITEMsetvoid();
    if (KEYcmp(k, KEYget(&st->a[m]))==-1)
        return searchR(st, l, m-1, k);
    else
        return searchR(st, m+1, r, k);
}

//Wrapper di searchR
Item STsearch(ST st, Key k) {
    return searchR(st, 0, st->size-1, k) ;
}*/

//------------------- LISTA -----------------------------

typedef struct STnode* link;
struct STnode {
    Item val;
    link next;
};
typedef struct {
    link head;
    int size;
} list;

struct symbtab {
    list tab;
};

static link NEW( Item val, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL) return NULL;
    x->val = val;
    x->next = next;
    return x;
}

ST STinit(int maxN) {
    ST st;
    st = malloc(sizeof(*st));
    if(st == NULL)
        return NULL;
    st->tab.size = 0;
    st->tab.head = NULL;
    return st;
}

void STfree(ST st) {
    link x, t;
    for (x = st->tab.head; x != NULL; x = t) {
        t = x->next;
        free(x); }
    free(st);
}

int STcount(ST st) {
    return st->tab.size;
}

void STdisplay(ST st) {
    link x;
    for (x = st->tab.head; x != NULL; x = x->next)
        ITEMstore(x->val);
}

Item STsearch(ST st, Key k) {
    link x;
    if (st == NULL)
        return ITEMsetvoid();
    if (st->tab.head == NULL)
        return ITEMsetvoid();
    for (x = st->tab.head; x != NULL; x = x->next)
        if (KEYcmp( KEYget(&x->val), k) ==0)
            return x->val;
    return ITEMsetvoid();
}

void STdelete(ST st, Key k) {
    link x, p;
    if (st == NULL)
        return;
    if (st->tab.head == NULL)
        return;
    for (x = st->tab.head, p = NULL; x != NULL; p = x, x = x->next) {
        if (KEYcmp(k, KEYget(&x->val)) == 0) {
            if (x == st->tab.head)
                st->tab.head = x->next;
            else
                p->next = x->next;
            free(x);
            break;
        }
    }
    st->tab.size--;
}

void STinsert(ST st, Item val) {
    if (st == NULL)
        return;
    st->tab.head = NEW(val, st->tab.head);
    st->tab.size++;
}

Item STselect(ST st, int r) { int i;
    link x = st->tab.head;
    for (i = r; i>0; i--)
        x = x->next;
    return x->val;
}

void STinsert(ST st, Item val) {
    link x, p;
    if (st == NULL)
        return;
    if ((st->tab.head == NULL) || (KEYcmp(KEYget(&st->tab.head->val),KEYget(&val))==1))
        st->tab.head = NEW(val,st->tab.head);
    else {
        for (x = st->tab.head->next, p = st->tab.head;
             x!=NULL && (KEYcmp(KEYget(&val),KEYget(&x->val))==1); p = x, x = x->next);
        p->next = NEW(val, x);
    }
    st->tab.size++;
}