#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *Item;

/*typedef struct node_s{
    Item val;
    struct node_s *next;
}node_t, *link;*/

typedef struct canz_s{
    char *titolo;
    int id_cant;
} canz_t;

typedef struct cant_s{
    char *nome;
    int *lista;
    int n_canz;
}cant_t;

void generaElenchi(cant_t *cantanti, canz_t *canzoni, int n_cant, int n_canz){
    int i, id_c;

    for (i=0; i<n_cant; i++)
        cantanti[i].n_canz = 0;
    for (i=0; i<n_canz; i++)
        cantanti[canzoni[i].id_cant].n_canz++;
    for (i=0; i<n_cant; i++){
        if (cantanti[i].n_canz==0)
            cantanti[i].lista = NULL;
        else{
            cantanti[i].lista = (int *) malloc(cantanti[i].n_canz * sizeof (int));
            if (cantanti[i].lista==NULL)
                exit(-1);
            // contatore re-inizializzato a zero per tracciare l'inserimento parziale
            cantanti[i].n_canz = 0;
        }
    }
    //associazione delle canzoni agli album
    for (i=0;i<n_canz;i++){
        id_c = canzoni[i].id_cant;
        cantanti[id_c].lista[cantanti[id_c].n_canz] = i;
        cantanti[id_c].n_canz++;
    }
}


int main() {
}
