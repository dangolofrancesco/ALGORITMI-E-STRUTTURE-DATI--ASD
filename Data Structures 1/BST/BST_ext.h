//
// Created by Francesco D'Angolo on 04/01/23.
//

#ifndef BST_BST_EXT_H
#define BST_BST_EXT_H

#include "Item.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct  binarysearchtree *BST;

//FUNZIONE MODIFICATA
BST BSTinit();

void BSTfree(BST bst);
int BSTcount(BST bst);
int BSTempty(BST bst);
Item BSTmin(BST bst);
Item BSTmax(BST bst);

//FUNZIONI MODIFICATE
void BSTinsert_leafI(BST bst, Item x);
void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);

Item BSTsearch(BST bst, Key k);
void BSTvisit(BST bst, int strategy);

//NUOVE FUNZIONI
void BSTdelete(BST bst, Key k);
Item BSTselect(BST bst, int r);
Item BSTsucc(BST bst, Key k);
Item BSTpred(BST bst, Key k);
void BSTbalance(BST bst);

#endif //BST_BST_EXT_H
