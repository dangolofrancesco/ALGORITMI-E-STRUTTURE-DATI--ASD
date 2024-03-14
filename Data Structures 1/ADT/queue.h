//
// Created by Francesco D'Angolo on 08/12/22.
//

#ifndef MAIN_C_QUEUE_H
#define MAIN_C_QUEUE_H
#include "Item.h"

void QUEUEinit(int maxN);
int QUEUEempty();
void QUEUEput(Item val);
Item QUEUEget();

typedef struct queue *QUEUE;

QUEUE QUEUEinit(int maxN);
int QUEUEempty(QUEUE q);
void QUEUEput(QUEUE q,Item val);
Item QUEUEget (QUEUE q);


#endif //MAIN_C_QUEUE_H
