//LAB01 ES_03 - FRANCESCO PIO D'ANGOLO 295068
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 31
#define FILENAME "../corse.txt"

typedef struct{
    int ora;
    int minuti;
    int secondi;
}orario_t;

typedef struct{
    int anno;
    int mese;
    int giorno;
}data_t;

typedef struct{
    char codice[MAX];
    char staz_partenza[MAX];
    char staz_arrivo[MAX];
    char data_str[MAX];
    char orap_str[MAX];
    char oraArr_str[MAX];
    int ritardo;
    data_t data;
    orario_t partenza, arrivo;
}corse_t;

typedef enum{c_stampa, c_ordinamento, c_ricerca, c_fine}comando_e;

typedef enum{o_data, o_codice, o_stazP, o_stazA, o_fine}ordinamento_e;

int apertura_file(FILE **fp);
void leggi_tabella(FILE *fp, corse_t *t1, int n);
char *strToLower(char v[]);
int menuComandi(corse_t **tab, int n);
comando_e leggi_comando(char tab[][MAX]);
void cmd_stampa(corse_t **tab, int n);
ordinamento_e leggi_ord(char tab[][MAX]);
void menuOrdinamento(corse_t **tab, int n);
void mergeSort(corse_t **tab1, int N);
void mergeSortR(corse_t **tab1, corse_t **tab2, int l, int r);
void merge_date(corse_t **tab1, corse_t **tab2, int l, int q, int r);
void ordina_codice(corse_t **tab1, int n);
void ordina_partenza(corse_t **tab1, int n);
void ordina_arrivo(corse_t **tab1, int n);
char *strToLower2(char s[]);
void binary(corse_t **tab, int n);
int ricercaBinaria(corse_t **tab, int l, int r, char s[MAX]);
void ricercaLineare(corse_t **tab, int n, char s[MAX]);

int main() {
    FILE *fp;
    corse_t tabella[MAX], **tabella_p;
    int n, i;

    n = apertura_file(&fp);
    leggi_tabella(fp,tabella, n);

    for (i=0;i<n;i++)
        tabella_p[i] = &tabella[i];

    menuComandi(tabella_p, n);
}
int apertura_file(FILE **fp){
    int n;
    FILE *fp1 = fopen(FILENAME, "r");
    if (fp1==NULL)
        return -1;
    fscanf(fp1, "%d", &n);
    *fp = fp1;
    return n;
}

void leggi_tabella(FILE *fp, corse_t *t1, int n){
    int i;
    for (i=0;i<n;i++) {
        fscanf(fp, "%s%s%s%s%s%s%d", t1[i].codice, t1[i].staz_partenza, t1[i].staz_arrivo,
               t1[i].data_str, t1[i].orap_str, t1[i].oraArr_str, &t1[i].ritardo);
        sscanf(t1[i].data_str, "%d/%d/%d", &t1[i].data.anno, &t1[i].data.giorno, &t1[i].data.mese);
        sscanf(t1[i].orap_str, "%d:%d:%d", &t1[i].partenza.ora, &t1[i].partenza.minuti, &t1[i].partenza.secondi);
        sscanf(t1[i].oraArr_str, "%d:%d:%d", &t1[i].arrivo.ora, &t1[i].arrivo.minuti, &t1[i].arrivo.secondi);
    }
    fclose(fp);
}

comando_e leggi_comando(char tab[][MAX]){
    char comando[MAX];
    int i;
    printf("Scegli comando: ");
    scanf("%s", comando);

    for (i=0;i<c_fine;i++){
        if (strcmp(strToLower(comando), tab[i])==0)
            return (comando_e) i;
    }
}

int menuComandi(corse_t **tab, int n){
    int i, continua = 1, indice;
    comando_e cmd;
    char stazione[MAX];
    char comandi[][MAX] = {"stampa", "ordina", "ricerca", "fine"};
    printf("Tabella comandi:\n");
    for (i=0; i<c_fine+1;i++){
        printf("%d.%s\n", i+1, comandi[i]);
    }
    do {
        cmd = leggi_comando(comandi);
        switch (cmd) {
            case c_stampa:
                cmd_stampa(tab, n);
                return 0;
            case c_ordinamento:
                menuOrdinamento(tab, n);
                return 0;
            case c_ricerca:
                binary(tab, n);
                return 0;
            case c_fine:
                continua = 0;
                return 0;
        }
    }while (continua);
        return 0;
}

char *strToLower(char parola[]){
    int i;
    char v[strlen(parola)];
    strcpy(v,parola);
    for (i=0;i< strlen(v);i++)
        v[i] = tolower(v[i]);
    return v;
}

void cmd_stampa(corse_t **tab, int n){
    int i;
    char input;
    printf("Stampare su video(V) o file(F): ");
    scanf(" %c", &input);
    input = tolower(input);

    if (input == 'v'){
        printf("\nElenco corse disponibili:\n");
        for (i=0;i<n;i++)
            printf("%s %s %s %s %s\n",tab[i]->codice, tab[i]->staz_partenza, tab[i]->staz_arrivo, tab[i]->data_str, tab[i]->orap_str);
        printf("\n");
    }
    else if (input == 'f'){
        FILE *fpout = fopen("../FILE_OUT", "w");
        fprintf(fpout, "\nElenco corse disponibili:\n");
        for (i=0;i<n;i++)
            fprintf(fpout, "%s %s %s %s %s\n",tab[i]->codice, tab[i]->staz_partenza, tab[i]->staz_arrivo, tab[i]->data_str, tab[i]->orap_str);
        printf("\n");
        fclose(fpout);
    }
}

ordinamento_e leggi_ord(char tab[][MAX]){
    char comando[MAX];
    int i;
    printf("Scegli comando: ");
    scanf("%s", comando);

    for (i=0;i<o_fine;i++){
        if (strcmp(strToLower(comando), tab[i])==0)
            return (ordinamento_e) i;
    }
}

void menuOrdinamento(corse_t **tab, int n){
    int i;
    ordinamento_e cmd;
    char tab_comandi[][MAX] = {"data", "codice", "partenza", "arrivo", "fine"};
    printf("\nTabella ordinamenti:\n");
    for (i=0;i<o_fine;i++)
        printf("%d.%s\n",i+1,tab_comandi[i]);
    cmd = leggi_ord(tab_comandi);

    switch (cmd) {
        case o_data:
            mergeSort(tab, n);
            return;
        case o_codice:
            ordina_codice(tab, n);
            return;
        case o_stazP:
            ordina_partenza(tab, n);
            return;
        case o_stazA:
            ordina_arrivo(tab, n);
            return;
        case o_fine:
            return;
    }
}

//FUNZIONE ORDINAMENTO PER DATA (eventualmente per ora)
void mergeSort(corse_t **tab1, int N){
    int l=0, r=N-1, i;
    corse_t *tab2[MAX];
    mergeSortR(tab1, tab2, l, r);
    printf("\nCorse ordinate per data:\n\n");
    for (i=0; i<=r;i++)
        printf("%s %s %s %s %s %s\n", tab1[i]->codice, tab1[i]->staz_partenza, tab1[i]->staz_arrivo, tab1[i]->data_str, tab1[i]->orap_str, tab1[i]->oraArr_str);
}

void mergeSortR(corse_t **tab1, corse_t **tab2, int l, int r){
    int q;
    if (l>=r)
        return;

    q = (l+r)/2;
    mergeSortR(tab1, tab2, l, q);
    mergeSortR(tab1, tab2, q+1, r);
    merge_date(tab1, tab2, l, q, r);
}

void merge_date(corse_t **tab1, corse_t **tab2, int l, int q, int r){
    int i, j, k;
    i = l;
    j = q+1;
    for (k=l;k<=r;k++){
        if (i>q)
            tab2[k] = tab1[j++];
        else if (j>r)
            tab2[k] = tab1[i++];
        else if ((strcmp(tab1[i]->data_str, tab1[j]->data_str)<0) || ((strcmp(tab1[i]->data_str, tab1[j]->data_str)==0) && (strcmp(tab1[i]->orap_str, tab1[j]->orap_str)<0)))
            tab2[k] = tab1[i++];
        else
            tab2[k] = tab1[j++];
    }
    for (k=l; k<=r; k++)
        tab1[k] = tab2[k];
    return;
}

//FUNZIONE ORDINAMENTO PER CODICE TRATTA
//UTILIZZO DI BUBBLE SORT
void ordina_codice(corse_t **tab1, int n){
    int i,j;
    corse_t *tmp;
    printf("\nCorse ordinate per codice:\n\n");
    for (i=0;i<n-1;i++){
        for (j=0;j<n-1-i;j++){
            if (strcmp(tab1[j]->codice,tab1[j+1]->codice)>0){
                tmp = tab1[j];
                tab1[j] = tab1[j+1];
                tab1[j+1] = tmp;
            }
        }
    }
    for (i=0;i<n;i++)
        printf("%s %s %s %s %s\n",tab1[i]->codice, tab1[i]->staz_partenza, tab1[i]->staz_arrivo, tab1[i]->data_str, tab1[i]->orap_str);
    printf("\n");
}

//FUNZIONE ORDINAMENTO PER STAZIONE DI PARTENZA
void ordina_partenza(corse_t **tab1, int n){
    int i,j;
    corse_t *tmp;
    printf("\nCorse ordinate per stazione di partenza:\n\n");
    for (i=0;i<n-1;i++){
        for (j=0;j<n-1-i;j++){
            if (strcmp(tab1[j]->staz_partenza,tab1[j+1]->staz_partenza)>0){
                tmp = tab1[j];
                tab1[j] = tab1[j+1];
                tab1[j+1] = tmp;
            }
        }
    }
    for (i=0;i<n;i++)
        printf("%s %s %s %s %s\n",tab1[i]->codice, tab1[i]->staz_partenza, tab1[i]->staz_arrivo, tab1[i]->data_str, tab1[i]->orap_str);
    printf("\n");
}

//FUNZIONE ORDINAMENTO PER STAZIONE DI ARRIVO
void ordina_arrivo(corse_t **tab1, int n){
    int i,j;
    corse_t *tmp;
    printf("\nCorse ordinate per stazione di arrivo:\n\n");
    for (i=0;i<n-1;i++){
        for (j=0;j<n-1-i;j++){
            if (strcmp(tab1[j]->staz_arrivo,tab1[j+1]->staz_arrivo)>0){
                tmp = tab1[j];
                tab1[j] = tab1[j+1];
                tab1[j+1] = tmp;
            }
        }
    }
    for (i=0;i<n;i++)
        printf("%s %s %s %s %s\n",tab1[i]->codice, tab1[i]->staz_partenza, tab1[i]->staz_arrivo, tab1[i]->data_str, tab1[i]->orap_str);
    printf("\n");
}

char *strToLower2(char s[]){
    int i;
    int lun_s = strlen(s);

    for (i=0;i<lun_s;i++){
        s[i] = tolower(s[i]);
    }
    return s;
}

void binary(corse_t **tab, int n){
    char stazione[MAX];
    //ordinamento vettore
    int i,j;
    corse_t *tmp;
    for (i=0;i<n-1;i++){
        for (j=0;j<n-1-i;j++){
            if (strcmp(tab[j]->staz_partenza,tab[j+1]->staz_partenza)>0){
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
    //printf("%s", tab[indice]->staz_partenza);
    ricercaLineare(tab, n, strToLower2(stazione));
}

int ricercaBinaria(corse_t **tab, int l, int r, char s[MAX]){
    int m;
    if (l>r)
        return -1;
    m = (l+r)/2;
    if (strstr(strToLower2(tab[m]->staz_partenza), s)!=NULL)
        return m;
    if (strcmp(strToLower2(tab[m]->staz_partenza), s)<0)
        return ricercaBinaria(tab, l, m-1, s);
    return ricercaBinaria(tab, m+1, r, s);
}

void ricercaLineare(corse_t **tab, int n, char s[MAX]){
    int i;
    for (i=0;i<n;i++){
        if (strstr(strToLower2(tab[i]->staz_partenza), strToLower2(s))!=NULL){
            printf("%s\n", tab[i]->staz_partenza);
        }
    }
}