#include "aux.h"

float distanciaNodos(Nodo n1, Nodo n2){
    float x = n1.x - n2.x;
    float y = n1.y - n2.y;
    return sqrt((x*x) + (y*y));
}