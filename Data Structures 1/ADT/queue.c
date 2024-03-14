//
// Created by Francesco D'Angolo on 08/12/22.
//

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

/*static Item *q;
static int N, head, tail;

//inizializzazione
void QUEUEinit(int maxN) {
    q = malloc((maxN+1)*sizeof(Item));
    N = maxN+1;
    head = N;
    tail = 0;
}

int QUEUEempty() {
    return head%N == tail;
}

void QUEUEput(Item val) {
    q[tail++] = val;
    tail = tail%N;
}

Item QUEUEget() {
    head = head%N;
    return q[head++];
}*/

/*struct queue {
    Item *q;
    int N, head, tail;
};

QUEUE QUEUEinit(int maxN) {
    QUEUE q = malloc(sizeof *q);
    q->q = malloc(maxN*sizeof(Item));
    q->N=maxN+1;
    q->head = q->N;
    q->tail = 0;
    return q;
}
int QUEUEempty(QUEUE q) {
    return (q->head)%(q->N) == q->tail;
}

void QUEUEput(QUEUE q, Item val) {
    q->q[tail++] = val;
    q->tail = q->tail%N;
}
Item QUEUEget(QUEUE q) {
    q->head = q->head%N;
    return q->q[q->head++];
}*/

/*typedef struct QUEUEnode *link;
struct QUEUEnode{
    Item val;
    link next;
};

static link head, tail;

link NEW (Item val, link next) {
    link x = malloc(sizeof *x);
    x->val = val;
    x->next = next;
    return x;
}

void QUEUEinit(int maxN) {
    head = tail = NULL;
}

int QUEUEempty() {
    return head == NULL;
}

void QUEUEput(Item val) {
    if (head == NULL) {
        head = (tail = NEW(val, head));
        return;
    }
    tail->next = NEW(val, tail->next);
    tail = tail->next;
}

Item QUEUEget() {
    Item tmp = head->val;
    link t = head->next;
    free(head);
    head = t;
    return tmp;
}*/

typedef struct QUEUEnode *link;
struct QUEUEnode{
    Item val;
    link next;
};
struct queue {
    link head;
    link tail;
};

link NEW(Item val, link next) {
    link x = malloc(sizeof *x) ;
    x->val = val;
    x->next = next;
    return x;
}
QUEUE QUEUEinit(int maxN) {
    QUEUE q = malloc(sizeof *q) ;
    q->head = NULL;
    return q;
}
int QUEUEempty(QUEUE q) {
    return q->head == NULL;
}
void QUEUEput (QUEUE q, Item val) {
    if (q->head == NULL){
        q->tail = NEW(val, q->head) ;
        q->head = q->tail;
        return;
    }
    q->tail->next = NEW(val,q->tail->next);
    q->tail = q->tail->next;
}
Item QUEUEget(QUEUE q) {
    Item tmp = q->head->tmp;
    link t = q->head->next;
    free(q->head);
    q->head = t;
    return tmp;
}