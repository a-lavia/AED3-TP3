#include "aux.h"
#include "Camino.h"

int main(int argc, char* argv[]){
    Camino caminoBL;

    caminoBL.leerEntrada();

    caminoBL.asignarSolucionGolosaJ();

    if(caminoBL.encontreSolucion()){
        #ifdef DEBUG
            cout << "Solucion golosa:" << endl;
            caminoBL.imprimirSolucion();
            cout << endl;
        #endif
            
        Camino caminoBLCopia;
        caminoBLCopia = caminoBL;

        Cambios cambiosBL;
        
        cout << "Busqueda local con vecindad = permutaCamino:" << endl;
        if(caminoBL.encontreCamino()){
            cambiosBL = caminoBL.busquedaLocal(permutaCamino);
        }
        caminoBL.imprimirSolucion();
        cout << endl;

        cout << "Busqueda local con vecindad = permutaYReemplazaPokeparadas:" << endl;
        if(caminoBLCopia.encontreCamino()){
            cambiosBL = caminoBLCopia.busquedaLocal(permutaYReemplazaPokeparadas);
        }
        caminoBLCopia.imprimirSolucion();
    } else{
        cout << -1 << endl;
    }

    return 0;
}