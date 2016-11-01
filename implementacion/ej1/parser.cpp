#include "parser.h"

void leerEntrada(int& cantGimnasios, int& cantPokeparadas, list<Nodo>& nodos, int& mochila){
    cin >> cantGimnasios;
    cin >> cantPokeparadas;
    cin >> mochila;
    int cantNodos = cantGimnasios + cantPokeparadas;
    //nodos.resize(cantNodos);
 
    /*matrizDistancias.resize(cantNodos);
    for(int i = 0; i < cantNodos; i++){ 
        matrizDistancias[i].resize(cantNodos);
    }*/
        
    
//    list<Nodo> nodos;
    
    int nodoActual;
    int id;
    int x;
    int y;
    int pociones;

    for(nodoActual = 0; nodoActual < cantGimnasios; nodoActual++){
        id = nodoActual + 1;
        cin >> x;
        cin >> y;
        cin >> pociones;
        pociones = - pociones;
        nodos.push_back(Nodo(id, x, y, pociones));
        /*cin >> nodos[nodoActual].x;
        cin >> nodos[nodoActual].y;
        cin >> nodos[nodoActual].pociones;
        nodos[nodoActual].id = nodoActual+1;*/
    }

    for(; nodoActual < cantNodos; nodoActual++){
        id = nodoActual + 1;
        cin >> x;
        cin >> y;
        pociones = 3;
        nodos.push_back(Nodo(id, x, y, pociones));
        /*cin >> nodos[nodoActual].x;
        cin >> nodos[nodoActual].y;
        nodos[nodoActual].pociones = 3;
        nodos[nodoActual].id = nodoActual+1;*/
    }

/*    for (int i = 0; i < cantNodos; ++i){
        nodos[i].showMe();
    }*/
    
    /*for(list<Nodo>::iterator itNodos = nodos.begin(), end = nodos.end(); itNodos != end; ++itNodos){
        itNodos->showMe();
    }*/

    /*for(int i = 0; i < cantNodos; ++i){
        for(int j = 0; j < cantNodos; ++j){
            matrizDistancias[i][j] = distancia(nodos[i], nodos[j]);
            cout << matrizDistancias[i][j] << " ";
        }
        cout << endl;
    }*/
}