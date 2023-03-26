#include <stdio.h>
#include "Graph.h"

int main(int argc, char **argv) {
    char nodo[MAXL];
    Graph G = NULL;
    ST st = STinit(1);
    FILE *fp;
    int id1, id2, id3, stop = 0, cmd;

    if (argc != 2) {
        printf("Uso: %s <file_in>\n", argv[0]);
        exit(-1);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(-1);

    G = GRAPHload(fp, st);
    if (G == NULL || st == NULL)
        exit(-1);

    do {
        printf("\nQuale operazione vuoi eseguire?\n");
        printf("\t1. Visualizza grafo\n");
        printf("\t2. Genera liste di adiacenza\n");
        printf("\t3. Controlla adiacenza di 3 vertici\n");
        printf("\t4. Esci\n");
        scanf("%d", &cmd);

        switch(cmd) {
            case 1: {
                GRAPHstore(stdout, G, st);
            }
                break;

            case 2: {
                LISTinit(G, st);
                printf("Generazione lista adiacenze avvenuta con successo!\n");
                LISTdisplay(G, st);
#if DBG
                GRAPHstore(g, st);
#endif /* DBG */
            }
                break;

            case 3: {
                printf("Inserisci nome primo nodo: ");
                KEYscan(nodo);
                id1 = STsearch(st, nodo);
                printf("Inserisci nome secondo nodo: ");
                KEYscan(nodo);
                id2 = STsearch(st, nodo);
                printf("Inserisci nome terzo nodo: ");
                KEYscan(nodo);
                id3 = STsearch(st, nodo);
                if ((id1 != -1) && (id2 != -1) && (id3 != -1))
                    printf("Il sottografo %se' completo\n", GRAPHcheck3adj(G, id1, id2, id3) ? "" : "non ");
            }
                break;

            case 4: {
                stop  = 1;
            }
                break;

            default:
                printf("Scelta non valida!\n");
        }
    } while(!stop);

    STfree(st);
    GRAPHfree(G);
    return 0;
}