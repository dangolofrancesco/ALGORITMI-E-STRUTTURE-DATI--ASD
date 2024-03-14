#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

typedef enum{
    punto,
    quadra1,
    quadra2,
    minuscolo,
    maiuscolo,
}meta_t;

char *cercaRegexp(char *scr, char *regexp);
int lenReal(char *regexp,int len_regexp);
meta_t cercaMeta(char *meta);
int menuMeta(meta_t cmd, int *j, char *scr_c, char *regexp_c);
int metaPunto(char *scr_c);
int metaQuadra1(int *j, char *scr_c, char *regexp_c );
int metaQuadra2(int *j, char *scr_c, char *regexp_c);
int metaMinuscolo(int *j, char *scr_c);
int metaMaiuscolo(int *j, char *scr_c);

int main() {
    char regexp[MAX] = ".[o][^g]\\a";
    char source[MAX] = "abfoto";
    char *p;
    p = cercaRegexp(source,regexp);

    printf("%p \n%p", source, p);
}

char *cercaRegexp(char *scr, char *regexp){
    int i,j,scarto,scarto_prec, lun_scr, lun_regexp, equal;
    lun_regexp = strlen(regexp);
    lun_scr = strlen(scr);
    int lun_real = lenReal(regexp, strlen(regexp));
    meta_t c;

    for (i=0;i<=(lun_scr-lun_real);i++){
        equal = 1;
        scarto = 0;
        for (j=0;equal==1 && j<lun_regexp;j++){
            if (!isalpha(regexp[j])){
                scarto_prec = scarto;
                scarto += j;
                c = cercaMeta(&regexp[j]);
                equal = menuMeta(c,&j,scr+i+j+scarto_prec,regexp+j);
                scarto -= j;
            }
            else{
                if (scr[i+j+scarto] != regexp[j])
                    equal = 0;
            }
        }
        if (equal == 1){
            return scr + i;
        }
    }
    return NULL;
}

int lenReal(char *regexp, int len_regexp){
    int i=0, j, cnt=0;
    while (i<len_regexp){
        if (regexp[i]=='['){
            j=i+1;
            while (regexp[j] != ']'){
                j++;
            }
            i = i+j;
            cnt++;
        }
        else if (regexp[i] == '\\'){
            i = i+2;
            cnt++;
        }
         else{
            cnt++;
            i++;
         }
    }
    return cnt;
}

meta_t cercaMeta(char *meta){
    int i;
    meta_t c;

    if (meta[0] == '.')
        c = punto;
    else if (meta[0] == '[')
        if (meta[1] == '^')
            c = quadra2;
        else
            c = quadra1;
    else if (meta[0] == '\\'){
        if (meta[1] == 'a')
            c = minuscolo;
        else if (meta[1] == 'A')
            c = maiuscolo;
    }
    return c;

}

int menuMeta(meta_t cmd, int *j, char *scr_c, char *regexp_c){

    switch (cmd) {
        case punto:
            return metaPunto(scr_c);
        case quadra1:
            return metaQuadra1(j,scr_c,regexp_c);
        case quadra2:
            return metaQuadra2(j,scr_c,regexp_c);
        case minuscolo:
            return metaMinuscolo(j,scr_c);
        case maiuscolo:
            return metaMaiuscolo(j,scr_c);
    }
}

int metaPunto(char *scr_c){
    if (isalpha(*scr_c))
        return 1;
    return 0;
}

int metaQuadra1(int *j, char *scr_c, char *regexp_c){
    int n=0,i;
    while (regexp_c[n] != ']'){
        n++;
    }
    *j += n;

    for (i=0;i<n;i++){
        if (scr_c[0] == regexp_c[i])
            return 1;
    }
    return 0;
}

int metaQuadra2(int *j, char *scr_c, char *regexp_c){
    int n=0,i;
    while (regexp_c[n] != ']'){
        n++;
    }
    *j += n;

    for (i=0;i<n;i++){
        if (scr_c[0] == regexp_c[i])
            return 0;
    }
    return 1;
}

int metaMinuscolo(int *j, char *scr_c){
    *j += 1;
    if (islower(scr_c[0]))
        return 1;
    return 0;
}

int metaMaiuscolo(int *j, char *scr_c){
    *j += 1;
    if (isupper(scr_c[0]))
        return 1;
    return 0;
}