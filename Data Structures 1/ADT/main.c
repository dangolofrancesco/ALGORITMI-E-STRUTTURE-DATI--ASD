#include <stdio.h>
#include <stdlib.h>

#include "complex.h"
#include "Item.h"

int main() {



}

int GETindex(Key k) {
    int i=0, b=26;
    for (; *k!='0'; k++){
        i = (b*i + (*k-((int) 'A')));
    }
    return i;
}


