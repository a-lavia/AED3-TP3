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
        float distancia() const;
        int tamMochila() const;

        void asignarNodoInicial(Nodo* nodoInicial);
        void asignarDistancia(int distancia);

        void solucionInicial();

        void busquedaLocal(Vecindad criterio);
        
        bool encuentroSolucionVecinaMejor(vector<Nodo*>& nodosVisitados);
        bool intercambiarMejora(Nodo* n1, Nodo* n2);

        bool encuentroSolucionVecinaIgual(vector<Nodo*>& nodosVisitados);
        bool intercambiarMantieneIgual(Nodo* n1, Nodo* n2);

        int distanciaIntercambiar(const Nodo* n1, const Nodo* n2);
        bool puedoIntercambiar(Nodo* n1, Nodo* n2);
        void intercambiar(Nodo* n1, Nodo* n2, int distanciaNueva);

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

float CaminoBL::distancia() const{
    return _distancia;
}

int CaminoBL::tamMochila() const{
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
    assert(nodoInicial() != NULL);

    if(criterio == vecindad1){
        // Intercambia el orden de los nodos del recorrido.

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
            while(encuentroSolucionVecinaMejor(nodosVisitados)){
                if(!vengoDeUnaSolucionMejor){
                    vengoDeUnaSolucionMejor = true;
                }
            }
            if(encuentroSolucionVecinaIgual(nodosVisitados) && vengoDeUnaSolucionMejor){
                vengoDeUnaSolucionMejor = false;
            } else{
                busco = false;
            }
        }
    } else{
        // Intercambia pokeparadas incluyendo las que estan afuera del recorrido original.

        vector<Nodo*> pokeparadas;
        for(int i = 0; i < grafo().nodos().size(); i++){
            if(!grafo().nodos()[i].gimnasio){
                pokeparadas.push_back(&grafo().nodos()[i]);
            }
        }

        bool busco = true;
        bool vengoDeUnaSolucionMejor = true;
        while(busco){
            while(encuentroSolucionVecinaMejor(pokeparadas)){
                if(!vengoDeUnaSolucionMejor){
                    vengoDeUnaSolucionMejor = true;
                }
            }
            if(encuentroSolucionVecinaIgual(pokeparadas) && vengoDeUnaSolucionMejor){
                vengoDeUnaSolucionMejor = false;
            } else{
                busco = false;
            }
        }
    }

    imprimirSolucion();
}

bool CaminoBL::encuentroSolucionVecinaMejor(vector<Nodo*>& nodosVisitados){
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
    float distanciaNueva = distanciaIntercambiar(n1, n2);
    
    if(distanciaNueva < distancia() && puedoIntercambiar(n1, n2)){  
        intercambiar(n1, n2, distanciaNueva);
        mejora = true;
    }
    
    return mejora;
}

bool CaminoBL::encuentroSolucionVecinaIgual(vector<Nodo*>& nodosVisitados){
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
    bool mantiene = false;
    float distanciaNueva = distanciaIntercambiar(n1, n2);
    
    if(distanciaNueva == distancia() && puedoIntercambiar(n1, n2)){  
        intercambiar(n1, n2, distanciaNueva);
        mantiene = true;
    }
    
    return mantiene;
}

int CaminoBL::distanciaIntercambiar(const Nodo* n1, const Nodo* n2){
    float distanciaNueva = distancia();

    if(n1->anterior != NULL){
        distanciaNueva -= grafo().distancia(*(n1->anterior), *n1);
        distanciaNueva += grafo().distancia(*(n1->anterior), *n2);
    }

    if(n1->siguiente != NULL){
        distanciaNueva -= grafo().distancia(*(n1->siguiente), *n1);
        distanciaNueva += grafo().distancia(*(n1->siguiente), *n2);
    }

    if(n2->anterior != NULL){
        distanciaNueva -= grafo().distancia(*(n2->anterior), *n2);
        distanciaNueva += grafo().distancia(*(n2->anterior), *n1);
    }

    if(n2->siguiente != NULL){
        distanciaNueva -= grafo().distancia(*(n2->siguiente), *n2);
        distanciaNueva += grafo().distancia(*(n2->siguiente), *n1);
    }

    return distanciaNueva;
}

bool CaminoBL::puedoIntercambiar(Nodo* n1, Nodo* n2){
    int pocionesDisponibles = 0;

    Nodo* nodoActual = nodoInicial();
    while(pocionesDisponibles >= 0 && nodoActual != NULL){
        if(nodoActual->gimnasio){
            pocionesDisponibles -= nodoActual->pociones;
        } else{
            pocionesDisponibles += POCIONES_POKEPARADA;
        }

        if(nodoActual == n1->anterior && nodoActual != NULL){
            nodoActual = n2;
        }

        if(nodoActual == n2->anterior && nodoActual != NULL){
            nodoActual = n1;
        }
    }

    return pocionesDisponibles >= 0;
}

void CaminoBL::intercambiar(Nodo* n1, Nodo* n2, int distanciaNueva){
    n2->anterior = n1->anterior;
    n2->siguiente = n1->siguiente;
    
    n1->anterior = n2->anterior;
    n1->siguiente = n2->siguiente;

    if(n1->siguiente != NULL){
        n1->siguiente->anterior = n2;
    }

    if(n2->siguiente != NULL){
        n2->siguiente->anterior = n1;
    }

    if(n1->anterior != NULL){
        n1->anterior->siguiente = n2;
    } else{
        asignarNodoInicial(n2);
    }

    if(n2->anterior != NULL){
        n2->anterior->siguiente = n1;
    } else{
        asignarNodoInicial(n1);
    }

    asignarDistancia(distanciaNueva);

    bool n1Visitado = n1->visitado;
    n1->visitado = n2->visitado;
    n2->visitado = n1Visitado;
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