#include "funciones.h"

float distancia(Nodo n1, Nodo n2){
    int x = n1.x - n2.x;
    int y = n1.y - n2.y;
    return sqrt((x*x) + (y*y));
}

void magicBacktracking(int cantGimnasios, int cantPokeparadas, vector<vector<float>>& matrizDistancias, vector<Nodo>& nodos){

}