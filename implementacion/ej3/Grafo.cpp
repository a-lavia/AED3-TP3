#include "Grafo.h"

Grafo::Grafo(int cantNodos){
    _nodos.resize(cantNodos);
    _distancias.resize(cantNodos, vector<float>(cantNodos));
}

Grafo& Grafo::operator=(const Grafo& otro){
    _nodos = otro._nodos;
    _distancias = otro._distancias;

    int cantNodos = _nodos.size();
    for(int i = 0; i < cantNodos; i++){
        if(otro._nodos[i].anterior != NULL){
            _nodos[i].anterior = &nodo(otro._nodos[i].anterior->id);
        }
        if(otro._nodos[i].siguiente != NULL){
            _nodos[i].siguiente = &nodo(otro._nodos[i].siguiente->id);
        }
    }

    return *this;
}

vector<Nodo>& Grafo::nodos(){
    return _nodos;
}

Nodo& Grafo::nodo(int id){
    return _nodos[id - 1];
}

float Grafo::distancia(const Nodo& n1, const Nodo& n2){
    return _distancias[n1.id - 1][n2.id - 1];
}

void Grafo::asignarNodo(const Nodo& n){
    int cantNodos = _nodos.size();

    if(n.id > cantNodos){
        _nodos.resize(n.id);
        for(int i = 0; i < cantNodos; i++){
            _distancias[i].resize(n.id);
        }
        _distancias.resize(n.id, vector<float>(n.id));
    }

    _nodos[n.id - 1] = n;

    for(int i = 0; i < cantNodos; i++){
        if(_nodos[i].id != INV){
            float distancia = distanciaNodos(n, _nodos[i]);
            _distancias[n.id - 1][_nodos[i].id - 1] = distancia;
            _distancias[_nodos[i].id - 1][n.id - 1] = distancia;
        }
    }
}
