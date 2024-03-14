//
// Created by Francesco D'Angolo on 27/11/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct node *link;

struct node{
    Item val;
    link next;
};

struct list{
    link head;
    int N;
};

link newNode(Item val, link next){
    link h = malloc(sizeof (struct node));
    if (h==NULL)
        return NULL;
    h->val = val;
    h->next = next;
    return h;
}

void listInsHead(LIST l, Item val){
    l->head = newNode(val, l->head);
    l->N++;
}