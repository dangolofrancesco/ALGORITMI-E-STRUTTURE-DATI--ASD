//LAB05 ES2 - FRANCESCO PIO D'ANGOLO 295068
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char c1, c2;
    int v1, v2;
    int id;
}tiles_t;

typedef struct {
    int id;
    int rot;
}sol_t;

typedef struct{
    tiles_t *tiles;
    sol_t **board, **b_board;
    int *mark, *mark_pos, r, c;
    int c_val, b_val;
}tab_t;

int aperturaFile(FILE **f1, FILE **f2){
    int n;
    (*f1) = fopen("../tiles.txt", "r" );
    if ((*f1)==NULL){
        printf("Errore 1");
        return -1;
    }
    fscanf((*f1), "%d", &n);

    (*f2) = fopen("../board.txt", "r");
    if ((*f2)==NULL){
        printf("Errore 2");
        return -1;
    }
    return n;

}

void malloc2d(tab_t *tab, FILE *f2){
    int i;
    fscanf(f2, "%d %d", &tab->r, &tab->c);
    tab->board = (sol_t **) malloc(tab->r*sizeof (sol_t *));
    if (tab->board==NULL){
        printf("Errore di allocazione");
        exit(1);
    }

    tab->b_board = (sol_t **) malloc(tab->r*sizeof (sol_t *));
    if (tab->b_board==NULL){
        printf("Errore di allocazione");
        exit(2);
    }

    for (i=0; i<tab->r; i++){
        tab->board[i] = (sol_t *) malloc(tab->c* sizeof(sol_t));
        if (tab->board[i]==NULL){
            printf("Errore di allocazione");
            exit(3);
        }
        tab->b_board[i] = (sol_t *) malloc(tab->c* sizeof(sol_t));
        if (tab->b_board[i]==NULL){
            printf("Errore di allocazione");
            exit(4);
        }
    }
}

void inizializza(tab_t *tab, FILE *f1, FILE *f2, int n){
    int i, j, cnt=0;
    tab->tiles = (tiles_t *) malloc(n*sizeof (tiles_t));
    tab->mark = calloc(n,sizeof (int ));
    tab->mark_pos = calloc(n, sizeof (int));
    for (i=0; i<n; i++){
        fscanf(f1, " %c%d %c%d ", &tab->tiles[i].c1, &tab->tiles[i].v1,
               &tab->tiles[i].c2, &tab->tiles[i].v2);
        tab->tiles[i].id = i;
    }
    malloc2d(tab, f2);
    for (i=0; i<tab->r; i++){
        for (j=0; j<tab->c; j++){
            fscanf(f2, "%d/%d", &tab->board[i][j].id, &tab->board[i][j].rot);
            if (tab->board[i][j].id != -1){
                tab->mark[tab->board[i][j].id] = 1;
                tab->mark_pos[cnt] = 1;
            }
            cnt++;
        }
    }
    tab->c_val = tab->b_val = 0;

    fclose(f1);
    fclose(f2);
}

int checkPos(tab_t *t, int pos){
    return (!t->mark_pos[pos]);
}

int checkSomma(tab_t *t){
    int i, j, id, prev, c_somma=0, check=1;
    sol_t *riga;

    // somma su righe
    for (i=0; i<t->r; i++){
        riga = t->board[i];
        for (j=1; j<t->c && check==1; j++){
            prev = riga[j-1].id;
            id = riga[j].id;
            if (riga[j].rot==0){
                if (riga[j-1].rot == 0){
                    if (t->tiles[prev].c1 != t->tiles[id].c1)
                        check=0;
                } else{
                    if (t->tiles[prev].c2 != t->tiles[id].c1)
                        check=0;
                }
            } else{
                if (riga[j-1].rot == 0){
                    if (t->tiles[prev].c1 != t->tiles[id].c2)
                        check=0;
                } else{
                    if (t->tiles[prev].c2 != t->tiles[id].c2)
                        check=0;
                }
            }
        }
        if (check){
            for (j=0; j<t->c; j++){
                id = riga[j].id;
                if (riga[j].rot == 0){
                    c_somma += t->tiles[id].v1;
                }
                else{
                    c_somma += t->tiles[id].v2;
                }
            }
        }
    }

    check = 1;
    // somma su colonne
    for (j=0; j<t->c; j++){
        for (i=1; i<t->r && check==1; i++){
            prev = t->board[i-1][j].id;
            id = t->board[i][j].id;
            if (t->board[i][j].rot == 0){
                if (t->board[i-1][j].rot == 0){
                    if (t->tiles[prev].c2 != t->tiles[id].c2)
                        check=0;
                } else{
                    if (t->tiles[prev].c1 != t->tiles[id].c2)
                        check=0;
                }
            } else{
                if (t->board[i-1][j].rot == 0){
                    if (t->tiles[prev].c2 != t->tiles[id].c1)
                        check=0;
                } else{
                    if (t->tiles[prev].c1 != t->tiles[id].c1)
                        check=0;
                }
            }
        }
        if (check){
            for (i=0; i<t->r; i++){
                id = t->board[i][j].id;
                if (t->board[i][j].rot==0)
                    c_somma += t->tiles[id].v2;
                else
                    c_somma += t->tiles[id].v1;
            }
        }
    }
    return c_somma;
}

void perm_s(int pos, int n, tab_t *t){
    int i, j, k;
    sol_t *riga;
    if (pos>=n){
        t->c_val = checkSomma(t);
        if (t->c_val > t->b_val){
            t->b_val = t->c_val;
            for (j=0; j<t->r; j++){
                for (k=0; k<t->c;k++){
                    t->b_board[j][k] = t->board[j][k];
                }
            }

        }
        return;
    }

    for (i=0; i<n; i++){
        if (checkPos(t, pos)){
            if (t->mark[i] == 0){
                t->mark[i]=1;
                riga = t->board[pos/3];
                riga[pos%3].id = i;
                riga[pos%3].rot = 0;
                perm_s(pos+1, n, t);
                riga[pos%3].rot = 1;
                perm_s(pos+1, n, t);
                t->mark[i] = 0;
            }
        }
        else
            perm_s(pos+1, n, t);
    }
}

void freeTot(tab_t *t){
    free(t->tiles);
    free(t->mark);
    free(t->mark_pos);

}

void free2d(tab_t t){
    int i;
    for (i=0; i<t.r; i++){
        free(t.board[i]);
        free(t.b_board[i]);
    }
    free(t.board);
    free(t.b_board);
}

int main() {
    FILE *f_tiles, *f_board;
    int i, j, val, n=aperturaFile(&f_tiles, &f_board);
    tab_t tab;
    inizializza(&tab, f_tiles, f_board, n);

    perm_s(0, n, &tab);
    for (i=0; i<tab.r; i++){
        for (j=0; j<tab.c; j++){
            printf("%d/%d ", tab.b_board[i][j].id, tab.b_board[i][j].rot);
        }
        printf("\n");
    }
    printf("%d", tab.b_val);

    freeTot(&tab);
    free2d(tab);
}