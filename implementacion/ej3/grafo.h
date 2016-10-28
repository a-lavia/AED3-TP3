#ifndef GRAFO_H_
#define GRAFO_H_

#include "ej.h"

class Grafo{
    public:
        Grafo(int cantNodos);
        Grafo& operator=(const Grafo& otro);

        vector<Nodo>& nodos();
        Nodo& nodo(int id);
        float distancia(const Nodo& n1, const Nodo& n2);

        void asignarDistancia(const Nodo& n1, const Nodo& n2, float distancia);
        void asignarNodo(const Nodo& n);

        int solucionInicial(int tamMochila, float* distanciaTotal);

        void busquedaLocal(float distanciaTotal, int cantGimnasios, int nodoInicial, Vecindad criterio);
        bool encuentroSolucionVecinaMejor1(float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial);
        bool intercambiarMejora(float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial, const Nodo& n1, const Nodo& n2);
        bool encuentroSolucionVecinaMejor2(float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial);

        void imprimirSolucion(int nodoInicial, float distanciaTotal, int cantGimnasios);

    private: 
        vector<Nodo> _nodos;
        vector<vector<float>> _distancias;
};

Grafo::Grafo(int cantNodos){
    _distancias.resize(cantNodos, vector<float>(cantNodos));
}

Grafo& Grafo::operator=(const Grafo& otro){
    _nodos = otro._nodos;
    _distancias = otro._distancias;
    return *this;
}

vector<Nodo>& Grafo::nodos(){
    return _nodos;
}

Nodo& Grafo::nodo(int id){
    return nodos()[id - 1];
}

float Grafo::distancia(const Nodo& n1, const Nodo& n2){
    return _distancias[n1.id - 1][n2.id - 1];
}

void Grafo::asignarDistancia(const Nodo& n1, const Nodo& n2, float distancia){
    _distancias[n1.id - 1][n2.id - 1] = distancia;
}

void Grafo::asignarNodo(const Nodo& n){
    assert(n.id == nodos().size() + 1);

    nodos().push_back(n);
}

int Grafo::solucionInicial(int tamMochila, float* distanciaTotal){
    // Llamar al algoritmo del segundo ejercicio.
    // Devuelve INV si no encontro una solucion.

    return INV;
}

void Grafo::busquedaLocal(float distanciaTotal, int cantGimnasios, int nodoInicial, Vecindad criterio){
    vector<Nodo> nodosSV;
    float distanciaTotalSV;

    if(criterio == vecindad1){
        while(encuentroSolucionVecinaMejor1(distanciaTotal, nodosSV, &distanciaTotalSV, &nodoInicial)){
            nodos() = nodosSV;
            distanciaTotal = distanciaTotalSV;
        }
    } else{
        while(encuentroSolucionVecinaMejor2(distanciaTotal, nodosSV, &distanciaTotalSV, &nodoInicial)){
            nodos() = nodosSV;
            distanciaTotal = distanciaTotalSV;
        } 
    }

    imprimirSolucion(nodoInicial, distanciaTotal, cantGimnasios);
}

bool Grafo::encuentroSolucionVecinaMejor1(float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial){
    // SWAP: intercambia el orden de los nodos del recorrido.
    
    bool encontre = false;

    vector<Nodo> nodosVisitados;
    Nodo nodoActual = nodo(*nodoInicial);
    nodosVisitados.push_back(nodoActual);
    while(nodoActual.siguiente != INV){
        nodoActual = nodo(nodoActual.siguiente);
        nodosVisitados.push_back(nodoActual);
    }

    for(int i = 0; i < nodosVisitados.size(); i++){
        for(int j = 0; j < nodosVisitados.size(); j++){
            if(i != j && intercambiarMejora(distanciaTotal, nodosSV, distanciaTotalSV, nodoInicial, nodosVisitados[i], nodosVisitados[j])){
                encontre = true;
            }
        }
    }

    return encontre;
}

bool Grafo::intercambiarMejora(float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial, const Nodo& n1, const Nodo& n2){
    bool mejora = false;

    float distanciaNueva = distanciaTotal - distancia(nodo(n1.anterior), n1) - distancia(n2, nodo(n2.siguiente)) + distancia(nodo(n1.anterior), n2) + distancia(n1, nodo(n2.siguiente));
    
    if(distanciaNueva < distanciaTotal){
        nodo(n1.anterior).siguiente = n2.id;

        nodo(n2.id).anterior = n1.anterior;
        nodo(n2.id).siguiente = n1.id;
        
        nodo(n1.id).anterior = n2.id;
        nodo(n1.id).siguiente = n2.siguiente;

        nodo(n2.siguiente).anterior = n1.id;
    
        mejora = true;
    }
    
    return mejora;
}

bool Grafo::encuentroSolucionVecinaMejor2(float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial){
    // Opcion: Cambiar los caminos hacia las pokeparadas, considerando tambien las que estan afuera del recorrido original, o sea, el orden de las aristas.

    return false;
}

void Grafo::imprimirSolucion(int nodoInicial, float distanciaTotal, int cantGimnasios){
    stack<int> camino;
    camino.push(nodoInicial);
    
    int nodosRecorridos = 1;

    Nodo nodoActual = nodo(nodoInicial);
    while(nodoActual.siguiente != INV){
        camino.push(nodoActual.siguiente);
        nodosRecorridos++;
        nodoActual = nodo(nodoActual.siguiente);
    }

    cout << distanciaTotal << " " << nodosRecorridos;
    while(!camino.empty()){
        cout << " " << camino.top() + 1;
        camino.pop();
    }
}

#endif