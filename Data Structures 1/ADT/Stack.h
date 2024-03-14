//
// Created by Francesco D'Angolo on 07/12/22.
//

#ifndef MAIN_C_STACK_H
#define MAIN_C_STACK_H

#include "Item.h"


/*QUasi ADT
 * void STACKinit(int maxN);
int STACKempty();
void STACKpush(Item val);
Item STACKpop();*/

//puntatore opaco (handle)
typedef struct stack *STACK;

STACK STACKinit(int maxN);
int STACKempty(STACK sp);
void STACKpush(STACK sp, Item val);
Item STACKpop (STACK sp);

#endif //MAIN_C_STACK_H
