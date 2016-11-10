#ifndef CAMINO_H
#define CAMINO_H

#include "aux.h"
#include "Grafo.h"
#include "../ej2/funciones.h"
#include "../ej2/SegundaHeuristica.h"

class Camino{
    public:
        Camino(Grafo g, int tamMochila);

        Camino();
        void leerEntrada();

        Camino& operator=(const Camino& otro);

        Grafo& grafo();
        int tamMochila() const;

        void asignarSolucion(double distancia, queue<int>& caminoCola);
        void asignarSolucionGolosaJ();
        void asignarSolucionGolosaA();

        bool encontreSolucion();
        bool encontreCamino();

        Cambios busquedaLocal(Vecindad criterio);

        double distancia() const;
        double devolverSolucion(queue<int>& camino);
        void imprimirSolucion();

    private: 
        Grafo _grafo;
        int _tamMochila;
        Nodo* _nodoInicial;
        double _distancia;
        Cambios _cambios;

        void asignarNodoInicial(Nodo* nodoInicial);
        void asignarDistancia(double distancia);
        
        void buscoSolucionVecinaMejor(vector<Nodo*>& nodosConsiderados);
        
        bool encuentroSolucionVecinaMejor(vector<Nodo*>& nodosConsiderados);
        bool cambiarMejora(Nodo* n1, Nodo* n2);

        bool encuentroSolucionVecinaIgual(vector<Nodo*>& nodosConsiderados, map<int, set<int>>& nodosCambiados);
        bool cambiarMantieneIgual(Nodo* n1, Nodo* n2);

        bool cambiarSiPuedo(Nodo* n1, Nodo* n2);

        bool estaEnElCamino(const Nodo* n);

        double distanciaPermutar(const Nodo* n1, const Nodo* n2);
        double distanciaReemplazar(const Nodo* nodoViejo, const Nodo* nodoNuevo);
        void permutar(Nodo* n1, Nodo* n2);
        void reemplazar(Nodo* nodoViejo, Nodo* nodoNuevo);
};

#endif