#include "ej.h"
#include "Grafo.h"
#include "CaminoBL.h"

int main(int argc, char* argv[]){
    int cantGimnasios, cantPokeparadas, tamMochila;    
    cin >> cantGimnasios;
    cin >> cantPokeparadas;
    cin >> tamMochila;

    int cantNodos = cantGimnasios + cantPokeparadas;

    Grafo g(cantNodos);

    int nodoActual;
    for(nodoActual = 0; nodoActual < cantGimnasios; nodoActual++){
        Nodo nodoNuevo;
        nodoNuevo.id = nodoActual + 1;
        cin >> nodoNuevo.x;
        cin >> nodoNuevo.y;
        cin >> nodoNuevo.pociones;  
        nodoNuevo.gimnasio = true;
        g.asignarNodo(nodoNuevo);
    }
    while(nodoActual < cantNodos){
        Nodo nodoNuevo;
        nodoNuevo.id = nodoActual + 1;
        cin >> nodoNuevo.x;
        cin >> nodoNuevo.y;
        nodoNuevo.pociones = POCIONES_POKEPARADA;
        nodoNuevo.gimnasio = false;
        g.asignarNodo(nodoNuevo);
        nodoActual++;
    }

    for(int i = 0; i < cantNodos; ++i){
        for(int j = 0; j < cantNodos; ++j){
            Nodo n1 = g.nodos()[i];
            Nodo n2 = g.nodos()[j];
            g.asignarDistancia(n1, n2, distanciaNodos(n1, n2));
        }
    }

    CaminoBL c(g, tamMochila);

    c.solucionInicial();

    if(c.nodoInicial() != NULL){
        CaminoBL cCopia = c;

        cout << "vecindad1:" << endl;
        c.busquedaLocal(vecindad1);

        cout << endl << "vecindad2:" << endl;
        cCopia.busquedaLocal(vecindad2);
    } else{
        cout << -1 << endl;
    }

    return 0;
}