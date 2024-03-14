//
// Created by Francesco D'Angolo on 26/11/22.
//

//complex.c
#include "complex.h"

struct complex_s{
    float Re;
    float Im;
};

Complex crea(void ){
    Complex c = malloc(sizeof (*c));
    return c;
}

Complex prod(Complex c1, Complex c2){
    Complex c = crea();
    c->Re = c1->Re * c2->Re - c1->Im * c2->Im;
    c->Im = c1->Re * c2->Im + c1->Re * c2->Im;
}