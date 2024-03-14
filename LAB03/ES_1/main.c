//LAB03 ES_01 - FRANCESCO PIO D'ANGOLO 295068
#include <stdio.h>
#include <stdlib.h>
int merge(int *a, int l, int r);
int majority(int *a, int N);
int realloc1d(int **v, int MAX);

int main() {
    int n=1, i;
    int *vet;
    vet = (int *) malloc(n*sizeof (int));


    n = realloc1d(&vet, n);
    printf("\nElementi del vettore:\n");
    for (i=0;i<n;i++){
        printf("%d ", vet[i]);
    }
    printf("\n\n");

    int major = majority(vet, n);
    if (major != -1)
        printf("L'elemento maggioritario del vettore inserito è: %d", major);
    else{
        printf("Non esiste elemento maggioritario del vettore inserito (%d)", major);
    }

    free(vet);
}

int majority(int *a, int N){
    int l=0, r=N-1, major;
    major = merge(a, l, r);
    return major;
}

int merge(int *a, int l, int r){
    int i, a1, a2, cnt=0, q;
    if (l>=r)
        return a[l];
    q = (l+r)/2;
    a1 = merge(a,l,q);
    a2 = merge(a,q+1,r);

    if (a1 == a2){
        for (i=l;a1!=-1 && i<=r; i++){
            if (a[i]==a1)
                cnt++;
        }
        if (cnt>(r-l+1)/2)
            return a1;
        cnt=0;
    }
    else{
        for (i=l;a1!=-1 && i<=r;i++){
            if (a[i]==a1)
                cnt++;
        }
        if (cnt>(r-l+1)/2)
            return a1;
        cnt=0;
        for (i=l;a2!=-1 && i<=r;i++){
            if (a[i]==a2)
                cnt++;
        }
        if (cnt>(r-l+1)/2)
            return a2;
        cnt = 0;
    }
    return -1;
}

int realloc1d(int **v, int MAX){
    int *v1, d, i=0;
    v1 = (int*) malloc(MAX*sizeof (int));
    printf("Inserisci elementi del vettore oppure 'fine' per terminare:\n");
    printf("%d.",i+1);
    while (scanf("%d", &d)==1){
        if (i==MAX){
            MAX = 2*MAX;
            v1 = realloc(v1, MAX);
        }
        v1[i++] = d;
        printf("%d.",i+1);
    }
    *v = v1;
    return i;
}
