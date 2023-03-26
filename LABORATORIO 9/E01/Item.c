//
// Created by Francesco D'Angolo on 13/01/23.
//

#include "Item.h"

Item ITEMload(char *val){
    Item x;
    strcpy(x.id, val);
    return x;
}

void ITEMstore(Item val){
    printf("%s", val.id);
}

Item ITEMsetNull(){
    Item x;
    strcpy(x.id, "");
    return x;
}

KEY KEYget(Item *val){
    return val->id;
}

int KEYcmp(KEY k1, KEY k2){
    return strcmp(k1, k2);
}

void KEYscan(KEY v) {
    scanf("%s", v);
}
