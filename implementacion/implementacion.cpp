#include "implementacion.h"

float distancia(Nodo n1, Nodo n2){
    int x = n1.x - n2.x;
    int y = n1.y - n2.y;
    return sqrt((x*x) + (y*y));
}

void leerEntrada(int* cantGimnasios, int* cantPokeparadas, vector<vector<float>>& matrizAdyacencia){
    cin >> *cantGimnasios;
    cin >> *cantPokeparadas;

    int cantNodos = *cantGimnasios + *cantPokeparadas;
 
    for(int i = 0; i < cantNodos; i++){
        matrizAdyacencia.push_back(vector<float>(cantNodos));
    }
    
    vector<int> pociones(cantNodos);
    
    char input;
    int nodoActual;
    vector<Nodo> nodos(cantNodos);
    for(nodoActual = 0; nodoActual < *cantGimnasios; nodoActual++){
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
}