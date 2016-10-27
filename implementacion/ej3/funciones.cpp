#include "funciones.h"

float distancia(Nodo n1, Nodo n2){
    int x = n1.x - n2.x;
    int y = n1.y - n2.y;
    return sqrt((x*x) + (y*y));
}

int solucionInicial(vector<Nodo>& nodos, vector<vector<float>>& distancias, float* distanciaTotal){
    // Llamar al algoritmo del segundo ejercicio.
}

void busquedaLocal1(vector<Nodo> nodos, vector<vector<float>>& distancias, float distanciaTotal, int cantGimnasios, int nodoInicial){
    vector<Nodo> nodosSV;
    float distanciaTotalSV;

    while(encuentroSolucionVecinaMejor1(nodos, distanciaTotal, nodosSV, &distanciaTotalSV, &nodoInicial)){
        nodos = nodosSV;
        distanciaTotal = distanciaTotalSV;
    }

    imprimirSalida(nodos, nodoInicial, distanciaTotal, cantGimnasios);
}

bool encuentroSolucionVecinaMejor1(vector<Nodo>& nodos, float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial){
    // Opcion: Intercambiar el orden del recorrido, o sea, el orden de los nodos.
}

void busquedaLocal2(vector<Nodo> nodos, vector<vector<float>>& distancias, float distanciaTotal, int cantGimnasios, int nodoInicial){
    vector<Nodo> nodosSV;
    float distanciaTotalSV;

    while(encuentroSolucionVecinaMejor2(nodos, distanciaTotal, nodosSV, &distanciaTotalSV, &nodoInicial)){
        nodos = nodosSV;
        distanciaTotal = distanciaTotalSV;
    }

    imprimirSalida(nodos, nodoInicial, distanciaTotal, cantGimnasios);
}

bool encuentroSolucionVecinaMejor2(vector<Nodo>& nodos, float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial){
    // Opcion: Cambiar los caminos hacia las pokeparadas, considerando tambien las que estan afuera del recorrido original, o sea, el orden de las aristas.
}

void imprimirSalida(vector<Nodo>& nodos, int nodoInicial, float distanciaTotal, int cantGimnasios){
    stack<int> camino;
    camino.push(nodoInicial);
    
    int nodosRecorridos = 1;
    int gimnasiosRecorridos = 0;
    if(nodos[nodoInicial].gimnasio){
        gimnasiosRecorridos++;
    }

    Nodo nodoActual = nodos[nodoInicial];
    while(nodoActual.siguiente != INV){
        camino.push(nodoActual.siguiente);
        nodosRecorridos++;
        if(nodos[nodoActual.siguiente].gimnasio){
            gimnasiosRecorridos++;
        }
        nodoActual = nodos[nodoActual.siguiente];
    }

    if(gimnasiosRecorridos == cantGimnasios){
        cout << distanciaTotal << " " << nodosRecorridos;
        while(!camino.empty()){
            cout << " " << camino.top();
            camino.pop();
        }
    } else{
        cout << -1 << endl;
    }
}