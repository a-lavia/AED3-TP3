#include "aux.h"
#include "Camino.h"

/*void leerCamino() {

	int camino;
	cin >> camino;
	float dist;
	cin >> dist;
	queue<int> solucion;
	for(int i = 0; i < camino; i++) {
		int n;
		cin >> n;
		solucion.push(n-1);
	}
	caminoBL.asignarSolucion(dist, solucion);

	caminoBL.busquedaLocal(permutaCamino);
}*/

int main(int argc, char* argv[]){
    Camino caminoBL;

    caminoBL.leerEntrada();

    caminoBL.asignarSolucionGolosa();

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
