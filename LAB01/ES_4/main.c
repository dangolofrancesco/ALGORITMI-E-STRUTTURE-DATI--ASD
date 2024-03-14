#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define FILENAME "../corse.txt"
#define MAX 100
#define MAXN 30

typedef struct{
    char rideCode[MAX];
    char departureSt[MAX];
    char arrivalSt[MAX];
    char departureDate[MAX];
    char departureTime[MAX];
    char arrivalTime[MAX];
    int delay;
}rides_t;

typedef enum{
    sort_date,
    sort_code,
    sort_departing,
    sort_arrival,
    sort_end
}sorting_t;

void readRides(FILE *fp, rides_t *list, int n);
char *strToLower(char s[]);
void stampaComandi(char **comandi);
sorting_t leggicomando(char **comandi);
void controlloCasi(sorting_t cmd, rides_t **rif1, rides_t **rif2, rides_t **rif3, rides_t **rif4, int n);
void sortingDate(rides_t **rides, int n);
void sortingCode(rides_t **rides, int n);
void sortingDepSt(rides_t **rides, int n);
void sortingArrSt(rides_t **rides, int n);

int main() {
    FILE *fp = fopen(FILENAME, "r");
    int nr,i, continua=1;
    char *comandi[sort_end+1] = {"data", "codice","partenza", "arrivo", "fine"};
    sorting_t cmd;

    fscanf(fp,"%d", &nr);
    rides_t rides[nr], *ridesRif1[nr], *ridesRif2[nr], *ridesRif3[nr], *ridesRif4[nr];
    readRides(fp,rides, nr);

    for (i=0;i<nr;i++){
        ridesRif1[i]=ridesRif2[i]=ridesRif3[i]=ridesRif4[i]=&rides[i];
    }

    stampaComandi(comandi);
    do {
        cmd = leggicomando(comandi);
        if (cmd==sort_end){
            continua=0;
        }
        controlloCasi(cmd, ridesRif1, ridesRif2, ridesRif3, ridesRif4, nr);
    }while (continua);
}

void readRides(FILE *fp, rides_t *list, int n){
    int i;
    for (i=0;i<n;i++){
        fscanf(fp,"%s %s %s %s %s %s %d",
               list[i].rideCode,
               list[i].departureSt,
               list[i].arrivalSt,
               list[i].departureDate,
               list[i].departureTime,
               list[i].arrivalTime,
               &list[i].delay);
    }
    fclose(fp);
}

sorting_t leggicomando(char **comandi){
    int i;
    char cmd[MAXN];
    sorting_t c;
    printf("Scrivi comando di ordinamento: ");
    scanf("%s", cmd);

    for (i=0;i<=sort_end;i++){
        if (strcmp(strToLower(cmd),comandi[i])==0)
            return (sorting_t) i;
    }
}

void stampaComandi(char **comandi){
    int i;
    printf("Comandi disponibili:\n");
    for (i=0;i<sort_end+1;i++){
        printf("-%s\n", comandi[i]);
    }
}

void controlloCasi(sorting_t cmd, rides_t **rif1, rides_t **rif2, rides_t **rif3, rides_t **rif4, int n){
    switch (cmd) {
        case sort_date:
            return sortingDate(rif1, n);
        case sort_code:
            return sortingCode(rif2, n);
        case sort_departing:
            return sortingDepSt(rif3, n);
        case sort_arrival:
            return sortingArrSt(rif4, n);
        case sort_end:
            break;
    }
}

//FUNZIONE ORDINAMENTO PER DATA (eventualmente per ora)
//UTILIZZO DI INSERTION SORT PER STABILITA' ALGORITMICA
void sortingDate(rides_t **rides, int n) {
    int i,j;
    rides_t *tmp;
    printf("\nCorse ordinate per data:\n\n");
    for (i=1;i<n;i++){
        tmp = rides[i];
        j = i-1;
        while (j>=0 && ((strcmp(tmp->departureDate,rides[j]->departureDate)<0) || (strcmp(tmp->departureDate,rides[j]->departureDate)==0) && (strcmp(tmp->departureTime,rides[j]->departureTime)<0))){
            rides[j+1] = rides[j];
            j--;
        }
        rides[j+1] = tmp;
    }
    for (i=0;i<n;i++)
        printf("%s %s %s %s %s\n",rides[i]->rideCode, rides[i]->departureSt, rides[i]->arrivalSt, rides[i]->departureDate, rides[i]->departureTime);
    printf("\n");
}

//FUNZIONE ORDINAMENTO PER CODICE TRATTA
//UTILIZZO DI BUBBLE SORT
void sortingCode(rides_t **rides, int n){
    int i,j;
    rides_t *tmp;
    printf("\nCorse ordinate per codice:\n\n");
    for (i=0;i<n-1;i++){
        for (j=0;j<n-1-i;j++){
            if (strcmp(rides[j]->rideCode,rides[j+1]->rideCode)>0){
                tmp = rides[j];
                rides[j] = rides[j+1];
                rides[j+1] = tmp;
            }
        }
    }
    for (i=0;i<n;i++)
        printf("%s %s %s %s %s\n",rides[i]->rideCode, rides[i]->departureSt, rides[i]->arrivalSt, rides[i]->departureDate, rides[i]->departureTime);
    printf("\n");
}

//FUNZIONE ORDINAMENTO PER STAZIONE DI PARTENZA
void sortingDepSt(rides_t **rides, int n){
    int i,j;
    rides_t *tmp;
    printf("\nCorse ordinate per stazione di partenza:\n\n");
    for (i=0;i<n-1;i++){
        for (j=0;j<n-1-i;j++){
            if (strcmp(rides[j]->departureSt,rides[j+1]->departureSt)>0){
                tmp = rides[j];
                rides[j] = rides[j+1];
                rides[j+1] = tmp;
            }
        }
    }
    for (i=0;i<n;i++)
        printf("%s %s %s %s %s\n",rides[i]->rideCode, rides[i]->departureSt, rides[i]->arrivalSt, rides[i]->departureDate, rides[i]->departureTime);
    printf("\n");
}

//FUNZIONE ORDINAMENTO PER STAZIONE DI ARRIVO
void sortingArrSt(rides_t **rides, int n){
    int i,j;
    rides_t *tmp;
    printf("\nCorse ordinate per stazione di arrivo:\n\n");
    for (i=0;i<n-1;i++){
        for (j=0;j<n-1-i;j++){
            if (strcmp(rides[j]->arrivalSt,rides[j+1]->arrivalSt)>0){
                tmp = rides[j];
                rides[j] = rides[j+1];
                rides[j+1] = tmp;
            }
        }
    }
    for (i=0;i<n;i++)
        printf("%s %s %s %s %s\n",rides[i]->rideCode, rides[i]->departureSt, rides[i]->arrivalSt, rides[i]->departureDate, rides[i]->departureTime);
    printf("\n");
}

char *strToLower(char s[]){
    int i;
    int lun_s = strlen(s);

    for (i=0;i<lun_s;i++){
        s[i] = tolower(s[i]);
    }
    return s;
}