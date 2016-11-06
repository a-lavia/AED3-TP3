#include "funciones.h"

void generarCaminosAleat(vector<Camino>& caminos){
    assert(caminos.size() == CANT_CASOS);

    cout << "Generando caminos... " << endl;

    cout << "   Generando grafos... ";

    vector<Grafo> grafos(CANT_CASOS);

    for(int m = 0; m < CANT_CASOS; m++){
        int cantGimnasios = aleatEnRango(CANT_GIMNASIOS_MIN, CANT_GIMNASIOS_MAX);
        grafos[m] = generarGrafoAleat(cantGimnasios);
    }

    cout << "Listo" << endl;

    cout << "   Definiendo tamaños de mochilas... ";

    vector<int> tamMochilas(CANT_CASOS);
    for(int i = 0; i < CANT_CASOS; i++){
        tamMochilas[i] = TAM_MOCHILA;
    }

    cout << "Listo" << endl;

    for(int i = 0; i < CANT_CASOS; i++){
        Camino c(grafos[i], tamMochilas[i]);
        caminos[i] = c;
    }

    cout << "Listo" << endl;
}

Grafo generarGrafoAleat(int cantGimnasios){
    vector<Nodo> gimnasios(cantGimnasios);
        
    int n = 0;
    while(n < cantGimnasios){
        Nodo nodoNuevo;
        nodoNuevo.id = n + 1;
        nodoNuevo.x = aleatEnRango(X_MIN, X_MAX);
        nodoNuevo.y = aleatEnRango(Y_MIN, Y_MAX);
        nodoNuevo.gimnasio = true;
        nodoNuevo.pociones = aleatEnRango(POCIONES_MIN, POCIONES_MAX);
        gimnasios[n] = nodoNuevo;
        n++;
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

    while(n < cantNodos){
        Nodo nodoNuevo;
        nodoNuevo.id = n + 1;
        nodoNuevo.x = aleatEnRango(X_MIN, X_MAX);
        nodoNuevo.y = aleatEnRango(Y_MIN, Y_MAX);
        nodoNuevo.gimnasio = false;
        nodoNuevo.pociones = POCIONES_POKEPARADA;
        g.asignarNodo(nodoNuevo);
        n++;
    }

    return g;
}

void asignarSolucionesJ(vector<Camino>& caminos){
    cout << "Hallando soluciones golosas para los caminos... ";

    int cantCaminos = caminos.size();
    for(int c = 0; c < cantCaminos; c++){
        caminos[c].asignarSolucionGolosaJ();
    }
    
    cout << "Listo" << endl;
}

void generarSalidaBL(vector<Camino>& caminos, Vecindad criterio, ofstream& salida){
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

void generarCaminosAleatOp(vector<Camino>& caminos){
    assert(caminos.size() == CANT_NODOS_MAX_OP + 1);

    cout << "Generando caminos... " << endl;

    cout << "   Generando grafos... ";

    vector<Grafo> grafos(CANT_NODOS_MAX_OP + 1);

    for(int n = 0; n < CANT_NODOS_MAX_OP + 1; n++){
        int cantGimnasios = min(aleatEnRango(min(CANT_GIMNASIOS_MIN,n), n), CANT_GIMNASIOS_MAX_OP);
        grafos[n] = generarGrafoAleatOp(cantGimnasios, n - cantGimnasios); 
    }

    cout << "Listo" << endl;

    cout << "   Definiendo tamaños de mochilas... ";

    vector<int> tamMochilas(CANT_NODOS_MAX_OP + 1);
    for(int i = 0; i < CANT_NODOS_MAX_OP + 1; i++){
        tamMochilas[i] = TAM_MOCHILA;
    }

    cout << "Listo" << endl;

    for(int i = 0; i < CANT_NODOS_MAX_OP + 1; i++){
        Camino c(grafos[i], tamMochilas[i]);
        caminos[i] = c;
    }

    cout << "Listo" << endl;
}

Grafo generarGrafoAleatOp(int cantGimnasios, int cantPokeparadas){
    int cantNodos = cantGimnasios + cantPokeparadas;
    Grafo g(cantNodos);   

    int pocionesMax;
    if(cantGimnasios > 0){
        pocionesMax = (cantPokeparadas * 3) / cantGimnasios;
    }

    int n = 0;
    while(n < cantGimnasios){
        Nodo nodoNuevo;
        nodoNuevo.id = n + 1;
        nodoNuevo.x = aleatEnRango(X_MIN, X_MAX);
        nodoNuevo.y = aleatEnRango(Y_MIN, Y_MAX);
        nodoNuevo.gimnasio = true;
        nodoNuevo.pociones = aleatEnRango(POCIONES_MIN, min(pocionesMax, POCIONES_MAX));
        g.asignarNodo(nodoNuevo);
        n++;
    }

    while(n < cantNodos){
        Nodo nodoNuevo;
        nodoNuevo.id = n + 1;
        nodoNuevo.x = aleatEnRango(X_MIN, X_MAX);
        nodoNuevo.y = aleatEnRango(Y_MIN, Y_MAX);
        nodoNuevo.gimnasio = false;
        nodoNuevo.pociones = POCIONES_POKEPARADA;
        g.asignarNodo(nodoNuevo);
        n++;
    }

    return g;
}

void generarSalidaOp(vector<Camino>& caminos, ofstream& salida){
    cout << "   Generando salida... " << endl;

    salida << "cantGimnasios,cantPokeparadas,tamMochila,distancia,tamCamino,tiempo" << endl;
    
    int cantCaminos = caminos.size();
    
    double cantCiclosTotal;
    int cantGimnasios, cantPokeparadas, tamMochila, distancia, tamCamino, cantNodos;
    queue<int> caminoCola, caminoColaVacia;
    
    for(int c = 0; c < cantCaminos; c++){
        cout << "       Procesando camino " << c + 1 << " de " << cantCaminos << "..." << endl;

        cantGimnasios = 0;
        cantPokeparadas = 0;
        cantNodos = caminos[c].grafo().nodos().size();

        vector<pos> gimnasios;
        vector<int> gimnasiosPoder;
        vector<pos> paradas;

        for(int n = 0; n < cantNodos; n++){
            if(caminos[c].grafo().nodos()[n].gimnasio){
                cantGimnasios++;

                pos posNueva;
                posNueva.first = caminos[c].grafo().nodos()[n].x;
                posNueva.second = caminos[c].grafo().nodos()[n].y;
                gimnasios.push_back(posNueva);

                gimnasiosPoder.push_back(caminos[c].grafo().nodos()[n].pociones);
            } else{
                cantPokeparadas++;

                pos posNueva;
                posNueva.first = caminos[c].grafo().nodos()[n].x;
                posNueva.second = caminos[c].grafo().nodos()[n].y;
                paradas.push_back(posNueva);
            }
        }

        cout << "           Camino de " << cantGimnasios << " gimnasios y " << cantPokeparadas << " pokeparadas" << endl;
 
        tamMochila = caminos[c].tamMochila();

        cout << "           Midiendo tiempos... ";

        cantCiclosTotal = 0;
        for(int r = 0; r < CANT_REPETICIONES_OP; r++){
            backtracking bt(gimnasios, gimnasiosPoder, paradas, tamMochila);
            caminoCola = caminoColaVacia;
            auto inicio = RELOJ();
                distancia = bt.correr_backtracking(caminoCola);
            auto fin = RELOJ();
            cantCiclosTotal += (double) chrono::duration_cast<std::chrono::nanoseconds>(fin-inicio).count();
        }

        cout << "Listo" << endl;

        tamCamino = caminoCola.size();

        salida << cantGimnasios << "," << cantPokeparadas << "," << tamMochila << "," << distancia << ","
        << tamCamino << "," << cantCiclosTotal / (double) CANT_REPETICIONES_OP << endl;

        cout << "       Listo" << endl;
    }

    cout << "   Listo" << endl;
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