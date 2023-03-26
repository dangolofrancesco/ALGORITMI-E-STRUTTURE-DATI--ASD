//
// Created by Francesco D'Angolo on 06/01/23.
//

#include "quotazioni.h"

typedef struct BSTnode *link;

struct BSTnode{
    quotazione_t quot;
    link l, r;
};

struct BSTquot_s{
    link root;
    link z;
};

link NEW(quotazione_t q, link l, link r){
    link x = malloc(sizeof *x);
    x->quot = q;
    x->l = l;
    x->r = r;
    return x;
}

BSTquot BSTinit(){
    BSTquot quot = malloc(sizeof *quot);
    quot->z = NEW(QUOTsetNull(), NULL, NULL);
    quot->root = quot->z;
    return quot;
}

static int countR(link h, link z){
    if (h==z)
        return 0;
    return countR(h->l, z) + countR(h->r, z) +1;
}

int BSTcount(BSTquot bst){
    return countR(bst->root, bst->z);
}

int BSTempty(BSTquot bst){
    if (BSTcount(bst)==0)
        return 1;
    return 0;
}

link insertR(link h, quotazione_t q, link z){
    if (h==z){
        return NEW(q, z, z);
    }
    if (DATAcmp(q.data, h->quot.data)<0){
        h->l = insertR(h->l, q, z);
    }

    else if (DATAcmp(q.data, h->quot.data)>0){
        h->r = insertR(h->r, q, z);
    }

    else{
        h->quot.num += q.num;
        h->quot.den += q.den;
    }
    return h;
}

void BSTinsertLeaf(data_t data, float val, int qta, BSTquot bst){
    quotazione_t q;
    q.data = data;
    q.num = val*((float) qta);
    q.den = qta;
    bst->root = insertR(bst->root, q, bst->z);
}


static void treePrint(FILE *fp, link h, link z){
    if (h==z)
        return;
    treePrint(fp, h->l, z);
    QUOTstore(fp, h->quot);
    treePrint(fp, h->r, z);
}

void BSTvisit(FILE *fp, BSTquot bst){
    if (BSTempty(bst))
        return;
    treePrint(fp, bst->root, bst->z);
}


quotazione_t searchR(link h, link z, data_t data){
    int cmp;
    if (h==z)
        return QUOTsetNull();

    cmp = DATAcmp(data, h->quot.data);
    if (cmp==0)
        return h->quot;
    if (cmp<0)
        return searchR(h->l, z, data);
    return searchR(h->r, z, data);
}


quotazione_t BSTsearch(BSTquot bst, data_t data){
    return searchR(bst->root, bst->z, data);
}

void static maxMin(link h, link z, data_t d1, data_t d2, float *max, float *min){
    int cmp1, cmp2;
    float tmp;
    cmp1 = DATAcmp( QUOTgetData(h->quot), d1);
    cmp2 = DATAcmp(d2, QUOTgetData(h->quot));

    if (h==z)
        return;

    maxMin(h->l, z, d1, d2, max, min);
    if (cmp1 >=0 && cmp2>=0){
        tmp = (h->quot.num)/((float )h->quot.den);
        if (tmp>*max) {
            *max = tmp;
        }
        if (tmp<*min)
            *min = tmp;
    }
    maxMin(h->r, z, d1, d2, max, min);
}

void BSTmaxmin(BSTquot bst, data_t d1, data_t d2, float *max, float *min){
    maxMin(bst->root, bst->z, d1, d2, max, min);
}

void maxMinTot(link h, link z, float *max, float *min){
    if (h==z)
        return;

    maxMinTot(h->l, z, max, min);
    float tmp = QUOTgetVal(h->quot);
    if (tmp>*max)
        *max = tmp;
    if (tmp<*min)
        *min = tmp;
    maxMinTot(h->r, z, max, min);
}

void BSTmaxMinTot(BSTquot bst, float *max, float *min){
    maxMinTot(bst->root, bst->z, max, min);
}

