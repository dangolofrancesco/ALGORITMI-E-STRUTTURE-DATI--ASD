#include <stdio.h>
#include <string.h>

void ordinaVettore(char *v[], int n);

int main() {
    int i, ns, fine=0;
    char *v[20], buf[520];
    printf("Scrivi stringhe:\n");
    for (ns=i=0;!fine && ns<20;ns++){
        v[ns] = buf + i; // v[ns] = buf[i]
        gets(v[ns]);
        if (strlen(v[ns])==0)
            fine = 1;
        i = i+ strlen(v[ns])+1;
    }
    ordinaVettore(v,ns);
    printf("Stringhe ordinate:\n");
    for (i=0;i<ns;i++)
        printf("%s\n",v[i]);
}

void ordinaVettore(char *v[], int n){
    int i, j, min;
    char *tmp;
    for (i=0;i<n-1;i++){
        min = i;
        for (j=i+1;i<n;j++) {
            if (strcmp(v[min], v[j]) > 0)
                min = j;
        }
        tmp = v[i];
        v[i] = v[min];
        v[min] = tmp;
    }
}
