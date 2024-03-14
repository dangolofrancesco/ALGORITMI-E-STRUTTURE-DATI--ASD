//
// Created by Francesco D'Angolo on 26/11/22.
//

#ifndef ADT_COMPLEX_H
#define ADT_COMPLEX_H

//complex.h
//puntatore a struct (struct definita nel file complex.c)
typedef struct complex_s *Complex;


Complex crea(void);
void distruggi(Complex c);
Complex prod(Complex c1, Complex c2);

#endif //ADT_COMPLEX_H
