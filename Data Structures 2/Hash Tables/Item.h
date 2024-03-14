//
// Created by Francesco D'Angolo on 27/11/22.
//

#ifndef ADT_ITEM_H
#define ADT_ITEM_H

typedef struct item *Item;
typedef char *Key

Key KEYget(Item val);
Key KEYscan();
int KEYcmp(Key k1, Key k2);
int KEYeq(Key k1, Key k2);
int KEYless(Key k1, Key k2);
Item ITEMnew();
void ITEMfree(Item val);
Item ITEMscan();
void ITEMstore(Item val);
int ITEMless(Item val1, Item val2); int ITEMgreater(Item val1, Item val2); int ITEMcheckvoid(Item val);
int ITEMeq(Item val1, Item val2);
Item ITEMsetNull();


#endif //ADT_ITEM_H
