#include "aux.h"
#include "Camino.h"

int main(int argc, char* argv[]){
    Camino c;

    c.leerEntrada();

    c.solucionGolosaJ();

    if(c.encontreSolucion()){
        #ifdef DEBUG
            cout << "Solucion golosa:" << endl;
            c.imprimirSolucion();
            cout << endl;
        #endif
            
        Camino cCopia;
        cCopia = c;

        cout << "Busqueda local con vecindad = permutaCamino:" << endl;
        c.busquedaLocal(permutaCamino);
        c.imprimirSolucion();
        cout << endl;

        cout << "Busqueda local con vecindad = permutaYReemplazaPokeparadas:" << endl;
        cCopia.busquedaLocal(permutaYReemplazaPokeparadas);
        cCopia.imprimirSolucion();
    } else{
        cout << -1 << endl;
    }

    return 0;
}