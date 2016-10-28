#include "ej.h"
#include "grafo.h"

int main(int argc, char* argv[]){
    int cantGimnasios, cantPokeparadas, tamMochila;    
    cin >> cantGimnasios;
    cin >> cantPokeparadas;
    cin >> tamMochila;

    int cantNodos = cantGimnasios + cantPokeparadas;

    Grafo grafo(cantNodos);

    int nodoActual;
    for(nodoActual = 0; nodoActual < cantGimnasios; nodoActual++){
        Nodo nodoNuevo;
        nodoNuevo.id = nodoActual + 1;
        cin >> nodoNuevo.x;
        cin >> nodoNuevo.y;
        cin >> nodoNuevo.pociones;  
        nodoNuevo.gimnasio = true;
        grafo.asignarNodo(nodoNuevo);
    }
    while(nodoActual < cantNodos){
        Nodo nodoNuevo;
        nodoNuevo.id = nodoActual + 1;
        cin >> nodoNuevo.x;
        cin >> nodoNuevo.y;
        nodoNuevo.pociones = 3;
        nodoNuevo.gimnasio = false;
        grafo.asignarNodo(nodoNuevo);
        nodoActual++;
    }

    for(int i = 0; i < cantNodos; ++i){
        for(int j = 0; j < cantNodos; ++j){
            Nodo n1 = grafo.nodos()[i];
            Nodo n2 = grafo.nodos()[j];
            grafo.asignarDistancia(n1, n2, distanciaNodos(n1, n2));
        }
    }

    float distanciaTotal = 0;

    int nodoInicial = grafo.solucionInicial(tamMochila, &distanciaTotal);

    if(nodoInicial != INV){
        Grafo grafoCopia = grafo;

        cout << "vecindad1:" << endl;
        grafo.busquedaLocal(distanciaTotal, cantGimnasios, nodoInicial, vecindad1);

        cout << endl << "vecindad2:" << endl;
        grafoCopia.busquedaLocal(distanciaTotal, cantGimnasios, nodoInicial, vecindad2);
    } else{
        cout << -1 << endl;
    }

    return 0;
}