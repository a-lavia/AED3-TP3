#include "parser.h"

int main (int argc, char* argv[]) {
    int cantGimnasios, cantPokeparadas;
    //vector<vector<float>> matrizDistancias;
    //vector<Nodo> nodos;
    list<Nodo> nodos;
    int mochila;
    leerEntrada(cantGimnasios, cantPokeparadas, nodos, mochila);

    list<Nodo> vacia;
    int pociones = 0;
    int gimnasiosVencidos = 0;
    Solucion mejorSolucionActual;
    mejorSolucionActual.distanciaRecorrida = -8;
    magicBacktracking(cantGimnasios, vacia, nodos, gimnasiosVencidos, 0, mochila, 0, mejorSolucionActual);
    mejorSolucionActual.showMe();
    //cout << "Mejor distancia: " << mejorSolucionActual.distanciaRecorrida << endl; 
    return 0;
}