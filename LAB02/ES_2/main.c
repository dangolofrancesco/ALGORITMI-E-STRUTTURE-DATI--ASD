#include <stdio.h>
#include <stdlib.h>
#define FILENAME "../mat.txt"

int **malloc2dR(int nr, int nc, FILE *fp);
//int malloc2dP(int ***mp, int nr, int nc, FILE *fp);
void free2d(int **m, int nr);
void separa(int **mat, int nr, int nc, int **neri, int **bianchi);
int realloc1d(int *MAX, int i, int **v);
void stampa(int *v);

int main() {
    FILE *fp = fopen(FILENAME, "r");
    int nr, nc, **matr, i=0, j;
    int *neri, *bianchi;
    if (fscanf(fp,"%d %d", &nr, &nc)<2)
        return -1;
    matr = malloc2dR(nr,nc,fp);
    //malloc2dP(&matr, nr, nc, fp);

    separa(matr, nr, nc, &neri, &bianchi);

    printf("Caselle nere:\n");
    stampa(neri);
    printf("Caselle bianche:\n");
    stampa(bianchi);


    free2d(matr, nr);
    free(neri);
    free(bianchi);
}

int **malloc2dR(int nr, int nc, FILE *fp){
    int **m;
    int i,j;

    m = (int **) malloc(nr*sizeof (int *));
    if (m==NULL)
        exit(1);

    for (i=0;i<nr;i++){
        m[i] = (int *) malloc(nc*sizeof (int));
        if (m[i]==NULL)
            exit(1);
        for (j=0;j<nc;j++){
            fscanf(fp,"%d",&m[i][j]);
        }
    }
    return m;
}

/*int malloc2dP(int ***mp, int nr, int nc, FILE *fp){
    int **m;
    int i,j;

    m = (int **) malloc(nr*sizeof (int *));
    if (m==NULL)
        exit(1);

    for (i=0;i<nr;i++){
        m[i] = (int *) malloc(nc*sizeof (int));
        if (m[i]==NULL)
            exit(1);
        for (j=0;j<nc;j++){
            fscanf(fp,"%d",&m[i][j]);
        }
    }
    *mp = m;
}*/

void free2d(int **m, int nr){
    int i;
    for (i=0;i<nr;i++)
        free(m[i]);
    free(m);
}

void separa(int **mat, int nr, int nc, int **neri, int **bianchi){
    int *n, *b;
    int i,j, MAX = 1, N, cnt=0;

    n = (int *) malloc(MAX*sizeof (int ));
    if (n==NULL)
        exit(2);
    b = (int *) malloc(MAX*sizeof(int ));
    if (b==NULL)
        exit(3);
    //bianchi (partono da (0,0))
    for (i=0;i<nr;i++){
        for (j=(i%2);j<nc;j=j+2){
            realloc1d(&MAX, cnt, &b);
            b[cnt++] = mat[i][j];
        }
    }
    *bianchi = b;

    cnt = 0;

    //neri (partono da (0,1))
    for (i=0;i<nr;i++){
        for (j=1-(i%2);j<nc;j=j+2){
            realloc1d(&MAX, cnt, &n);
            n[cnt++] = mat[i][j];
        }
    }

    *neri = n;
}

//CHIEDERE COME DEALLOCARE v1
int realloc1d(int *MAX, int i, int **v){
    int *v1;
    if (i==0)
        v1 = (int *) malloc(0*sizeof (int));

    if (i==*MAX){
        *MAX = 2*(*MAX);
        v1 = realloc(v1, (*MAX)*sizeof(int ));
    }
    *v = v1;
}

void stampa(int *v){
    int i=0;
    while (v[i]!=0)
        printf("%d ", v[i++]);
    printf("\n");
}