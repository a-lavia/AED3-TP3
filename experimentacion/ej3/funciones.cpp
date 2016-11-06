#include "funciones.h"

int aleatEnRango(int min, int max){
    return min + (rand() % (int)(max - min + 1));
}

int max(int a, int b){
    if(a >= b){
        return a;
    } else{
        return b;
    }
}

int min(int a, int b){
    if(a <= b){
        return a;
    } else{
        return b;
    }
}

void generarCaminosAleat(vector<Camino>& caminos, bool paraCompOp){
    assert(caminos.size() == CANT_CASOS);

    int cantGimnasiosMax;
    if(paraCompOp){
        cantGimnasiosMax = CANT_GIMNASIOS_MAX_OP;
    } else{
        cantGimnasiosMax = CANT_GIMNASIOS_MAX;
    }

    cout << "   Generando caminos... " << endl;

    cout << "       Generando grafos aleatorios... ";

    vector<Grafo> grafos(CANT_CASOS);

    for(int m = 0; m < CANT_CASOS; m++){
        int cantGimnasios = aleatEnRango(CANT_GIMNASIOS_MIN, cantGimnasiosMax);        
        vector<Nodo> gimnasios(cantGimnasios);
        
        int n;
        for(n = 0; n < cantGimnasios; n++){
            Nodo nodoNuevo;
            nodoNuevo.id = n + 1;
            nodoNuevo.x = aleatEnRango(X_MIN, X_MAX);
            nodoNuevo.y = aleatEnRango(Y_MIN, Y_MAX);
            nodoNuevo.gimnasio = true;
            nodoNuevo.pociones = aleatEnRango(POCIONES_MIN, POCIONES_MAX);
            gimnasios[n] = nodoNuevo;
        }

        int cantTotalPociones = 0;
        for(int i = 0; i < cantGimnasios; i++){
            cantTotalPociones += gimnasios[i].pociones;
        }

        int cantPokeparadas = aleatEnRango(cantTotalPociones, cantTotalPociones * 2);
        int cantNodos = cantGimnasios + cantPokeparadas;
        Grafo g(cantNodos);

        for(int i = 0; i < cantGimnasios; i++){
            g.asignarNodo(gimnasios[i]);
        }

        for( ; n < cantNodos; n++){
            Nodo nodoNuevo;
            nodoNuevo.id = n + 1;
            nodoNuevo.x = aleatEnRango(X_MIN, X_MAX);
            nodoNuevo.y = aleatEnRango(Y_MIN, Y_MAX);
            nodoNuevo.gimnasio = false;
            nodoNuevo.pociones = POCIONES_POKEPARADA;
            g.asignarNodo(nodoNuevo);
        }

        grafos[m] = g;
    }

    cout << "Listo" << endl;

    cout << "       Definiendo tamaños de mochilas... ";

    vector<int> tamMochilas(CANT_CASOS);
    for(int i = 0; i < CANT_CASOS; i++){
        tamMochilas[i] = TAM_MOCHILA;
    }

    cout << "Listo" << endl;

    for(int i = 0; i < CANT_CASOS; i++){
        Camino c(grafos[i], tamMochilas[i]);
        caminos[i] = c;
    }

    cout << "   Listo" << endl;
}

void generarSalida(vector<Camino>& caminos, Vecindad criterio, ofstream& salida){
    assert(caminos.size() == CANT_CASOS);

    cout << "   Generando salida... " << endl;

    salida << "cantGimnasios,cantPokeparadas,tamMochila,distanciaOriginal,distanciaNueva,cantPermutacionesParaMejorar,cantPermutacionesParaMantener,cantReemplazosParaMejorar,cantReemplazosParaMantener,tiempo" << endl;
    
    int cantCaminos = caminos.size();
    
    double cantCiclosTotal;
    int cantGimnasios, cantPokeparadas, tamMochila, distanciaOriginal, distanciaNueva, cantNodos;
    queue<int> caminoCola, caminoColaVacia;    
    Camino caminoCopia;
    Cambios cambiosBL;
    
    for(int c = 0; c < cantCaminos; c++){
        cout << "       Procesando camino " << c + 1 << " de " << cantCaminos << "..." << endl;

        cantGimnasios = 0;
        cantPokeparadas = 0;
        cantNodos = caminos[c].grafo().nodos().size();
        for(int n = 0; n < cantNodos; n++){
            if(caminos[c].grafo().nodos()[n].gimnasio){
                cantGimnasios++;
            } else{
                cantPokeparadas++;
            }
        }

        cout << "           Camino de " << cantGimnasios << " gimnasios y " << cantPokeparadas << " pokeparadas" << endl;

        cout << "           Hallando una solucion golosa... ";

        caminos[c].asignarSolucionGolosaJ();

        cout << "Listo" << endl;

        cout << "           Midiendo tiempos... ";
 
        cantCiclosTotal = 0;
        if(caminos[c].encontreCamino()){
            for(int r = 0; r < CANT_REPETICIONES; r++){
                caminoCola = caminoColaVacia;
                caminoCopia = caminos[c];
                auto inicio = RELOJ();
                    cambiosBL = caminoCopia.busquedaLocal(criterio);
                    distanciaNueva = caminoCopia.devolverSolucion(caminoCola);
                auto fin = RELOJ();
                cantCiclosTotal += (double) chrono::duration_cast<std::chrono::nanoseconds>(fin-inicio).count();
            }
        }

        cout << "Listo" << endl;

        tamMochila = caminos[c].tamMochila();
        distanciaOriginal = caminos[c].distancia();

        salida << cantGimnasios << "," << cantPokeparadas << "," << tamMochila << "," << distanciaOriginal << ","
        << distanciaNueva << "," << cambiosBL.cantPermutacionesParaMejorar << "," << cambiosBL.cantPermutacionesParaMantener
        << "," << cambiosBL.cantReemplazosParaMejorar << "," << cambiosBL.cantReemplazosParaMantener << ","
        << cantCiclosTotal / (double) CANT_REPETICIONES << endl;

        cout << "       Listo" << endl;
    }

    cout << "   Listo" << endl;
}

void expAleat(ofstream& salida, Vecindad criterio){
    vector<Camino> caminos(CANT_CASOS);
    generarCaminosAleat(caminos, false);

    generarSalida(caminos, criterio, salida);
}

void expOpAleat(ofstream& salida, Vecindad criterio){

}

void expMejor(ofstream& salida, Vecindad criterio){
    // tamMochila = max(pociones de gimnasios) * cant gimnasios para que pueda recorrer primero todas las pokeparadas.

}

void expOpMejor(ofstream& salida, Vecindad criterio){

}