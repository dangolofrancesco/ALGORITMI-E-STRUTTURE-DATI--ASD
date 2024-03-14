// LAB01 ES_2 - FRANCESCO PIO D'ANGOLO 295068

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 30
#define FILENAME "../corse.txt"

typedef struct{
    char codice_tratta[MAX], partenza[MAX], destinazione[MAX];
    int codice, ritardo, anno, mese, giorno, ora_p, minuto_p, ora_a, minuto_a;
}corse_t;

typedef enum{
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardoTot,
    r_fine
}comando_e;

char *strToLower(char *s);
comando_e leggi_comando(char *cmd);
int apertura_file(FILE *fp, int *n);

int main() {
    FILE *fp;
    int nr;
    char cmd[MAX];
    comando_e comando;
    corse_t corse[nr], *corse_p[nr];
    apertura_file(&fp, &nr);
    comando = leggi_comando(&cmd);
    printf("%d", comando);
}


int apertura_file(FILE *fp, int *n){
    if ((fp=fopen(FILENAME, "r")) == NULL){
        printf("Error opening file");
        return 0;
    }
    return fscanf(fp,"%d", n);
}
char *strToLower(char *s){
    int i;
    int lun_s = strlen(s);
    for (i=0;i<lun_s;i++){
        s[i] = tolower(s[i]);
    }
    return s;
}

comando_e leggi_comando(char *cmd){
    comando_e c = r_date;
    char *comandi[r_fine] = {"date", "partenza", "capolinea", "ritardo",
                             "ritardo_tot"};

    printf("Scegli comando (date/partenza/capolinea/ritardo/ritardo_tot/fine): ");
    scanf("%s", cmd);
    cmd = strToLower(cmd);

    while (c<r_fine && strcmp(cmd,comandi[c]) != 0){
        c++;
    }
    return c;
};

void riempi_strutture(FILE *fp, corse_t *corse, corse_t **corse_p, int n){
    int i;

    for (i=0;i<n;i++){
        corse_p[i] = &corse[i];
    }

    for (i=0;i<n;i++){
        fscanf(fscanf(fp, "%s%s%s %d/%d/%d %d:%d:%*d %d:%d:%*d %d", corse_p[i]->codice_tratta, corse_p[i]->partenza, corse_p[i]->destinazione,
                      corse_p[i]->anno, )
    }
};

