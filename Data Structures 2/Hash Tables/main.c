#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int occ;
    char lettera;
}
        cella;

typedef struct {
    cella **matrice;
    int nc,nr;
}
        GRID;

typedef struct{
    int nparole;
    char **vettoreparole;
}SOL;

typedef struct{
    char* parola;
    int valore;
}word;

typedef struct words{
    word *parole;
    int nparole;
}WORDS;

GRID leggigriglia(FILE*fin){
    GRID griglia;
    int i,j;
    fscanf(fin,"%d %d\n",&griglia.nr,&griglia.nc);
    griglia.matrice = malloc(griglia.nr*sizeof(cella*));
    if(griglia.matrice == NULL)
        exit(0);
    for(i= 0;i<griglia.nr;i++){
        griglia.matrice[i] = malloc(griglia.nc*sizeof(cella));
        if(griglia.matrice[i] == NULL)
            exit(0);
        for(j = 0;j<griglia.nc;j++){
            fscanf(fin,"%c",&griglia.matrice[i][j].lettera);
            griglia.matrice[i][j].occ = 2;
        }
        getc(fin);
    }
    return griglia;
}

WORDS leggiparole(FILE*fin){
    WORDS words;
    char aux[15];
    int i = 0;
    words.parole = malloc(0*sizeof(word));
    while(!feof(fin)){
        words.parole = realloc(words.parole,(i+1)*sizeof(word));
        fscanf(fin,"%s %d\n",aux,&words.parole[i].valore);
        words.parole[i].parola= strdup(aux);
        i++;

    }
    words.nparole = i;
    return words;
}

SOL leggisol(FILE*fin){ //fin ha come prima riga il numero di parole e successivamente una parola per riga
    SOL sol;
    char aux[15];
    int i;
    fscanf(fin,"%d",&sol.nparole);
    sol.vettoreparole = malloc(sol.nparole*sizeof(char*));
    for(i= 0;i<sol.nparole;i++){
        fscanf(fin,"%s\n",aux);
        sol.vettoreparole[i] = strdup(aux);
    }
    return sol;
}


int cercaparola(WORDS words,char *chiave){
    int i;
    for(i = 0;i<words.nparole;i++){
        if(strcmp(words.parole[i].parola,chiave) == 0)
            return 1;
    }
    return 0;
}

int checkdiag(GRID griglia,char *parola,int i,int j){
    int k;
    int lenparola = strlen(parola);
    if((griglia.nr-i) < lenparola || griglia.nc-j <lenparola)
        return 0;
    for(k = 0;k<lenparola;k++){
        if(griglia.matrice[i+k][j+k].lettera != parola[k] ||griglia.matrice[i+k][j+k].occ == 0)
            return 0;
    }
    for(k = 0;k<lenparola;k++){
        griglia.matrice[i+k][j+k].occ--;
    }
    return 1;
}

int checkvert(GRID griglia,char *parola,int i,int j){
    int k;
    int lenparola = strlen(parola);
    if((griglia.nr-i) < lenparola)
        return 0;
    for(k = 0;k<lenparola;k++){
        if(griglia.matrice[i+k][j].lettera != parola[k] || griglia.matrice[i+k][j].occ == 0)
            return 0;
    }
    for(k = 0;k<lenparola;k++){
        griglia.matrice[i+k][j].occ--;
    }
    return 1;
}

int checkor(GRID griglia,char *parola,int i ,int j){
    int k;
    int lenparola= strlen(parola);
    if((griglia.nc-j)<lenparola)
        return 0;
    for(k = 0;k<lenparola;k++){
        if(griglia.matrice[i][k+j].lettera != parola[k] || griglia.matrice[i][k+j].occ== 0)
            return 0;
    }
    for(k = 0;k<lenparola;k++){
        griglia.matrice[i][k+j].occ--;
    }
    return 1;
}

int controllamatrice(GRID griglia,char*parola){
    int i,j;
    for(i=0;i<griglia.nr;i++){
        for(j = 0;j<griglia.nc;j++){
            if(parola[0] == griglia.matrice[i][j].lettera){
                if(checkor(griglia,parola,i,j) == 1)     //presenza di diversi if con return 1 per modificare solo una volta la matrice
                    return 1;
                else if(checkvert(griglia,parola,i,j) == 1)
                    return 1;
                else if(checkdiag(griglia,parola,i,j) == 1)
                    return 1;
            }
        }
    }
    return 0;
}

int controllasoluzione(SOL sol,GRID griglia,WORDS words){
    int i,j;
//controllo se parole della soluzione in parole
    for(i= 0;i<sol.nparole;i++){
        if(cercaparola(words,sol.vettoreparole[i]) == 0)
            return 0;
    }
    for(i = 0;i<sol.nparole;i++){
        if(controllamatrice(griglia,sol.vettoreparole[i]) == 0)
            return 0;
    }
    //resetto matrice per un eventuale nuova soluzione da verificare
    for(i = 0;i<griglia.nr;i++){
        for(j = 0;j<griglia.nc;j++){
            griglia.matrice[i][j].occ = 2;
        }
    }
    return 1;
}






// soluzione problema corretto


int controllacoppie(SOL sol,int *aux,GRID grid,int pos,int start,int n);

int checkocc(GRID grid){
    int i,j,zeros = 0;

    for(i = 0;i<grid.nr;i++){
        for (j = 0; j < grid.nc; j++) {
            if(grid.matrice[i][j].occ<= 0)
                zeros++;

        }
    }
    for(i = 0;i<grid.nr;i++){
        for(j = 0; j<grid.nc;j++){
            grid.matrice[i][j].occ = 2;
        }
    }
    if(zeros >1)
        return 0;
    return 1;
}
int controllacoppie(SOL sol,int *aux,GRID grid,int pos,int start,int n){
    int i;
    if(pos>= n){
        if(controllamatrice(grid,sol.vettoreparole[aux[0]])==1 && controllamatrice(grid,sol.vettoreparole[aux[1]])==1){
            if(checkocc(grid))
                return 1;
        }
        return 0;
    }
    for(i = start;i<sol.nparole;i++){
        aux[pos] = i;
        if(controllacoppie(sol,aux,grid,pos+1,i+1,n) == 0)
            return 0;


    }
    return 1;
}



int controllacoppieW(SOL sol,GRID griglia){
    int *aux;
    aux = malloc(2*sizeof(*aux));
    if(controllacoppie(sol,aux,griglia,0,0,2)==1)
        return 1;
    return 0;

}


int controllasoluzionev2(SOL sol,GRID griglia,WORDS words){
    int i,j,a;
//controllo se parole della soluzione in parole
    for(i= 0;i<sol.nparole;i++){
        if(cercaparola(words,sol.vettoreparole[i]) == 0)
            return 0;
    }

    if(controllacoppieW(sol,griglia)==0)
        return 0;

    return 1;
}




int main() {
    GRID grid;
    WORDS words;
    SOL sol;
    FILE *fin;
    fin = fopen("../proposta.txt","r");
    sol = leggisol(fin);

    fclose(fin);
    fin = fopen("../parole.txt","r");
    words = leggiparole(fin);
    fclose(fin);
    fin = fopen("../griglia.txt","r");
    grid = leggigriglia(fin);
    fclose(fin);
    int a = controllasoluzione(sol,grid,words);
    printf("%d",a);
    return 0;
}
