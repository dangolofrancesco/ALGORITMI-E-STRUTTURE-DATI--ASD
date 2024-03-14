#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 50
#define MAXD 10

typedef struct {
    int giorno;
    int mese;
    int anno;
}data_t;

typedef struct{
    char codice[MAX];
    char nome[MAX];
    char cognome[MAX];
    char data_str[MAXD];
    char via[MAX];
    char citta[MAX];
    int cap;
    data_t data;
}Item;

typedef struct node *link;

struct node{
    Item val;
    link next;
};

void tabella_comd();
link menu(link h);

link newNode(Item val, link next);
link sortIns(link h, Item val);

data_t DATAget(Item val);
int DATAgreater(data_t k1, data_t k2);
char *CODEget(Item d);
void ITEMstampa(Item val);
Item ITEMsetVoid();
int CODEeq(char k1[MAX], char k2[MAX]);
int DATAcomapre(char k1[MAX], char k2[MAX], Item d);

FILE *aperturaFile();
link letturaFile(link h, FILE *fp, int *n);
link letturaTastiera(link h, int *n);
Item ricerca(link h, char code[MAX]);
void stampa(link h, FILE *fpout);
Item estrazioneCodice(link *hp, char code[MAX]);
Item estrazioneData(link *h, char k1[MAX], char k2[MAX]);

int main() {
    int i;
    link head=NULL;
    head = menu(head);
}

void tabella_comd(){
    printf("Tabella comandi:\n"
           "1. Acquisizione ed inserimento ordinato di un nuovo elemento in lista (da tastiera)\n"
           "2. Acquisizione ed inserimento ordinato di nuovi elementi in lista (da file)\n"
           "3. Ricerca, per codice, di un elemento\n"
           "4. Cancellazione (con estrazione del dato) di un elemento dalla lista, previa ricerca per codice\n"
           "5. Cancellazione (con estrazione del dato) di tutti gli elementi con date comprese tra 2 date lette da tastiera\n"
           "6. Stampa della lista su file\n"
           "7. Fine\n");
    printf("Inserisci comando (numero): ");
}

link menu(link h){
    int cmd, continua=1;
    FILE *fp, *fout;
    char codice[MAX], filename[MAX], data1[MAX], data2[MAX];
    Item d;
    link x;
    int i, n;

    fp = aperturaFile();
    h = letturaFile(h, fp, &n);

    tabella_comd();
    scanf("%d", &cmd);
    if (isdigit(cmd)==1){
        printf("Comando non valido");
        exit(-1);
    }
    while (continua)
        switch (cmd) {
            case 1:
                h = letturaTastiera(h, &n);
                printf("\n");
                stampa(h, stdout);
                continua = 0;
                break;
            case 2:
                fp = aperturaFile();
                h = letturaFile(h, fp, &n);
                if (h==NULL)
                    printf("Errore 1");
                printf("\nOrdinamento per data: \n");
                stampa(h, stdout);
                continua = 0;
                break;
            case 3:
                printf("\nInserisci chiave di ricerca (formato A****): ");
                scanf("%s", codice);
                d = ricerca(h, codice);
                if (strcmp(d.codice, "0")!=0){
                    ITEMstampa(d);
                }else
                    printf("Codice non trovato");
                break;
            case 4:
                printf("\nInserisci chiave di ricerca (formato A****): ");
                scanf("%s", codice);
                d = estrazioneCodice(&h, codice);
                if (strcmp(d.codice, "0")!=0){
                    ITEMstampa(d);
                } else
                    printf("Codice non trovato");
                printf("\n");
                stampa(h, stdout);
                break;
            case 5:
                printf("Inserisci date:\n");
                printf("Data 1 (gg/mm/aaaa): ");
                scanf("%s", data1);
                printf("Data 2 (gg/mm/aaaa): ");
                scanf("%s", data2);
                for (i=0; i<n;i++){
                    d = estrazioneData(&h, data1, data2);
                    printf("Date trovate: \n");
                    ITEMstampa(d);
                    printf("\n Lista con estrazioni:\n");
                    stampa(h, stdout);
                    printf("\n");
                }
                break;
            case 6:
                printf("Inserisci file di output: ");
                scanf("%s", filename);
                fout = fopen(filename, "w");
                stampa(h, fout);
            case 7:
                continua = 0;
                break;
            default:
                tabella_comd();
                break;
    }
}


// FUNZIONI SU LISTA
link newNode(Item val, link next){
    link x=(link) malloc(sizeof(*x));
    if (x==NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}

link sortIns(link h, Item val){
    link x, p;
    data_t k = DATAget(val);
    //Inserimento in testa
    if (h==NULL || DATAgreater(DATAget(h->val), k))
        return newNode(val, h);

    //Cerca posizione
    for (x=h->next, p=h; x!=NULL && DATAgreater(k, DATAget(x->val)); p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}

// FUNZIONI SU ITEM
data_t DATAget(Item val){
    return val.data;
}

int DATAgreater(data_t k1, data_t k2){
    if (k1.anno>k2.anno)
        return 1;
    else if (k1.anno==k2.anno) {
        if (k1.mese>k2.mese)
            return 1;
        else if (k1.mese==k2.mese){
            if (k1.giorno>k2.giorno)
                return 1;
        }
    }
    return 0;
}

char *CODEget(Item d){
    return d.codice;
}

void ITEMstampa(Item val){
    printf("%s %s %s %d/%d/%d %s %s %d\n", val.codice, val.nome, val.cognome,
           val.data.giorno, val.data.mese, val.data.anno,
           val.via, val.citta, val.cap);
}

int CODEeq(char k1[MAX], char k2[MAX]){
    return strcmp(k1, k2);
}

Item ITEMsetVoid(){
    Item d;
    strcpy(d.codice, "0");
    return d;
}

int DATAcomapre(char k1[MAX], char k2[MAX], Item d){
    data_t d1, d2;
    sscanf(k1, "%d/%d/%d", &d1.giorno, &d1.mese, &d1.anno);
    sscanf(k2, "%d/%d/%d", &d2.giorno, &d2.mese, &d2.anno);
    if (d.data.anno>d1.anno && d.data.anno<d2.anno) {
        return 1;
    }
    else if (d.data.anno==d1.anno ) {
        if (d.data.mese > d1.mese) {
            return 1;
        }
        else if (d.data.mese == d1.mese) {
            if (d.data.giorno > d1.giorno)
                return 1;
        }
    }
    else if (d.data.anno==d2.anno) {
        if (d.data.mese < d2.mese) {
            return 1;
        }
        else if (d.data.mese == d1.mese) {
            if (d.data.giorno < d2.giorno)
                return 1;
        }
    }
    return 0;
}


//FUNZIONI COMANDO
// lettura(File *fp, link), chiamata in case 1 : lettura(stdin, h)
FILE *aperturaFile(){
    FILE *fp;
    char filename[MAX];
    /*printf("Inserisci nome file: ");
    scanf("%s", filename);*/
    fp = fopen("../anag1.txt", "r");
    if (fp==NULL)
        printf("Errore");
    return fp;
}

link letturaFile(link h, FILE *fp, int *n){
    int i;
    Item d;
    if (fp==NULL){
        printf("Errore");
        return NULL;
    }
    for (i=0; (fscanf(fp," %s%s%s%s%s%s %d", d.codice, d.nome, d.cognome, d.data_str, d.via, d.citta, &d.cap))== 7; i++){
        sscanf(d.data_str, "%d/%d/%d", &d.data.giorno, &d.data.mese, &d.data.anno);
        h = sortIns(h, d);
    }
    *n = i;
    return h;
}

link letturaTastiera(link h, int *n){
    int i;
    Item d;

    printf("Quanti dati vuoi inserire?: ");
    scanf("%d", n);
    for (i=0; i<(*n); i++){
        printf("Inserisci dati (seguiti da spazio): ");
        scanf("%s%s%s%s%s%s %d", d.codice, d.nome, d.cognome, d.data_str, d.via, d.citta, &d.cap);
        sscanf(d.data_str, "%d/%d/%d", &d.data.giorno, &d.data.mese, &d.data.anno);
        h = sortIns(h, d);
    }
    return h;
}
void stampa(link h, FILE *fpout){
    link x;
    for (x=h; x!=NULL; x=x->next)
        printf("%s %s %s %d/%d/%d %s %s %d\n", x->val.codice,x->val.nome, x->val.cognome,
               x->val.data.giorno, x->val.data.mese, x->val.data.anno,
               x->val.via, x->val.citta, x->val.cap);
}

Item ricerca(link h, char code[MAX]){
    link x;
    for (x=h; x->next!=NULL; x=x->next){
        if (CODEeq(CODEget(x->val), code)==0) {
            return x->val;
        }
    }
    return ITEMsetVoid();
}

Item estrazioneCodice(link *hp, char code[MAX]){
    link *xp, t;
    Item i = ITEMsetVoid();
    for (xp=hp; xp!=NULL; xp= &((*xp)->next)){
        if (CODEeq(CODEget((*xp)->val), code)==0){
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

Item estrazioneData(link *h, char k1[MAX], char k2[MAX]){
    link *xp, t;
    Item i = ITEMsetVoid();
    for (xp=h; xp!=NULL; xp= &((*xp)->next)){
        if (DATAcomapre(k1, k2, (*xp)->val)){
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}