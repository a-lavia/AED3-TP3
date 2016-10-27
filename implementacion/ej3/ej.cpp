#include "funciones.h"

int main(int argc, char* argv[]){
    int cantGimnasios, cantPokeparadas, tamMochila;    
    cin >> cantGimnasios;
    cin >> cantPokeparadas;
    cin >> tamMochila;

    int cantNodos = cantGimnasios + cantPokeparadas;
 
    vector<Nodo> nodos(cantNodos);
    vector<vector<float>> distancias(cantNodos, vector<float>(cantNodos));

    int nodoActual;
    for(nodoActual = 0; nodoActual < cantGimnasios; nodoActual++){
        cin >> nodos[nodoActual].x;
        cin >> nodos[nodoActual].y;
        cin >> nodos[nodoActual].pociones;  
        nodos[nodoActual].gimnasio = true;
    }
    while(nodoActual < cantNodos){
        cin >> nodos[nodoActual].x;
        cin >> nodos[nodoActual].y;
        nodos[nodoActual].pociones = 3;
        nodos[nodoActual].gimnasio = false;
        nodoActual++;
    }

    for(int i = 0; i < cantNodos; ++i){
        for(int j = 0; j < cantNodos; ++j){
            distancias[i][j] = distancia(nodos[i], nodos[j]);
        }
    }

    float distanciaTotal = 0;

    int nodoInicial = solucionInicial(nodos, distancias, tamMochila, &distanciaTotal);

    if(nodoInicial != INV){
        cout << "vecindad1:" << endl;
        busquedaLocal(nodos, distancias, distanciaTotal, cantGimnasios, nodoInicial, vecindad1);

        cout << endl << "vecindad2:" << endl;
        busquedaLocal(nodos, distancias, distanciaTotal, cantGimnasios, nodoInicial, vecindad2);
    } else{
        cout << -1 << endl;
    }

    return 0;
}