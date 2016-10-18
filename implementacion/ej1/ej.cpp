#include "funciones.h"

using namespace std;

int main (int argc, char* argv[]) {
    
    int cantGimnasios;
    int cantPokeparadas;
    int cantNodos;
    
    int gimnasioActual = 0;
    int pokeparadaActual = 0;


    cin >> cantGimnasios;
    cin >> cantPokeparadas;
    cantNodos = cantGimnasios + cantPokeparadas;
 
    vector<Nodo> nodos(cantNodos);
    vector<vector<float>> matrizAdyacencia(cantNodos, vector<float>(cantNodos));
    vector<int> pociones(cantNodos);
    char input;
    int nodoActual;
    for(nodoActual = 0; nodoActual < cantGimnasios; nodoActual++){
        cin >> nodos[nodoActual].x;
        cin >> nodos[nodoActual].y;
        cin >> nodos[nodoActual].pociones;  
    }
    for(; nodoActual < cantNodos; nodoActual++){
        cin >> nodos[nodoActual].x;
        cin >> nodos[nodoActual].y;
        nodos[nodoActual].pociones = 3;
    }

    for (int i = 0; i < cantNodos; ++i){
        cout << "Id: " << i << " X: " << nodos[i].x << " Y: " << nodos[i].x << " P:" << nodos[i].pociones << endl;
    }
    
    for(int i = 0; i < cantNodos; ++i){
        for(int j = 0; j < cantNodos; ++j){
            matrizAdyacencia[i][j] = distancia(nodos[i], nodos[j]);
            cout << matrizAdyacencia[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}