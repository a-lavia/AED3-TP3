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
    // Modificar para que tenga solucion
    for(int m = 0; m < CANT_MEDICIONES; m++){
        int cantNodos = aleatEnRango(0, CANT_NODOS_MAX);
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
        grafos.push_back(g);
    }
}

void generarGrafosOpAleat(vector<Grafo>& grafos){
    // Modificar para que tenga solucion
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
        
        grafos.push_back(g);
    }
}

void generarGrafosMejor(vector<Grafo>& grafos){
    // Modificar para que tenga solucion
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

        grafos.push_back(g);
    }
}

void generarGrafosOpMejor(vector<Grafo>& grafos){
    // Modificar para que tenga solucion
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

        grafos.push_back(g);
    }
}

void generarCaminos(vector<Grafo>& grafos, vector<int> tamMochilas, vector<Camino>& caminos){
    // tamMochila = max(pociones de gimnasios) * cant gimnasios

    assert(grafos.size() == tamMochilas.size());

    int cantCaminos = grafos.size();
    for(int i = 0; i < cantCaminos; i++){
        Camino c(grafos[i], tamMochilas[i]);
        caminos.push_back(c);
    }
}

void generarSalida(vector<Camino>& caminos, Vecindad criterio, ofstream& salida){
    salida << "cantGimnasios,cantPokeparadas,tamMochila,criterio,distancia,tamCamino,tiempo" << endl;
    
    int cantCaminos = caminos.size();
    double cantCiclosTotal;
    int cantGimnasios, cantPokeparadas, tamMochila, distancia, tamCamino, cantNodos;
    queue<int> caminoCola, caminoColaVacia;
    
    for(int c = 0; c < cantCaminos; c++){
        tamMochila = caminos[c].tamMochila();
        Camino caminoCopia = caminos[c];

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
    }
}

void expAleat(ofstream& salida){

}

void expOpAleat(ofstream& salida){

}

void expMejor(ofstream& salida){

}

void expOpMejor(ofstream& salida){

}