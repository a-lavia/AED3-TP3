#include "funciones.h"

void expAleat(ofstream& salida, Vecindad criterio){
    vector<Camino> caminos(CANT_CASOS);
    generarCaminosAleat(caminos);
    generarSalida(caminos, criterio, salida);
}

void generarCaminosAleat(vector<Camino>& caminos){
    assert(caminos.size() == CANT_CASOS);

    cout << "   Generando caminos... " << endl;

    cout << "       Generando grafos aleatorios... ";

    vector<Grafo> grafos(CANT_CASOS);

    for(int m = 0; m < CANT_CASOS; m++){
        int cantGimnasios = aleatEnRango(CANT_GIMNASIOS_MIN, CANT_GIMNASIOS_MAX);
        grafos[m] = generarGrafoAleat(cantGimnasios);
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

Grafo generarGrafoAleat(int cantGimnasios){
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

    return g;
}

void generarSalida(vector<Camino>& caminos, Vecindad criterio, ofstream& salida){
    assert(caminos.size() == CANT_CASOS);

    cout << "   Generando salida... " << endl;

    salida << "cantGimnasios,cantPokeparadas,tamMochila,distanciaOriginal,distanciaNueva,cantPermutacionesParaMejorar,cantPermutacionesParaMantener,cantReemplazosParaMejorar,cantReemplazosParaMantener,tamCamino,tiempo" << endl;
    
    int cantCaminos = caminos.size();
    
    double cantCiclosTotal;
    int cantGimnasios, cantPokeparadas, tamMochila, distanciaOriginal, distanciaNueva, tamCamino, cantNodos;
    queue<int> caminoCola, caminoColaVacia;    
    Camino caminoCopia;
    Cambios cambiosBL, cambiosBLVacio;
    
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
            tamCamino = caminoCola.size();
        } else{
            tamCamino = 0;
            distanciaNueva = caminos[c].distancia();
            cambiosBL = cambiosBLVacio;
        }

        cout << "Listo" << endl;

        tamMochila = caminos[c].tamMochila();
        distanciaOriginal = caminos[c].distancia();

        salida << cantGimnasios << "," << cantPokeparadas << "," << tamMochila << "," << distanciaOriginal << ","
        << distanciaNueva << "," << cambiosBL.cantPermutacionesParaMejorar << "," << cambiosBL.cantPermutacionesParaMantener
        << "," << cambiosBL.cantReemplazosParaMejorar << "," << cambiosBL.cantReemplazosParaMantener << "," << tamCamino << ","
        << cantCiclosTotal / (double) CANT_REPETICIONES << endl;

        cout << "       Listo" << endl;
    }

    cout << "   Listo" << endl;
}

void expAleatOp(ofstream& salida, ofstream& salidaOp, Vecindad criterio){
    vector<Camino> caminos(CANT_GIMNASIOS_MAX_OP);
    generarCaminosAleatOp(caminos);
    generarSalida(caminos, criterio, salida);
    generarSalidaOp(caminos, criterio, salidaOp);
}

void generarCaminosAleatOp(vector<Camino>& caminos){
    assert(caminos.size() == CANT_GIMNASIOS_MAX_OP + 1);

    cout << "   Generando caminos... " << endl;

    cout << "       Generando grafos aleatorios... ";

    vector<Grafo> grafos(CANT_GIMNASIOS_MAX_OP + 1);

    for(int cantGimnasios = 0; cantGimnasios < CANT_GIMNASIOS_MAX_OP + 1; cantGimnasios++){
        grafos[cantGimnasios] = generarGrafoAleat(cantGimnasios);
    }

    cout << "Listo" << endl;

    cout << "       Definiendo tamaños de mochilas... ";

    vector<int> tamMochilas(CANT_GIMNASIOS_MAX_OP + 1);
    for(int i = 0; i < CANT_GIMNASIOS_MAX_OP + 1; i++){
        tamMochilas[i] = TAM_MOCHILA;
    }

    cout << "Listo" << endl;

    for(int i = 0; i < CANT_GIMNASIOS_MAX_OP + 1; i++){
        Camino c(grafos[i], tamMochilas[i]);
        caminos[i] = c;
    }

    cout << "   Listo" << endl;
}

void generarSalidaOp(vector<Camino>& caminos, Vecindad criterio, ofstream& salidaOp){
    assert(caminos.size() == CANT_GIMNASIOS_MAX);

    cout << "   Generando salida del recorrido optimo... " << endl;

    salidaOp << "cantGimnasios,cantPokeparadas,tamMochila,distancia,tamCamino,tiempo" << endl;
    
    int cantCaminos = caminos.size();
    
    double cantCiclosTotal;
    int cantGimnasios, cantPokeparadas, tamMochila, distancia, tamCamino, cantNodos;
    queue<int> caminoCola, caminoColaVacia;    
    Camino caminoCopia;
    
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

        cout << "           Midiendo tiempos... ";
 
        cantCiclosTotal = 0;
        for(int r = 0; r < CANT_REPETICIONES_OP; r++){
            auto inicio = RELOJ();
                // Llamar al backtracking <--------------------------------------------------------
            auto fin = RELOJ();
            cantCiclosTotal += (double) chrono::duration_cast<std::chrono::nanoseconds>(fin-inicio).count();
        }

        cout << "Listo" << endl;

        tamMochila = caminos[c].tamMochila();

        salidaOp << cantGimnasios << "," << cantPokeparadas << "," << tamMochila << "," << distancia << ","
        << tamCamino << "," << cantCiclosTotal / (double) CANT_REPETICIONES << endl;

        cout << "       Listo" << endl;
    }

    cout << "   Listo" << endl;
}

void expMejor(ofstream& salida, Vecindad criterio){
    // tamMochila = max(pociones de gimnasios) * cant gimnasios para que pueda recorrer primero todas las pokeparadas.

}

void expMejorOp(ofstream& salida, Vecindad criterio){

}

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