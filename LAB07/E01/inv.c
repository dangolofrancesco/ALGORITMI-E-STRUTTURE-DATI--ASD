//
// Created by Francesco D'Angolo on 14/12/22.
//

#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, "%d", &statp->hp);
    fscanf(fp, "%d", &statp->mp);
    fscanf(fp, "%d", &statp->atk);
    fscanf(fp, "%d", &statp->def);
    fscanf(fp, "%d", &statp->mag);
    fscanf(fp, "%d", &statp->spr);
}

void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp, "%s", invp->nome);
    fscanf(fp, "%s", invp->tipo);
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
    if (statp->hp>soglia)
        printf("%d ", statp->hp);
    if (statp->mp>soglia)
        printf("%d ", statp->mp);
    if (statp->atk>soglia)
        printf("%d ", statp->atk);
    if (statp->def>soglia)
        printf("%d ", statp->def);
    if (statp->mag>soglia)
        printf("%d ", statp->mag);
    if (statp->spr>soglia)
        printf("%d ", statp->spr);
}

void inv_print(FILE *fp, inv_t *invp){
    printf("%s %s ", invp->nome, invp->tipo);
}

stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}

