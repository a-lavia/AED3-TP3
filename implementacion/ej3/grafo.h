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

        void busquedaLocal(float distanciaTotal, int nodoInicial, Vecindad criterio);
        bool encuentroSolucionVecinaMejor1(vector<int>& nodosVisitados, float distanciaTotal, int* nodoInicial);
        bool intercambiarMejora(float distanciaTotal, int n1, int n2, int* nodoInicial);
        bool encuentroSolucionVecinaMejor2(float distanciaTotal, int* nodoInicial);

        void imprimirSolucion(float distanciaTotal, int nodoInicial);

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

void Grafo::busquedaLocal(float distanciaTotal, int nodoInicial, Vecindad criterio){
    if(criterio == vecindad1){
        vector<int> nodosVisitados;
        Nodo nodoActual = nodo(nodoInicial);
        nodosVisitados.push_back(nodoActual.id);
        while(nodoActual.siguiente != INV){
            nodoActual = nodo(nodoActual.siguiente);
            nodosVisitados.push_back(nodoActual.id);
        }
        while(encuentroSolucionVecinaMejor1(nodosVisitados, distanciaTotal, &nodoInicial)){
        }
        // Chequear cuando no hay mejores pero hay iguales, hay que tener cuidado con los ciclos.
    } else{
        while(encuentroSolucionVecinaMejor2(distanciaTotal, &nodoInicial)){
        } 
    }

    imprimirSolucion(distanciaTotal, nodoInicial);
}

bool Grafo::encuentroSolucionVecinaMejor1(vector<int>& nodosVisitados, float distanciaTotal, int* nodoInicial){
    // SWAP: intercambia el orden de los nodos del recorrido.

    bool busco = true;
    int cantVisitados = nodosVisitados.size();

    for(int i = 0; i < cantVisitados && busco; i++){
        for(int j = 0; j < cantVisitados && busco; j++){
            if(i != j && intercambiarMejora(distanciaTotal, nodosVisitados[i], nodosVisitados[j], nodoInicial)){
                busco = false;
            }
        }
    }

    return !busco;
}

bool Grafo::intercambiarMejora(float distanciaTotal, int n1, int n2, int* nodoInicial){
    bool mejora = false;

    Nodo n1Nodo = nodo(n1);
    Nodo n2Nodo = nodo(n2);

    float distanciaNueva = distanciaTotal;
    if(n1Nodo.anterior != INV){
        distanciaNueva = distanciaNueva - distancia(nodo(n1Nodo.anterior), n1Nodo) + distancia(nodo(n1Nodo.anterior), n2Nodo);
    }
    if(n2Nodo.siguiente != INV){
        distanciaNueva = distanciaNueva - distancia(n2Nodo, nodo(n2Nodo.siguiente)) + distancia(n1Nodo, nodo(n2Nodo.siguiente));
    }
    
    if(distanciaNueva < distanciaTotal){
        if(n1Nodo.anterior != INV){
            nodo(n1Nodo.anterior).siguiente = n2;
        } else{
            *nodoInicial = n2;
        }

        nodo(n2).anterior = n1Nodo.anterior;
        nodo(n2).siguiente = n1;
        
        nodo(n1).anterior = n2;
        nodo(n1).siguiente = n2Nodo.siguiente;

        if(n2Nodo.siguiente != INV){
            nodo(n2Nodo.siguiente).anterior = n1;
        }

        mejora = true;
    }
    
    return mejora;
}

bool Grafo::encuentroSolucionVecinaMejor2(float distanciaTotal, int* nodoInicial){
    // Opcion: Cambiar los caminos hacia las pokeparadas, considerando tambien las que estan afuera del recorrido original, o sea, el orden de las aristas.

    return false;
}

void Grafo::imprimirSolucion(float distanciaTotal, int nodoInicial){
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