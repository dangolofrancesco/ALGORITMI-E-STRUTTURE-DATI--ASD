//
// Created by Francesco D'Angolo on 02/01/23.
//

#include "Item.h"

Item ITEMload(char *elab, char *rete){
    Item x;
    strcpy(x.elab, elab);
    strcpy(x.rete, rete);
    return x;
}

void ITEMstore(FILE *fp, Item val){
    fprintf(fp, "Elaboratore: %s Rete: %s", val.elab, val.rete);
}

Item ITEMsetNull(){
    Item x;
    strcpy(x.elab, "");
    strcpy(x.rete, "");
    return x;
}

KEY KEYget(Item *val){
    return val->elab;
}

int KEYcmp(KEY k1, KEY k2){
    return strcmp(k1, k2);
}

void KEYscan(KEY v) {
    scanf("%s", v);
}
