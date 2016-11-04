#ifndef GRAFO_H
#define GRAFO_H

#include "aux.h"

class Grafo{
    public:
        Grafo() = default;
        Grafo(int cantNodos);
        Grafo& operator=(const Grafo& otro);

        vector<Nodo>& nodos();
        Nodo& nodo(int id);
        float distancia(const Nodo& n1, const Nodo& n2);

        void asignarNodo(const Nodo& n);

    private: 
        vector<Nodo> _nodos;
        vector<vector<float>> _distancias;
};

#endif