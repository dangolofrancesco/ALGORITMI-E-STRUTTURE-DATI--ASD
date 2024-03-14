//LAB02 ES_03 - FRANCESCO PIO D'ANGOLO 295068
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "../corse.txt"
#define MAX 31

typedef struct{
    char codice[MAX];
    char staz_partenza[MAX];
    char staz_arrivo[MAX];
    char data_str[MAX];
    char orap_str[MAX];
    char oraArr_str[MAX];
}corse_tmp;

typedef struct{
    char *codice;
    char *staz_partenza;
    char *staz_arrivo;
    char *data_str;
    char *orap_str;
    char *oraArr_str;
    int ritardo;
}corse_t;

typedef struct{
    corse_t *tab1;
    corse_t *tab2;
    corse_t *tab3;
    corse_t *tab4;
}rif_t;

typedef enum{c_stampa, c_ordinamento, c_ricerca, c_file, c_fine}comando_e;

typedef enum{o_data, o_codice, o_stazP, o_stazA, o_fine}ordinamento_e;

int apertura_file(FILE **fp, char filename[MAX]);
void malloc1d(FILE *fp, corse_t **v, int n);
void free1d(corse_t *v, int n);
void stampComandi(char comandi[][MAX], int n);
void stampaVoci(corse_t *tab, int n);
corse_t *nuovo_file(corse_t *tab, int n);
char *strToLower(char str[]);
comando_e leggi_comando(char tab[][MAX]);
int menuComandi(corse_t *tab, int n, rif_t rif);
void cmd_stampa(corse_t *tab, int n);
ordinamento_e leggi_ord(char tab[][MAX]);
void menuOrdinamento(corse_t *tab, int n, rif_t rif);
void ordina_data(corse_t *tab, int n);
void ordina_codice(corse_t *tab, int n);
void ordina_partenza(corse_t *tab, int n);
void ordina_arrivo(corse_t *tab, int n);
void binary(corse_t *tab, int n);
int ricercaBinaria(corse_t *tab, int l, int r, char s[MAX]);
void ricercaLineare(corse_t *tab, int n, char s[MAX]);

int main() {
    FILE *fp;
    int n = apertura_file(&fp, FILENAME);
    corse_t *tab;
    rif_t rif;
    malloc1d(fp, &tab,n);
    //assegno a ogni puntatore la stessa inizializzazione di tab
    rif.tab1=rif.tab2=rif.tab3=rif.tab4=tab;
    menuComandi(tab, n, rif);
    free1d(tab,n);
}

int apertura_file(FILE **fp, char filename[MAX]){
    int n;
    FILE *fp1 = fopen(filename, "r");
    if (fp1==NULL)
        return -1;
    if (fscanf(fp1, "%d", &n)!=1)
        return -1;
    *fp = fp1;
    return n;
}

void malloc1d(FILE *fp, corse_t **v, int n){
    int i, j;
    corse_t *v1;
    corse_tmp v2;
    v1 = (corse_t *) malloc(n* sizeof(corse_t));
    if (v1==NULL)
        exit(-1);
    for (i=0;i<n;i++){
        fscanf(fp,"%s %s %s %s %s %s %d", v2.codice, v2.staz_partenza, v2.staz_arrivo, v2.data_str,
               v2.orap_str, v2.oraArr_str, &v1[i].ritardo);
        v1[i].codice = (char *) malloc((strlen(v2.codice))*sizeof (char ));
        strcpy(v1[i].codice, v2.codice);
        v1[i].staz_partenza = (char *) malloc((strlen(v2.staz_partenza))*sizeof (char ));
        strcpy(v1[i].staz_partenza, v2.staz_partenza);
        v1[i].staz_arrivo = (char *) malloc((strlen(v2.staz_arrivo))*sizeof (char ));
        strcpy(v1[i].staz_arrivo, v2.staz_arrivo);
        v1[i].data_str = (char *) malloc((strlen(v2.data_str))*sizeof (char ));
        strcpy(v1[i].data_str, v2.data_str);
        v1[i].orap_str = (char *) malloc((strlen(v2.orap_str))*sizeof (char ));
        strcpy(v1[i].orap_str, v2.orap_str);
        v1[i].oraArr_str = (char *) malloc((strlen(v2.oraArr_str))*sizeof (char ));
        strcpy(v1[i].oraArr_str, v2.oraArr_str);
    }
    *v = v1;
    fclose(fp);
}

void free1d(corse_t *v, int n){
    int i;
    for (i=0;i<n;i++){
        free(v[i].codice);
        free(v[i].staz_partenza);
        free(v[i].staz_arrivo);
        free(v[i].data_str);
        free(v[i].orap_str);
        free(v[i].oraArr_str);
    }
    free(v);
}

comando_e leggi_comando(char tab[][MAX]){
    char comando[MAX];
    int i;
    printf("Scegli comando: ");
    scanf("%s", comando);

    for (i=0;i<=c_fine;i++){
        if (strcmp(strToLower(comando), tab[i])==0)
            return (comando_e) i;
    }
}

int menuComandi(corse_t *tab, int n, rif_t rif){
    int i, continua = 1, indice;
    comando_e cmd;
    char comandi[][MAX] = {"stampa", "ordina", "ricerca", "file","fine"};

    stampComandi(comandi, c_fine);
    do {
        cmd = leggi_comando(comandi);
        switch (cmd) {
            case c_stampa:
                cmd_stampa(tab, n);
                break;
            case c_ordinamento:
                menuOrdinamento(tab, n, rif);
                break;
            case c_ricerca:
                binary(tab, n);
                break;
            case c_file:
                tab = nuovo_file(tab, n);
                rif.tab1 = rif.tab2 = rif.tab3 = rif.tab4 = tab;
                stampaVoci(tab, n);
                break;
            case c_fine:
                continua = 0;
                break;
            default:
                stampComandi(comandi, c_fine);
        }
    } while (continua);
    return 0;
}

void stampComandi(char comandi[][MAX], int n){
    int i;
    printf("Tabella comandi:\n");
    for (i=0; i<=n;i++){
        printf("%d.%s\n", i+1, comandi[i]);
    }
}

corse_t *nuovo_file(corse_t *tab, int n){
    FILE *fp;
    int n_new;
    char filename[MAX];
    free1d(tab,n);
    printf("Nome file: ");
    scanf("%s", filename);
    n_new = apertura_file(&fp, filename);
    malloc1d(fp, &tab, n_new);
    return tab;
}

char *strToLower(char *s){
    int i;
    int lun_s = strlen(s);
    for (i=0;i<lun_s;i++){
        s[i] = tolower(s[i]);
    }
    return s;
}

void cmd_stampa(corse_t *tab, int n){
    int i;
    char input;
    printf("Stampare su video(V) o file(F): ");
    scanf(" %c", &input);
    input = tolower(input);

    if (input == 'v'){
        printf("\nElenco corse disponibili:\n");
        for (i=0;i<n;i++)
            printf("%s %s %s %s %s\n",tab[i].codice, tab[i].staz_partenza, tab[i].staz_arrivo, tab[i].data_str, tab[i].orap_str);
        printf("\n");
    }
    else if (input == 'f'){
        FILE *fpout = fopen("../FILE_OUT", "w");
        fprintf(fpout, "\nElenco corse disponibili:\n");
        for (i=0;i<n;i++)
            fprintf(fpout, "%s %s %s %s %s\n",tab[i].codice, tab[i].staz_partenza, tab[i].staz_arrivo, tab[i].data_str, tab[i].orap_str);
        printf("\n");
        fclose(fpout);
    }
}

ordinamento_e leggi_ord(char tab[][MAX]){
    char comando[MAX];
    int i;
    printf("Scegli comando: ");
    scanf("%s", comando);

    for (i=0;i<=o_fine;i++){
        if (strcmp(strToLower(comando), tab[i])==0)
            return (ordinamento_e) i;
    }
}

void menuOrdinamento(corse_t *tab, int n, rif_t rif){
    int i, continua=1;
    ordinamento_e cmd;
    char tab_comandi[][MAX] = {"data", "codice", "partenza", "arrivo", "fine"};

    stampComandi(tab_comandi, o_fine);
    do {
        cmd = leggi_ord(tab_comandi);
        switch (cmd) {
            case o_data:
                ordina_data(rif.tab1, n);
                break;
            case o_codice:
                ordina_codice(rif.tab2, n);
                break;
            case o_stazP:
                ordina_partenza(rif.tab3, n);
                break;
            case o_stazA:
                ordina_arrivo(rif.tab4, n);
                break;
            case o_fine:
                continua=0;
                break;
            default:
                stampComandi(tab_comandi, o_fine);

        }
    } while (continua);
    return;
}

//FUNZIONE ORDINAMENTO PER DATA (eventualmente per ora)
//UTILIZZO DI INSERTION SORT PER STABILITA' ALGORITMICA
void ordina_data(corse_t *tab, int n) {
    int i,j;
    corse_t tmp;
    printf("\nCorse ordinate per data:\n\n");
    for (i=1;i<n;i++){
        tmp = tab[i];
        j = i-1;
        while (j>=0 && ((strcmp(tmp.data_str,tab[j].data_str)<0) || ((strcmp(tmp.data_str,tab[j].data_str)==0) && (strcmp(tmp.orap_str,tab[j].orap_str)<0)))){
            tab[j+1] = tab[j];
            j--;
        }
        tab[j+1] = tmp;
    }
    stampaVoci(tab, n);
}

//FUNZIONE ORDINAMENTO PER CODICE TRATTA
//UTILIZZO DI BUBBLE SORT
void ordina_codice(corse_t *tab, int n){
    int i,j;
    corse_t tmp;
    printf("\nCorse ordinate per codice:\n\n");
    for (i=0;i<n-1;i++){
        for (j=0;j<n-1-i;j++){
            if (strcmp(tab[j].codice,tab[j+1].codice)>0){
                tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
            }
        }
    }
    stampaVoci(tab, n);
}

//FUNZIONE ORDINAMENTO PER STAZIONE DI PARTENZA
void ordina_partenza(corse_t *tab, int n){
    int i,j;
    corse_t tmp;
    printf("\nCorse ordinate per stazione di partenza:\n\n");
    for (i=0;i<n-1;i++){
        for (j=0;j<n-1-i;j++){
            if (strcmp(tab[j].staz_partenza,tab[j+1].staz_partenza)>0){
                tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
            }
        }
    }
    stampaVoci(tab, n);
}

//FUNZIONE ORDINAMENTO PER STAZIONE DI ARRIVO
void ordina_arrivo(corse_t *tab, int n) {
    int i, j;
    corse_t tmp;
    printf("\nCorse ordinate per stazione di arrivo:\n\n");
    for (i=0;i<n-1;i++){
        for (j=0;j<n-1-i;j++){
            if (strcmp(tab[j].staz_arrivo,tab[j+1].staz_arrivo)>0){
                tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
            }
        }
    }
    stampaVoci(tab, n);
}

void binary(corse_t *tab, int n){
    char stazione[MAX];
    //ordinamento vettore
    int i,j;
    corse_t tmp;
    for (i=0;i<n-1;i++){
        for (j=0;j<n-1-i;j++){
            if (strcmp(tab[j].staz_partenza,tab[j+1].staz_partenza)>0){
                tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
            }
        }
    }
    int indice;
    //inserimento chiave di confronto
    printf("Inserisci stazione: ");
    scanf("%s", stazione);
    //indice = ricercaBinaria(tab,0,n-1, stazione);
    //printf("%s", tab[indice].staz_partenza);
    ricercaLineare(tab, n, strToLower(stazione));
}

int ricercaBinaria(corse_t *tab, int l, int r, char s[MAX]){
    int m;
    if (l>r)
        return -1;
    m = (l+r)/2;
    if (strstr(strToLower(tab[m].staz_partenza), strToLower(s))!=NULL)
        return m;
    if (strcmp(strToLower(tab[m].staz_partenza), strToLower(s))<0)
        return ricercaBinaria(tab, l, m-1, s);
    return ricercaBinaria(tab, m+1, r, s);
}

void ricercaLineare(corse_t *tab, int n, char s[MAX]){
    int i;
    for (i=0;i<n;i++){
        if (strstr(strToLower(tab[i].staz_partenza), strToLower(s))!=NULL){
            printf("%s\n", tab[i].staz_partenza);
        }
    }
}

void stampaVoci(corse_t *tab, int n){
    int i;
    for (i=0;i<n;i++)
        printf("%s %s %s %s %s\n",tab[i].codice, tab[i].staz_partenza, tab[i].staz_arrivo, tab[i].data_str, tab[i].orap_str);
    printf("\n");
}