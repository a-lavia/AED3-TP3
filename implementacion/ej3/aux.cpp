#include "aux.h"

double distanciaNodos(Nodo n1, Nodo n2){
    double x = n1.x - n2.x;
    double y = n1.y - n2.y;
    return sqrt((x*x) + (y*y));
}