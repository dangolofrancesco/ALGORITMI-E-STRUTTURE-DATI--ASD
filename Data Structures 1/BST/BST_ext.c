//
// Created by Francesco D'Angolo on 04/01/23.
//

#include "BST_ext.h"

Item minR(link h, link z) {
    if (h == z)
        return ITEMsetvoid();
    if (h->l == z)
        return (h->item);
    return minR(h->l, z);
}

Item BSTmin(BST bst) {
    return minR(bst->root, bst->z);
}

Item maxR(link h, link z) {
    if (h == z)
        return ITEMsetvoid();
    if (h->r == z)
        return (h->item);
    return maxR(h->r, z);
}
Item BSTmax(BST bst) {
    return maxR(bst->root, bst->z);
}

typedef struct BSTnode* link;

struct BSTnode{
    Item item;
    //puntatore al padre
    link p;
    link l;
    link r;
    //dimensione sotto-albero
    int N;
};

struct binarysearchtree{
    link root;
    link z;
};

static link NEW(Item item, link p, link l, link r, int N){
    link x = malloc(sizeof *x);
    x->item = item;
    x->p = p;
    x->l = l;
    x->r = r;
    x->N = N;
    return x;
}

BST BSTinit(){
    BST bst = malloc(sizeof *bst);
    bst->z = NEW(ITEMsetvoid(), NULL, NULL, NULL, 0 );
    bst->root = bst->z;
    return bst;
}

Item searchSucc(link h, Key k, link z) {
    link p;
    if (h == z)
        return ITEMsetNull();
    if (KEYcompare(k, KEYget(h->item))==0) {
        if (h->r != z)
            return minR(h->r, z);
        else {
            p = h->p;
            while (p != z && h == p->r) {
                h = p;
                p = p->p;
            }
            return p->item;
        }
    }
    if (KEYcompare(k, KEYget(h->item))==-1)
        return searchSucc(h->l, k, z);
    return searchSucc(h->r, k, z);
}

Item BSTsucc(BST bst, Key k) {
    return searchSucc(bst->root, k, bst->z);
}

Item searchPred(link h, Key k, link z) {
    link p;
    if (h == z)
        return ITEMsetNull();
    if (KEYcompare(k, KEYget(h->item))==0) {
        if (h->l != z)
            return maxR(h->l, z);
        else {
            p = h->p;
            while (p != z && h == p->l) {
                h = p; p = p->p;}
            return p->item;
        }
    }
    if (KEYcompare(k, KEYget(h->item))==-1)
        return searchPred(h->l, k, z);
    return searchPred(h->r, k, z);
}
Item BSTpred(BST bst, Key k) {
    return searchPred(bst->root, k, bst->z);
}

link insertR(link h, Item x, link z) {
    if (h == z)
        return NEW(x, z, z, z, 1);
    if (KEYcompare(KEYget(x), KEYget(h->item))==-1) {
        h->l = insertR(h->l, x, z);
        h->l->p = h;
    }
    else {
        h->r = insertR(h->r, x, z);
        h->r->p = h;
    }
    (h->N)++;
    return h;
}
void BSTinsert_leafR(BST bst, Item x) {
    bst->root = insertR(bst->root, x, bst->z);
}

void BSTinsert_leafI(BST bst, Item x) {
    link p = bst->root, h = p;
    if (bst->root == bst->z) {
        bst->root = NEW(x, bst->z, bst->z, bst->z, 1);
        return;
    }
    while (h != bst->z) {
        p = h;
        h->N++;
        h=(KEYcompare(KEYget(x),KEYget(h->item))==-1) ? h->l : h->r;
    }
    h = NEW(x, p, bst->z, bst->z, 1);
    if (KEYcompare(KEYget(x), KEYget(p->item))==-1)
        p->l = h;
    else
        p->r = h;
}

Item selectR(link h, int r, link z) {
    int t;
    if (h == z)
        return ITEMsetNull();
    t = h->l->N;
    if (t > r)
        return selectR(h->l, r, z);
    if (t < r)
        return selectR(h->r, r-t-1, z);
    return h->item;
}
Item BSTselect(BST bst, int r) {
    return selectR(bst->root, r, bst->z);
}

link insertT(link h, Item x, link z) {
    if (h == z)
        return NEW(x, z, z, z, 1);
    if (KEYcmp(KEYget(x), KEYget(h->item))==-1) {
        h->l = insertT(h->l, x, z);
        h = rotR(h);
        h->N++;
    }
    else {
        h->r = insertT(h->r, x, z);
        h = rotL(h);
        h->N++;
    }
    return h;
}
void BSTinsert_root(BST bst, Item x) {
    bst->root = insertT(bst->root, x, bst->z);
}

link partR(link h, int r) {
    int t = h->l->N;
    if (t > r) {
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if (t < r) {
        h->r = partR(h->r, r - t - 1);
        h = rotL(h);
    }
    return h;
}

//a e b sono le radici dei due sottoalberi
link joinLR(link a, link b, link z) {
    if (b == z)
        return a;
    b = partR(b, 0);
    b->l = a;
    a->p = b;
    b->N = a->N + b->r->N +1;
    return b;
}

link deleteR(link h, Key k, link z) {
    link y, p;
    if (h == z)
        return z;
    if (KEYcompare(k, KEYget(h->item))==-1)
        h->l = deleteR(h->l, k, z);
    if (KEYcompare(k, KEYget(h->item))==1)
        h->r = deleteR(h->r, k, z);
    (h->N)--;
    if (KEYcompare(k, KEYget(h->item))==0) {
        y=h;
        p=h->p;
        h = joinLR(h->l, h->r, z);
        h->p = p;
        free(y);
    }
    return h;
}
void BSTdelete(BST bst, Key k) {
    bst->root= deleteR(bst->root, k, bst->z);
}

static link balanceR(link h, link z) {
    int r;
    if (h == z)
        return z;
    //rango del nodo associato alla chiave mediana inferiore
    // che vogliamo far risalire
    r = (h->N+1)/2-1;
    h = partR(h, r);
    h->l = balanceR(h->l, z);
    h->r = balanceR(h->r, z);
    return h;
}
void BSTbalance(BST bst) {
    bst->root = balanceR(bst->root, bst->z);
}