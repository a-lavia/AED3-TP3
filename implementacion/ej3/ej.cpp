#include "ej.h"
#include "CaminoBL.h"

int main(int argc, char* argv[]){
    CaminoBL c;

    c.leerEntrada();

    c.solucionInicial();

    if(c.nodoInicial() != NULL){
        CaminoBL cCopia = c;

        cout << "Intercambia el orden de los nodos del recorrido original:" << endl;
        c.busquedaLocal(intercambiaNodosVisitados);
        c.imprimirSolucion();

        cout << endl << "Intercambia pokeparadas incluyendo las que estan afuera del recorrido original:" << endl;
        cCopia.busquedaLocal(intercambiaPokeparadas);
        cCopia.imprimirSolucion();
    } else{
        cout << -1 << endl;
    }

    return 0;
}