#include <stdio.h>

#include "titoli.h"
#define MAXL 20

void leggiFile(char *scr, titoli_t list){
    FILE *fp = fopen(scr, "r");
    char data_s[MAXL], ora_s[MAXL], titolo[MAXL];
    int i, n, k, j, qta;
    float val;
    titolo_t tit;

    fscanf(fp, "%d", &n);
    list = LISTinit();
    for (i=0; i<n; i++){
        fscanf(fp, "%s%d", titolo, &k);
        LISTins(list, titolo);
        for (j=0; j<k; j++){
            //inserimento quotazione
            tit = LISTAgetTitolo(list, titolo);
            fscanf(fp, "%s %s %f %d", data_s, ora_s, &val, &qta);
            BSTinsertLeaf(DATAload(data_s), val, qta, TITOLOgetBst(tit));
            //BSTvisit(stdout, TITOLOgetBst(tit));
        }
    }



}

int main() {
    FILE *fp;
    fp = fopen("../F3.txt", "r");
    data_t data1, data2;
    data_t data_min, data_max;
    char titolo[20], dataS1[30], dataS2[20], oras[30];

    float val;
    int qta;

    titolo_t tit;
    titoli_t list;
    int i, n, k, j;
    fscanf(fp, "%d", &n);
    list = LISTinit();
    for (i=0; i<n; i++){
        fscanf(fp, "%s%d", titolo, &k);
        LISTins(list, titolo);
        for (j=0; j<k; j++){
            //inserimento quotazione
            tit = LISTAgetTitolo(list, titolo);
            fscanf(fp, "%s %s %f %d", dataS1, oras, &val, &qta);
            BSTinsertLeaf(DATAload(dataS1), val, qta, TITOLOgetBst(tit));
            //BSTvisit(stdout, TITOLOgetBst(tit));
        }
    }

    LISTstore(stdout, list);

    //ricerca titolo da BST
    float max=0, min=100;
    quotazione_t q;
    printf("Titolo: ");
    scanf("%s", titolo);
    printf("Data 1: ");
    scanf("%s", dataS1);
    printf("Data 2: ");
    scanf("%s", dataS2);
    data1 = DATAload(dataS1);
    data2 = DATAload(dataS2);
    tit = LISTAgetTitolo(list, titolo);
    //BSTmaxmin(TITOLOgetBst(tit), data1, data2, &max, &min);
    BSTmaxMinTot(TITOLOgetBst(tit), &max, &min);


    printf("%.2f %.2f", max, min);


}
