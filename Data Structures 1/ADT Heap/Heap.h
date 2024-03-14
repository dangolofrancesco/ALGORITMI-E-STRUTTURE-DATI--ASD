//
// Created by Francesco D'Angolo on 16/12/22.
//

#ifndef ADT_HEAP_HEAP_H
#define ADT_HEAP_HEAP_H

#include <stdio.h>
#include <stdlib.h>


typedef struct heap *Heap;

Heap HEAPinit(int maxN);
Void HEAPfree(Heap h);
void HEAPfill(Heap h, Item val);
void HEAPsort(Heap h);
void HEAPdisplay(Heap h);
void HEAPify(Heap h, int i);


#endif //ADT_HEAP_HEAP_H
