//LAB02 ES_01 - FRANCESCO PIO D'ANGOLO - 295068
#include <stdio.h>

void swap(int *a, int *b);
int even(int a);
int gcd(int a, int b);

int main() {
    int a,b,continua=1,mcd;

    do{
        printf("Inserisci due numeri:\n");
        printf("a: ");
        if (scanf("%d", &a)==1 && a>0)
            continua = 0;
        printf("\nb: ");
        if (scanf("%d", &b)==1 && b>0)
            continua = 0;
        else{
            printf("Errore in input\n");
            continua = 1;
        }
    }while (continua);

    mcd = gcd(a,b);
    if (mcd>1)
        printf("Il minimo comun divisore è: %d", mcd);
    else
        printf("a e b sono numeri primi");
}

int gcd(int a, int b){

    if (b>a)
        swap(&a, &b);

    if (a%b==0)
        /*condizione di terminazione*/
        return b;

    if (even(a)){
        if (even(b)){
            /* a pari e b pari*/
            return 2* gcd(a/2,b/2);
        }else{
            /* a pari e b dispari*/
            swap(&a, &b);
            return gcd(a,b/2);
        }
    }else if (even(b)){
        /* a dispari e b pari*/
        return gcd(a,b/2);
    }else{
        /* a dispari e b dispari*/
        return gcd((a-b)/2,b);
    }
}


int even(int a){
    return 1-(a%2);
}

void swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}