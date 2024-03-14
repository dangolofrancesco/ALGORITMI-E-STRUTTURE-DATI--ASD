//
// Modulo inventario - header
//

#ifndef E03_INVENTARIO_H
#define E03_INVENTARIO_H

#define MAX 50

typedef struct {
    int hp, mp, atk, def, mag, spr;
}stat_t;

typedef struct{
    char nome[MAX];
    char tipo[MAX];
    stat_t stat;
}inv_t;

typedef struct {
    inv_t *vettInv;
    int nInv;
    int maxInv;
}tabInv_t;


tabInv_t *allocaInventario(int n);
void liberaInventario(tabInv_t *inv);

tabInv_t *leggiInventario(char *nomeFile);
inv_t *cercaOggettoN(tabInv_t *inv, char *chiave);
void scriviInventario(char *nomeFile, tabInv_t *inv, char *chaive);

#endif //E03_INVENTARIO_H
