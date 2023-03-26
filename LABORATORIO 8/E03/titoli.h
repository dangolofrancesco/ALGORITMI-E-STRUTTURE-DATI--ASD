//
// Created by Francesco D'Angolo on 06/01/23.
//

#ifndef E03_TITOLI_H
#define E03_TITOLI_H

#include "titolo.h"

typedef struct titoli_s *titoli_t;

titoli_t LISTinit();
void LISTins(titoli_t lista, KEY titolo);
titolo_t LISTAgetTitolo(titoli_t lista, KEY titolo);
void LISTstore(FILE *fp, titoli_t list);

#endif //E03_TITOLI_H
