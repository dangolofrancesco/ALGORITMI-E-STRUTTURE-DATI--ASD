#include <stdio.h>
#define MAX 100
// funzioni leggi e scrivi puntatori

void leggi(int *v, int maxDim, int *n);
void scrivi(int *v, int n);

int main(){
    int n, dati[MAX], i;
    leggi(dati, MAX, &i);
    scrivi(dati, i);
}

void leggi(int *v, int maxDim, int *n){
    int i, fine = 0;
    for (i=0; !fine && i<maxDim;i++){
        printf("v[%d] (0 per terminare): ", i);
        scanf("%d", v+i); // scanf("%d", &v[i]);
        if (*(v+i) == 0){
            fine = 1;
            *n = i-1;
        }
    }
}

void scrivi(int *v, int n){
    int i;
    for (i=0;i<=n;i++)
        printf("%d ", *(v+i));
}



