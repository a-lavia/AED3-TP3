#include "Grafo.h"

Grafo::Grafo(){

}

Grafo::Grafo(int cantNodos){
    _distancias.resize(cantNodos, vector<float>(cantNodos));
}

Grafo& Grafo::operator=(const Grafo& otro){
    _nodos = otro._nodos;
    int cantNodos = _nodos.size();
    for(int i = 0; i < cantNodos; i++){
        if(otro._nodos[i].anterior != NULL){
            _nodos[i].anterior = &nodo(otro._nodos[i].anterior->id);
        }
        if(otro._nodos[i].siguiente != NULL){
            _nodos[i].siguiente = &nodo(otro._nodos[i].siguiente->id);
        }
    }

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
    assert(n.id <= nodos().size() + 1);

    if(n.id == nodos().size() + 1){
        nodos().push_back(n);
    } else{
        nodos()[n.id - 1] = n;
    }
}
