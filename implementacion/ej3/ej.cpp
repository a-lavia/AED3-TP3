#include "ej.h"
#include "Camino.h"

int main(int argc, char* argv[]){
    Camino c;

    c.leerEntrada();

    c.solucionGolosa();

    if(c.encontreSolucion()){
        cout << "Solucion golosa:" << endl;
        c.imprimirSolucion();
        cout << endl;

        Camino cCopia;
        cCopia = c;

        cout << "Intercambia el orden de los nodos del recorrido original:" << endl;
        c.busquedaLocal(intercambiaNodosVisitados);
        c.imprimirSolucion();
        cout << endl;

        cout << "Intercambia pokeparadas incluyendo las que estan afuera del recorrido original:" << endl;
        cCopia.busquedaLocal(intercambiaPokeparadas);
        cCopia.imprimirSolucion();
    } else{
        cout << -1 << endl;
    }

    return 0;
}