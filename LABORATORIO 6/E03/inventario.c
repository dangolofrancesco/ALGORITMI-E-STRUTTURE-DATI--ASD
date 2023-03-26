//
// modulo inventario
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inventario.h"

tabInv_t *allocaInventario(int max){
    tabInv_t *inv = (tabInv_t *) malloc(sizeof(tabInv_t));
    inv->maxInv = max;
    inv->nInv = 0;
    inv->vettInv = (inv_t *) malloc(max*sizeof(inv_t));
    return inv;
};

void liberaInventario(tabInv_t *inv){
    int i;
    free(inv->vettInv);
    free(inv);
}

void leggiStringhe(FILE *fp, inv_t *inv){
    int i;
    fscanf(fp, "%s", inv->nome);
    fscanf(fp, "%s", inv->tipo);
}

void leggiStat(FILE *fp, stat_t *stat){
    fscanf(fp, "%d", &stat->hp);
    fscanf(fp, "%d", &stat->mp);
    fscanf(fp, "%d", &stat->atk);
    fscanf(fp, "%d", &stat->def);
    fscanf(fp, "%d", &stat->mag);
    fscanf(fp, "%d", &stat->spr);
}

tabInv_t *leggiInventario(char *nomeFile){
    int i, nmax;
    tabInv_t *weapons;
    FILE *fp = fopen(nomeFile, "r");
    if (fp==NULL){
        printf("Errore");
        return NULL;
    }
    fscanf(fp, "%d", &nmax);
    weapons = allocaInventario(nmax);
    for (i=0; i< nmax; i++){
        leggiStringhe(fp, &(weapons->vettInv[i]));
        leggiStat(fp, &(weapons->vettInv[i].stat));
    }
    weapons->nInv = nmax;
    fclose(fp);
    return weapons;
};

char *strToLower(char *str){
    int i, l= strlen(str);
    char *nome = malloc(l*sizeof (char));
    for (i=0; i<l; i++){
        nome[i] = tolower(str[i]);
    }
    return nome;
}

inv_t *cercaOggettoN(tabInv_t *inv, char *chiave){
    int i;
    char *nome;
    for (i=0; i<inv->nInv; i++){
        nome = strToLower(inv->vettInv[i].nome);
        if (strcmp(nome, strToLower(chiave))==0){
            return &(inv->vettInv[i]);
        }
    }
    return NULL;
}

void scriviInventario(char *nomeFile, tabInv_t *inv, char *chiave){
    FILE *fout;
    inv_t *item;
    stat_t stat;
    if (strcmp(nomeFile, "stdout")==0)
        fout=stdout;
    else
        fout = fopen("oggetto.txt", "w");

    item = cercaOggettoN(inv, chiave);
    stat = item->stat;
    printf("%s %s ", item->nome, item->tipo);
    printf("%d %d %d %d %d %d\n", stat.hp, stat.mp, stat.atk, stat.def, stat.mag, stat.spr);
}