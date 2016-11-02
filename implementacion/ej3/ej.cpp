#include "ej.h"
#include "CaminoBL.h"

int main(int argc, char* argv[]){
    CaminoBL c;

    c.leerEntrada();

    c.solucionInicial();

    if(c.encontreSolucion()){
        cout << "Solucion inicial:" << endl;
        c.imprimirSolucion();
        cout << endl;

        CaminoBL cCopia;
        cCopia = c;

        cout << "Intercambia el orden de los nodos del recorrido original:" << endl;
        c.busquedaLocal(intercambiaNodosVisitados);
        c.imprimirSolucion();
        cout << endl;
        
        cout << "Solucion inicial:" << endl;
        cCopia.imprimirSolucion();
        cout << endl;

        cout << "Intercambia pokeparadas incluyendo las que estan afuera del recorrido original:" << endl;
        cCopia.busquedaLocal(intercambiaPokeparadas);
        cCopia.imprimirSolucion();
    } else{
        cout << -1 << endl;
    }

    return 0;
}