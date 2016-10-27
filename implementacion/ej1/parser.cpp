#include "parser.h"

void leerEntrada(int& cantGimnasios, int& cantPokeparadas, vector<vector<float>>& matrizDistancias, vector<Nodo>& nodos){
    cin >> cantGimnasios;
    cin >> cantPokeparadas;

    int cantNodos = cantGimnasios + cantPokeparadas;
    nodos.resize(cantNodos);
 
    matrizDistancias.resize(cantNodos);
    for(int i = 0; i < cantNodos; i++){ 
        matrizDistancias[i].resize(cantNodos);
    }
        
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
            matrizDistancias[i][j] = distancia(nodos[i], nodos[j]);
            cout << matrizDistancias[i][j] << " ";
        }
        cout << endl;
    }
}