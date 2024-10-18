#include "lista.h"
#include <iostream>
#include "r1.h"

int main()
{
   Lista l;
   l=creare();
   tipar(l);
   printf("LCM: %d\n", lcmmultiple(l._prim));
   printf("Maximum in the list: %d\n", maximum(l._prim));
}
