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

void generarGrafosAleat(vector<Grafo>& grafos){
    assert(grafos.size() == CANT_MEDICIONES);

    cout << "   Generando grafos aleatorios... ";

    for(int m = 0; m < CANT_MEDICIONES; m++){
        int cantGimnasios = aleatEnRango(0, CANT_GIMNASIOS_MAX);        
        
        // Asumo que voy a usar estos grafos con mochilas lo suficientemente grandes:
        int cantPokeparadas = (POCIONES_MAX*cantGimnasios)/3 + 1;
        
        int cantNodos = cantGimnasios + cantPokeparadas;
        
        Grafo g(cantNodos);

        int n;
        for(n = 0; n < cantGimnasios; n++){
            Nodo nodoNuevo;
            nodoNuevo.id = n + 1;
            nodoNuevo.x = aleatEnRango(0, X_MAX);
            nodoNuevo.y = aleatEnRango(0, Y_MAX);
            nodoNuevo.gimnasio = true;
            nodoNuevo.pociones = aleatEnRango(0, POCIONES_MAX);
        }

        for( ; n < cantNodos; n++){
            Nodo nodoNuevo;
            nodoNuevo.id = n + 1;
            nodoNuevo.x = aleatEnRango(0, X_MAX);
            nodoNuevo.y = aleatEnRango(0, Y_MAX);
            nodoNuevo.gimnasio = false;
            nodoNuevo.pociones = POCIONES_POKEPARADA;
        }

        grafos[m] = g;
    }

    cout << "Listo" << endl;
}

void generarGrafosOpAleat(vector<Grafo>& grafos){
    // Modificar para que tenga solucion
    assert(grafos.size() == CANT_MEDICIONES);

    for(int m = 0; m < CANT_MEDICIONES; m++){
        int cantNodos = aleatEnRango(0, CANT_NODOS_OP_MAX);
        Grafo g(cantNodos);

        for(int n = 0; n < cantNodos; n++){
            Nodo nodoNuevo;
            nodoNuevo.id = n + 1;
            nodoNuevo.x = aleatEnRango(0, X_MAX);
            nodoNuevo.y = aleatEnRango(0, Y_MAX);
            if(rand() % 2 == 0){
                nodoNuevo.gimnasio = true;
                nodoNuevo.pociones = aleatEnRango(0, POCIONES_MAX);
            } else{
                nodoNuevo.gimnasio = true;
                nodoNuevo.pociones = POCIONES_POKEPARADA;
            }
        }
        
        grafos[m] = g;
    }
}

void generarGrafosMejor(vector<Grafo>& grafos){
    // Modificar para que tenga solucion
    assert(grafos.size() == CANT_MEDICIONES);

    for(int m = 0; m < CANT_MEDICIONES; m++){
        int cantNodos = aleatEnRango(0, CANT_NODOS_MAX);
        Grafo g(cantNodos);

        for(int n = 0; n < cantNodos / 2; n++){
            Nodo nodoNuevo;
            nodoNuevo.id = n + 1;
            nodoNuevo.x = aleatEnRango(0, X_MAX / 2);
            nodoNuevo.y = aleatEnRango(0, Y_MAX / 2);
            nodoNuevo.gimnasio = true;
            nodoNuevo.pociones = POCIONES_POKEPARADA;
        }

        for(int n = cantNodos / 2; n < cantNodos; n++){
            Nodo nodoNuevo;
            nodoNuevo.id = n + 1;
            nodoNuevo.x = aleatEnRango(X_MAX / 2, X_MAX);
            nodoNuevo.y = aleatEnRango(Y_MAX / 2, Y_MAX);
            nodoNuevo.gimnasio = true;
            nodoNuevo.pociones = aleatEnRango(0, POCIONES_MAX);
        }

        grafos[m] = g;
    }
}

void generarGrafosOpMejor(vector<Grafo>& grafos){
    // Modificar para que tenga solucion
    assert(grafos.size() == CANT_MEDICIONES);

    for(int m = 0; m < CANT_MEDICIONES; m++){
        int cantNodos = aleatEnRango(0, CANT_NODOS_OP_MAX);
        Grafo g(cantNodos);

        for(int n = 0; n < cantNodos / 2; n++){
            Nodo nodoNuevo;
            nodoNuevo.id = n + 1;
            nodoNuevo.x = aleatEnRango(0, X_MAX / 2);
            nodoNuevo.y = aleatEnRango(0, Y_MAX / 2);
            nodoNuevo.gimnasio = true;
            nodoNuevo.pociones = POCIONES_POKEPARADA;
        }

        for(int n = cantNodos / 2; n < cantNodos; n++){
            Nodo nodoNuevo;
            nodoNuevo.id = n + 1;
            nodoNuevo.x = aleatEnRango(X_MAX / 2, X_MAX);
            nodoNuevo.y = aleatEnRango(Y_MAX / 2, Y_MAX);
            nodoNuevo.gimnasio = true;
            nodoNuevo.pociones = aleatEnRango(0, POCIONES_MAX);
        }

        grafos[m] = g;
    }
}

void generarCaminos(vector<Grafo>& grafos, vector<int>& tamMochilas, vector<Camino>& caminos){
    assert(grafos.size() == CANT_MEDICIONES && tamMochilas.size() == CANT_MEDICIONES && caminos.size() == CANT_MEDICIONES);

    cout << "   Generando caminos... ";

    int cantCaminos = grafos.size();
    for(int i = 0; i < cantCaminos; i++){
        Camino c(grafos[i], tamMochilas[i]);
        caminos[i] = c;
    }

    cout << "Listo" << endl;
}

void generarSalida(vector<Camino>& caminos, Vecindad criterio, ofstream& salida){
    assert(caminos.size() == CANT_MEDICIONES);

    cout << "   Generando salida... " << endl;

    salida << "cantGimnasios,cantPokeparadas,tamMochila,criterio,distancia,tamCamino,tiempo" << endl;
    // cant iteraciones <--------------------------------------------------------------------------------------------------
    
    int cantCaminos = caminos.size();
    double cantCiclosTotal;
    int cantGimnasios, cantPokeparadas, tamMochila, distancia, tamCamino, cantNodos;
    queue<int> caminoCola, caminoColaVacia;
    Camino caminoCopia;
    
    for(int c = 0; c < cantCaminos; c++){

        cout << "       Procesando camino " << c + 1 << " de " << cantCaminos << "... ";

        tamMochila = caminos[c].tamMochila();

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

        cantCiclosTotal = 0;
        for(int r = 0; r < CANT_REPETICIONES; r++){
            caminoCola = caminoColaVacia;
            caminoCopia = caminos[c];
            auto inicio = RELOJ();
                caminoCopia.busquedaLocal(criterio);
                distancia = caminoCopia.devolverSolucion(caminoCola);
            auto fin = RELOJ();
            cantCiclosTotal += (double) chrono::duration_cast<std::chrono::nanoseconds>(fin-inicio).count();
        }

        tamCamino = caminoCola.size();

        salida << cantGimnasios << "," << cantPokeparadas << "," << tamMochila << "," << criterio << ","
               << distancia << "," << tamCamino << "," << cantCiclosTotal / (double) CANT_REPETICIONES << endl;

        cout << "Listo" << endl;
    }

    cout << "Listo" << endl;
}

void expAleat(ofstream& salida, Vecindad criterio){
    vector<Grafo> grafos(CANT_MEDICIONES);
    generarGrafosAleat(grafos);

    cout << "   Definiendo tamaños de mochilas... ";

    vector<int> tamMochilas(CANT_MEDICIONES);
    /*for(int i = 0; i < CANT_MEDICIONES; i++){
        tamMochilas[i] = aleatEnRango(POCIONES_MAX + 2, TAM_MOCHILA_MAX);
    }*/
    for(int i = 0; i < CANT_MEDICIONES; i++){
        tamMochilas[i] = POCIONES_MAX * CANT_GIMNASIOS_MAX;
    }

    cout << "Listo" << endl;

    vector<Camino> caminos(CANT_MEDICIONES);

    generarCaminos(grafos, tamMochilas, caminos);

    generarSalida(caminos, criterio, salida);
}

void expOpAleat(ofstream& salida, Vecindad criterio){

}

void expMejor(ofstream& salida, Vecindad criterio){
    // tamMochila = max(pociones de gimnasios) * cant gimnasios para que pueda recorrer primero todas las pokeparadas.

}

void expOpMejor(ofstream& salida, Vecindad criterio){

}