#include <stdio.h>
#define FILENAME "../file.txt"
#define MAXN 200
#define MAXS 256

//ORDINAMENTO STRUCT
int leggiStud(char *nomeFile, stud_t *el, int nmax);
void ordinaPerMatricola(studente_t **elR, int n);

typedef struct studente{
    char cognome[MAXS], nome[MAXS];
    int matricola;
    float media;
}studente_t;

int main() {
    studente_t elenco[MAXN], *elencoRif[MAXN];
    int i, ns = leggiStud(FILENAME,elenco,MAXN);
    for (i=0;i<ns;i++)
        elencoRif[i] = &elenco[i];
    ordinaPerMatricola(elencoRif,ns);


}

int leggiStud(char *nomeFile, stud_t *el, int nmax) {
    int n;
    FILE *fp = fopen(nomeFile,"r"); for (n=0; n<nmax; n++) {
        if (fscanf(fp,"%s%s%d%f", el[n].cognome, el[n].nome, &el[n].matr,&el[n].media)==EOF)
            break;
    }
    fclose(fp);
    return n;
}

//LA FUNZIONE, NEL PARAMETRO **elR, RICEVE SOLO IL VETTORE DI PUNTATORI A STRUCT
void ordinaPerMatricola(studente_t **elR, int n) {
    studente_t *temp;
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            //CONFRTONTO A PARTIRE DAI PUNTATORI
            if ((elR[j]->matricola - elR[min]->matricola) < 0)
                min = j;
            //SCAMBIO DI PUNTATORI
            temp = elR[i];
            elR[i] = elR[min];
            elR[min] = temp;
        }
    }
}

// studente_t **elR equivale a studente_t *elR[]
void scriviRifStudenti(char *fileOut,studente_t **elR, int n){
    int i;
    FILE *fp = fopen(fileOut, "w");
    for (i=0;i<n;i++){
        fprintf(fp, "%s %s %d %f\n", elR[i]->cognome, elR[i]->nome, elR[i]->matricola,
                elR[i]->media);
    }
    fclose(fp);
}




