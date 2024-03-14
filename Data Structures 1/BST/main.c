#include <stdio.h>
#include "Item.h"
#include "ADT_BST.h"


int LEFT(int i) { return (i*2 + 1); }
int RIGHT(int i) { return (i*2 + 2); }
int PARENT(int i) { return ((i-1)/2); }

typedef struct node *link;

struct node{
    char *name;
    link left;
    link right;
};


//CALCOLO NUMERO DI NODI
int count(link root){
    if (root==NULL)
        return 0;
    return count(root->left) + count(root->right) + 1;
}

//Variante più intuitiva
void count2(link root, int *cntP){
    if (root==NULL)
        return;
    count2(root->left, cntP);
    count2(root->right, cntP);
    (*cntP)++;
}

//CALCOLO ALTEZZA ALBERO
int height(link root){
    int u, v;
    if (root==NULL)
        return -1;
    u = height(root->left);
    v = height(root->right);
    if (u>v)
        return u+1;
    return v+1;
}

void preOrder(link root){
    if (root==NULL)
        return;
    printf("%s", root->name);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(link root){
    if (root==NULL)
        return;
    preOrder(root->left);
    preOrder(root->right);
    printf("%s", root->name);
}



int main() {
}