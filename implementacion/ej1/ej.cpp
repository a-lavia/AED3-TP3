#include "parser.h"

int main (int argc, char* argv[]) {
    int cantGimnasios, cantPokeparadas;
    vector<vector<float>> matrizDistancias;
    vector<Nodo> nodos;
    leerEntrada(cantGimnasios, cantPokeparadas, matrizDistancias, nodos);

    int pociones = 0;
    int gimnasioActual = 0;
    int pokeparadaActual = 0;
    
    magicBacktracking(cantGimnasios, cantPokeparadas, matrizDistancias, nodos);

    return 0;
}