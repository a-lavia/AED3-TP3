#include "parser.h"

int main (int argc, char* argv[]) {
    int cantGimnasios, cantPokeparadas;
    //vector<vector<float>> matrizDistancias;
    //vector<Nodo> nodos;
    list<Nodo> nodos;
    leerEntrada(cantGimnasios, cantPokeparadas, nodos);

    list<Nodo> vacia;
    int pociones = 0;
    int gimnasioActual = 0;
    int pokeparadaActual = 0;
    int gimnasiosVencidos = 0;
    magicBacktracking(cantGimnasios, vacia, nodos, gimnasiosVencidos);

    return 0;
}