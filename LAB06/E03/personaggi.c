//
// Created by Francesco D'Angolo on 25/11/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggi.h"


tabPg_t *allocaPg(){
    tabPg_t *pg = (tabPg_t*) malloc(sizeof (tabPg_t));
    pg->head = NULL;
    pg->tail = NULL;
    pg->nPg = 0;
    return pg;
}

void freePg(linkPg pg){
    int i;
    free(pg->campi.codice);
    free(pg->campi.nome);
    free(pg->campi.classe);
}

void liberaPg(tabPg_t *pg){
    linkPg p, q;
    for (p=pg->head; p!=NULL; p=q){
        q = p->next;
        freePg(p);
        free(p);
    }
    free(pg);
}

linkPg newNode(linkPg next, pg_t campi){
    linkPg x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    x->campi = campi;
    x->next = next;
    return x;
}

void listInTail(tabPg_t *tab, pg_t pg){
    linkPg x;
    x = newNode(NULL, pg);
    if (x==NULL)
        return;
    if (tab->head == NULL)
        tab->head = tab->tail = x;
    else{
        tab->tail->next = x;
        tab->tail = x;
    }
}

int leggiPg(FILE *fp, pg_t *pg){
    int check=0, i;
    char codice[MAX], nome[MAX], classe[MAX];
    if (fscanf(fp, "%s", codice)==1){
        if (strcmp(codice, "fine")==0)
            return 0;
        fscanf(fp, "%s %s", nome, classe);
        pg->codice = strdup(codice);
        pg->nome = strdup(nome);
        pg->classe = strdup(classe);
        fscanf(fp, "%d %d %d %d %d %d", &pg->stat.hp, &pg->stat.mp, &pg->stat.atk, &pg->stat.def, &pg->stat.mag, &pg->stat.spr);
        check=1;
    }
    pg->equip.inUso=0;
    for (i=0; i<MAXEQ; i++)
        pg->equip.vettEq[i] = NULL;
    return check;
}

FILE *aperturaFile(char *nomeFile){
    FILE *fp = fopen(nomeFile, "r");;
    if (fp==NULL){
        exit(1);
    }
    return fp;
}

int insertPg(char *nomeFile, tabPg_t *tabPg){
    pg_t pg;
    FILE *fp;
    int nPg=tabPg->nPg;

    if (strcmp(nomeFile, "stdin")==0){
        fp = stdin;
    } else{
        fp = aperturaFile(nomeFile);
    }

    if (fp==stdin){
        printf("Inserisci dati personaggio (fine per terminare):\n");
        printf("Codice Nome Classe Stat: hp mp atk def mag spr\n");
    }

    while (leggiPg(fp, &pg)){
        listInTail(tabPg, pg);
        nPg++;
    }

    if (fp!=stdin)
        fclose(fp);
}

void deletePg(tabPg_t *tabPg){
    linkPg x, p;
    int found=0;
    char codice[MAX];
    printf("\nInserisci codice personaggio da eliminare: ");
    scanf("%s", codice);

    if (tabPg->head == NULL)
        return;
    for (x=tabPg->head, p=NULL; x!=NULL; p=x, x=x->next){
        if (strcmp(x->campi.codice, codice)==0){
            found=1;
            if (x==tabPg->head)
                tabPg->head = x->next;
            else if (x==tabPg->tail)
                tabPg->tail = p;
            else{
                p->next = x->next;
            }
            freePg(x);
            free(x);
            break;
        }
    }
    if (found==0){
        printf("Codice inserito non valido");
        return;
    }
}

linkPg ricerca(tabPg_t *tabPg, char *codice){
    linkPg x;
    if (tabPg->head==NULL)
        return NULL;
    for (x=tabPg->head; x!=NULL; x=x->next){
        if (strcmp(x->campi.codice, codice)==0){
            return x;
        }
    }
    return NULL;
}

void calcolaStat(linkPg pg){
    int i;
    stat_t statEq;

    for (i=0; i<MAXEQ; i++){
        if (pg->campi.equip.vettEq[i]!=NULL){
            statEq = pg->campi.equip.vettEq[i]->stat;
            pg->campi.stat.hp += statEq.hp;
            pg->campi.stat.mp += statEq.mp;
            pg->campi.stat.atk += statEq.atk;
            pg->campi.stat.def += statEq.def;
            pg->campi.stat.mag += statEq.mag;
            pg->campi.stat.spr += statEq.spr;
        }
    }
}

void stampaEq(tabInv_t *tabInv, linkPg x){
    int i;
    printf("Oggetti equipaggiati per %s:\n", x->campi.nome);
    for (i=0; i<MAXEQ; i++){
        if (x->campi.equip.vettEq[i]!=NULL){
            scriviInventario(stdout, tabInv, x->campi.equip.vettEq[i]->nome);
        }
    }
}

void aggiungiEq(tabPg_t *tabPg, tabInv_t *tabInv){
    char codice[MAX], item[MAX];
    int i;

    printf("Inserisci codice personaggio: ");
    scanf("%s", codice);

    linkPg x;
    x = ricerca(tabPg, codice);

    if (x->campi.equip.inUso>=MAXEQ){
        printf("Raggiunto il numero massimo di oggetti per questo personaggio.\n"
               "Rimuovi oggetti per aggiungerne altri.");
    }

    printf("\nInventario:\n");
    for (i=0; i<tabInv->nInv; i++){
        strcpy(item, tabInv->vettInv[i].nome);
        scriviInventario("stdout", tabInv, item);
    }

    printf("\nScegli oggetto da equipaggiare: ");
    scanf("%s", item);
    inv_t *oggetto = cercaOggettoN(tabInv, item);
    for (i=0; i<MAXEQ; i++){
        if (x->campi.equip.vettEq[i]==NULL){
            x->campi.equip.vettEq[i] = oggetto;
            x->campi.equip.inUso++;
            break;
        }
    }

    stampaEq(tabInv, x);
}

void rimuoviEq(tabPg_t *tabPg, tabInv_t *tabInv){
    char codice[MAX], item[MAX];
    int i;

    printf("Inserisci codice personaggio: ");
    scanf("%s", codice);

    linkPg x;
    x = ricerca(tabPg, codice);

    if (x->campi.equip.inUso==0){
        printf("Non c'è alcun oggetto da rimuovere.");
        return;
    }

    stampaEq(tabInv, x);
    printf("\nScegli oggetto da rimuovere dall'equipaggiamento: ");
    scanf("%s", item);
    inv_t *oggetto = cercaOggettoN(tabInv, item);
    for (i=0; i<MAXEQ; i++){
        if (x->campi.equip.vettEq[i]==oggetto){
            x->campi.equip.vettEq[i] = NULL;
            x->campi.equip.inUso--;
            break;
        }
    }
    stampaEq(tabInv, x);
}

void stampaPg(linkPg pg){
    pg_t p = pg->campi;
    stat_t stat = pg->campi.stat;
    printf("%s %s %s", p.codice, p.nome, p.classe);
    printf("%d %d %d %d %d %d\n", stat.hp, stat.mp, stat.atk, stat.def, stat.mag, stat.spr);
}