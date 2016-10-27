#include "funciones.h"

float distancia(Nodo n1, Nodo n2){
    int x = n1.x - n2.x;
    int y = n1.y - n2.y;
    return sqrt((x*x) + (y*y));
}

int solucionInicial(vector<Nodo>& nodos, vector<vector<float>>& distancias, int tamMochila, float* distanciaTotal){
    // Llamar al algoritmo del segundo ejercicio.
    // Devuelve INV si no encontro una solucion.

    return INV;
}

void busquedaLocal(vector<Nodo> nodos, vector<vector<float>>& distancias, float distanciaTotal, int cantGimnasios, int nodoInicial, Vecindad criterio){
    vector<Nodo> nodosSV;
    float distanciaTotalSV;

    if(criterio == vecindad1){
        while(encuentroSolucionVecinaMejor1(nodos, distanciaTotal, nodosSV, &distanciaTotalSV, &nodoInicial)){
            nodos = nodosSV;
            distanciaTotal = distanciaTotalSV;
        }
    } else{
        while(encuentroSolucionVecinaMejor2(nodos, distanciaTotal, nodosSV, &distanciaTotalSV, &nodoInicial)){
            nodos = nodosSV;
            distanciaTotal = distanciaTotalSV;
        } 
    }

    imprimirSolucion(nodos, nodoInicial, distanciaTotal, cantGimnasios);
}

bool encuentroSolucionVecinaMejor1(vector<Nodo>& nodos, float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial){
    // Opcion: Intercambiar el orden del recorrido, o sea, el orden de los nodos.
    bool encontre = false;

    vector<Nodo> nodosVisitados;
    Nodo nodoActual = nodos[*nodoInicial];
    nodosVisitados.push_back(nodoActual);
    while(nodoActual.siguiente != INV){
        nodoActual = nodos[nodoActual.siguiente];
        nodosVisitados.push_back(nodoActual);
    }

    for(int i = 0; i < nodosVisitados.size(); i++){
        for(int j = 0; j < nodosVisitados.size(); j++){
            /*if(i != j && intercambiarMejora(nodos, distanciaTotal, nodosSV, distanciaTotalSV, nodoInicial, i, j)){
                encontre = true;
                
            }*/
        }
    }

    return encontre;
}

bool encuentroSolucionVecinaMejor2(vector<Nodo>& nodos, float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial){
    // Opcion: Cambiar los caminos hacia las pokeparadas, considerando tambien las que estan afuera del recorrido original, o sea, el orden de las aristas.

    return false;
}

void imprimirSolucion(vector<Nodo>& nodos, int nodoInicial, float distanciaTotal, int cantGimnasios){
    stack<int> camino;
    camino.push(nodoInicial);
    
    int nodosRecorridos = 1;

    Nodo nodoActual = nodos[nodoInicial];
    while(nodoActual.siguiente != INV){
        camino.push(nodoActual.siguiente);
        nodosRecorridos++;
        nodoActual = nodos[nodoActual.siguiente];
    }

    cout << distanciaTotal << " " << nodosRecorridos;
    while(!camino.empty()){
        cout << " " << camino.top() + 1;
        camino.pop();
    }
}