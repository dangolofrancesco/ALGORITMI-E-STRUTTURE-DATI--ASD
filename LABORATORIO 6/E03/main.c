#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "inventario.h"
#include "personaggi.h"

#define MAX 50

void stampaCmd(){
    printf("1. Aggiungi nuovo personaggio\n"
           "2. Elimina personaggio\n"
           "3. Aggiungi oggetto in equipaggiamento\n"
           "4. Rimuovi oggetto da equipaggiamento\n"
           "5. Calcola statistiche di un personaggio\n"
           "6. Stampa personaggi\n");
}
void menu(tabPg_t *tabPg, tabInv_t *tabInv){
    linkPg x;
    int cmd, continua=1;
    char codice[MAX];
    printf("Tabella comandi:\n");
    stampaCmd();

    printf("\nInserisci comando: ");
    scanf("%d", &cmd);
    if (isdigit(cmd)==1){
        printf("Comando non valido");
        exit(-1);
    }

    while (continua){
        switch (cmd) {
            case 1:
                tabPg->nPg = insertPg("stdin", tabPg);
                printf("Personaggio inserito: \n");
                stampaPg(tabPg->tail);
                continua=0;
                break;
            case 2:
                deletePg(tabPg);
                printf("Nuova lista personaggi\n");
                for (x=tabPg->head; x!=NULL; x=x->next)
                    stampaPg(x);
                continua=0;
                break;
            case 3:
                aggiungiEq(tabPg, tabInv);
                continua=0;
                break;
            case 4:
                rimuoviEq(tabPg, tabInv);
                continua=0;
                break;
            case 5:
                printf("Inserisci codice personaggio: ");
                scanf("%s", codice);
                x = ricerca(tabPg, codice);
                if (x==NULL){
                    printf("Codice inserito non valido");
                    continua=0;
                    break;
                }
                calcolaStat(x);
                continua=0;
                break;
            case 6:
                for (x=tabPg->head; x!=NULL; x=x->next){
                    printf("\n");
                    stampaPg(x);
                    stampaEq(tabInv, x);
                    printf("\n");
                }
                continua=0;
                break;
            case 7:
                continua=0;
                break;
            default:
                stampaCmd();
                break;
        }
    }

}
int main() {
    tabInv_t *tabInv;
    char filename[MAX] = "../inventario.txt";
    tabInv = leggiInventario(filename);

    tabPg_t *tabPg;
    tabPg = allocaPg();
    tabPg->nPg = insertPg("../pg.txt", tabPg);

    menu(tabPg, tabInv);
    liberaPg(tabPg);
    liberaInventario(tabInv);
}