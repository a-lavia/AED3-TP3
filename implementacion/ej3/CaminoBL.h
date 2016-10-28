#ifndef CAMINO_H_
#define CAMINO_H_

#include "ej.h"
#include "Grafo.h"

class CaminoBL{
    public:
        CaminoBL(Grafo g, int tamMochila);
        CaminoBL& operator=(const CaminoBL& otro);

        Grafo& grafo();
        Nodo* nodoInicial();
        float distancia();
        int tamMochila();

        void asignarNodoInicial(Nodo* nodoInicial);
        void asignarDistancia(int distancia);

        void solucionInicial();

        void busquedaLocal(Vecindad criterio);
        
        bool encuentroSolucionVecinaMejor1(vector<Nodo*>& nodosVisitados);
        bool intercambiarMejora(Nodo* n1, Nodo* n2);
        bool encuentroSolucionVecinaIgual1(vector<Nodo*>& nodosVisitados);
        bool intercambiarMantieneIgual(Nodo* n1, Nodo* n2);

        bool encuentroSolucionVecinaMejor2();

        void imprimirSolucion();

    private: 
        Grafo _grafo;
        int _tamMochila;
        Nodo* _nodoInicial;
        float _distancia;
};

CaminoBL::CaminoBL(Grafo g, int tamMochila){
    _grafo = g;
    _tamMochila = tamMochila;
    _nodoInicial = NULL;
    _distancia = 0;
}

CaminoBL& CaminoBL::operator=(const CaminoBL& otro){
    _grafo = otro._grafo;
    _tamMochila = otro._tamMochila;
    _nodoInicial = otro._nodoInicial;
    _distancia = otro._distancia;
    return *this;
}

Grafo& CaminoBL::grafo(){
    return _grafo;
}

Nodo* CaminoBL::nodoInicial(){
    return _nodoInicial;
}

float CaminoBL::distancia(){
    return _distancia;
}

int CaminoBL::tamMochila(){
    return _tamMochila;
}

void CaminoBL::asignarNodoInicial(Nodo* nodoInicial){
    _nodoInicial = nodoInicial;
}

void CaminoBL::asignarDistancia(int distancia){
    _distancia = distancia;
}

void CaminoBL::solucionInicial(){
    assert(nodoInicial() == NULL);

    // Llamar al algoritmo del segundo ejercicio.
    // Cambia el nodoInicial

}

void CaminoBL::busquedaLocal(Vecindad criterio){
    if(criterio == vecindad1){
        vector<Nodo*> nodosVisitados;
        Nodo* nodoActual = nodoInicial();
        nodosVisitados.push_back(nodoActual);
        while(nodoActual->siguiente != NULL){
            nodoActual = nodoActual->siguiente;
            nodosVisitados.push_back(nodoActual);
        }

        bool busco = true;
        bool vengoDeUnaSolucionMejor = true;
        while(busco){
            while(encuentroSolucionVecinaMejor1(nodosVisitados)){
                if(!vengoDeUnaSolucionMejor){
                    vengoDeUnaSolucionMejor = true;
                }
            }
            if(encuentroSolucionVecinaIgual1(nodosVisitados) && vengoDeUnaSolucionMejor){
                vengoDeUnaSolucionMejor = false;
            } else{
                busco = false;
            }
        }
    } else{
        while(encuentroSolucionVecinaMejor2()){
        } 
    }

    imprimirSolucion();
}

bool CaminoBL::encuentroSolucionVecinaMejor1(vector<Nodo*>& nodosVisitados){
    // SWAP: intercambia el orden de los nodos del recorrido.

    bool busco = true;
    int cantVisitados = nodosVisitados.size();

    for(int i = 0; i < cantVisitados && busco; i++){
        for(int j = 0; j < cantVisitados && busco; j++){
            if(i != j && intercambiarMejora(nodosVisitados[i], nodosVisitados[j])){
                busco = false;
            }
        }
    }

    return !busco;
}

bool CaminoBL::intercambiarMejora(Nodo* n1, Nodo* n2){
    bool mejora = false;

    float distanciaNueva = distancia();
    if(n1->anterior != NULL){
        distanciaNueva = distanciaNueva - grafo().distancia(*(n1->anterior), *n1) + grafo().distancia(*(n1->anterior), *n2);
    }
    if(n2->siguiente != NULL){
        distanciaNueva = distanciaNueva - grafo().distancia(*n2, *(n2->siguiente)) + grafo().distancia(*n1, *(n2->siguiente));
    }
    
    if(distanciaNueva < distancia()){
        n2->anterior = n1->anterior;
        n2->siguiente = n1;
        
        n1->anterior = n2;
        n1->siguiente = n2->siguiente;

        if(n2->siguiente != NULL){
            n2->siguiente->anterior = n1;
        }

        if(n1->anterior != NULL){
            n1->anterior->siguiente = n2;
        } else{
            asignarNodoInicial(n2);
        }

        asignarDistancia(distanciaNueva);

        mejora = true;
    }
    
    return mejora;
}

bool CaminoBL::encuentroSolucionVecinaIgual1(vector<Nodo*>& nodosVisitados){
    bool busco = true;
    int cantVisitados = nodosVisitados.size();

    for(int i = 0; i < cantVisitados && busco; i++){
        for(int j = 0; j < cantVisitados && busco; j++){
            if(i != j && intercambiarMantieneIgual(nodosVisitados[i], nodosVisitados[j])){
                busco = false;
            }
        }
    }

    return !busco;
}

bool CaminoBL::intercambiarMantieneIgual(Nodo* n1, Nodo* n2){


    return false;
}

bool CaminoBL::encuentroSolucionVecinaMejor2(){
    // Opcion: Cambiar los caminos hacia las pokeparadas, considerando tambien las que estan afuera del recorrido original, o sea, el orden de las aristas.

    return false;
}

void CaminoBL::imprimirSolucion(){
    stack<int> camino;
    camino.push(nodoInicial()->id);
    
    int nodosRecorridos = 1;

    Nodo* nodoActual = nodoInicial();
    while(nodoActual->siguiente != NULL){
        camino.push(nodoActual->siguiente->id);
        nodosRecorridos++;
        nodoActual = nodoActual->siguiente;
    }

    cout << distancia() << " " << nodosRecorridos;
    while(!camino.empty()){
        cout << " " << camino.top() + 1;
        camino.pop();
    }
}

#endif