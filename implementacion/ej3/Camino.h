#ifndef CAMINO_H
#define CAMINO_H

#include "aux.h"
#include "Grafo.h"
#include "../ej2/funciones.h"
#include "../ej1bis/heuristica.h"

class Camino{
    public:
        Camino(Grafo g, int tamMochila);
        
        Camino();
        void leerEntrada();

        Camino& operator=(const Camino& otro);

        Grafo& grafo();
        int tamMochila() const;
        Nodo* nodoInicial();
        float distancia() const;

        void solucionGolosaJ();
        void solucionGolosaA();

        bool encontreSolucion();

        void busquedaLocal(Vecindad criterio);

        void imprimirSolucion();

    private: 
        Grafo _grafo;
        int _tamMochila;
        Nodo* _nodoInicial;
        float _distancia;

        void asignarNodoInicial(Nodo* nodoInicial);
        void asignarDistancia(float distancia);
        void asignarCamino(queue<int>& caminoCola);
        
        void buscoSolucionVecinaMejor(vector<Nodo*>& nodosConsiderados);
        
        bool encuentroSolucionVecinaMejor(vector<Nodo*>& nodosConsiderados);
        bool cambiarMejora(Nodo* n1, Nodo* n2);

        bool encuentroSolucionVecinaIgual(vector<Nodo*>& nodosConsiderados, map<int, int>& nodosCambiados);
        bool cambiarMantieneIgual(Nodo* n1, Nodo* n2);

        bool cambiarSiPuedo(Nodo* n1, Nodo* n2);

        bool estaEnElCamino(const Nodo* n);

        float distanciaPermutar(const Nodo* n1, const Nodo* n2);
        float distanciaReemplazar(const Nodo* nodoViejo, const Nodo* nodoNuevo);
        void permutar(Nodo* n1, Nodo* n2);
        void reemplazar(Nodo* nodoViejo, Nodo* nodoNuevo);
};

#endif