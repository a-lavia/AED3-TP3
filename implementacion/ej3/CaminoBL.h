#ifndef CAMINOBL_H
#define CAMINOBL_H

#include "ej.h"
#include "Grafo.h"
#include "../ej2/funciones.h"

class CaminoBL{
    public:
        CaminoBL(Grafo g, int tamMochila);
        
        CaminoBL();
        void leerEntrada();

        CaminoBL& operator=(const CaminoBL& otro);

        Grafo& grafo();
        Nodo* nodoInicial();
        float distancia() const;
        int tamMochila() const;

        void asignarNodoInicial(Nodo* nodoInicial);
        void asignarDistancia(int distancia);

        void solucionInicial();

        void busquedaLocal(Vecindad criterio);

        void buscoSolucionVecinaMejor(vector<Nodo*>& nodosIntercambiables);
        
        bool encuentroSolucionVecinaMejor(vector<Nodo*>& nodosIntercambiables);
        bool intercambiarMejora(Nodo* n1, Nodo* n2);

        bool encuentroSolucionVecinaIgual(vector<Nodo*>& nodosIntercambiables);
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

CaminoBL::CaminoBL(){
    _nodoInicial = NULL;
    _distancia = 0;
}

void CaminoBL::leerEntrada(){
    int cantGimnasios, cantPokeparadas, tamMochila;    
    cin >> cantGimnasios;
    cin >> cantPokeparadas;
    cin >> tamMochila;

    int cantNodos = cantGimnasios + cantPokeparadas;

    Grafo g(cantNodos);

    int nodoActual;
    for(nodoActual = 0; nodoActual < cantGimnasios; nodoActual++){
        Nodo nodoNuevo;
        nodoNuevo.id = nodoActual + 1;
        cin >> nodoNuevo.x;
        cin >> nodoNuevo.y;
        cin >> nodoNuevo.pociones;  
        nodoNuevo.gimnasio = true;
        g.asignarNodo(nodoNuevo);
    }
    while(nodoActual < cantNodos){
        Nodo nodoNuevo;
        nodoNuevo.id = nodoActual + 1;
        cin >> nodoNuevo.x;
        cin >> nodoNuevo.y;
        nodoNuevo.pociones = POCIONES_POKEPARADA;
        nodoNuevo.gimnasio = false;
        g.asignarNodo(nodoNuevo);
        nodoActual++;
    }

    for(int i = 0; i < cantNodos; ++i){
        for(int j = 0; j < cantNodos; ++j){
            Nodo n1 = g.nodos()[i];
            Nodo n2 = g.nodos()[j];
            g.asignarDistancia(n1, n2, distanciaNodos(n1, n2));
        }
    }

    this->_grafo = g;
    this->_tamMochila = tamMochila;
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

    vector<gym> gimnasios;
    vector<parada> paradas;

    for(int i = 0; i < grafo().nodos().size(); i++){
        if(grafo().nodos()[i].gimnasio){
            gym gymNuevo;
            gymNuevo.x = grafo().nodos()[i].x;
            gymNuevo.y = grafo().nodos()[i].y;
            gymNuevo.p = grafo().nodos()[i].pociones;
            gymNuevo.visitado = false;
            gimnasios.push_back(gymNuevo);
        } else{
            parada paradaNueva;
            paradaNueva.x = grafo().nodos()[i].x;
            paradaNueva.y = grafo().nodos()[i].y;
            paradaNueva.visitado = false;
            paradas.push_back(paradaNueva);
        }
    }

    solucion* solucionInicial = solHeuristicaGolosa(tamMochila(), gimnasios, paradas);

    asignarDistancia(solucionInicial->d);

    int tamCamino = solucionInicial->camino.size();
    vector<int> camino(tamCamino);
    for(int i = 0; i < tamCamino; i++){
        camino[i] = solucionInicial->camino.front();
        solucionInicial->camino.pop();
    }

    asignarNodoInicial(&grafo().nodos()[camino[0]]);

    grafo().nodos()[camino[0]].siguiente = &grafo().nodos()[camino[1]];
    for(int i = 1; i < tamCamino - 1; i++){
        grafo().nodos()[camino[i]].anterior = &grafo().nodos()[camino[i-1]];
        grafo().nodos()[camino[i]].siguiente = &grafo().nodos()[camino[i+1]];
    }
    grafo().nodos()[camino[tamCamino - 1]].anterior = &grafo().nodos()[camino[tamCamino - 2]];
}

void CaminoBL::busquedaLocal(Vecindad criterio){
    assert(nodoInicial() != NULL);

    if(criterio == intercambiaNodosVisitados){
        vector<Nodo*>* nodosVisitados = new vector<Nodo*>;
        
        Nodo* nodoActual = nodoInicial();
        nodosVisitados->push_back(nodoActual);
        while(nodoActual->siguiente != NULL){
            nodoActual = nodoActual->siguiente;
            nodosVisitados->push_back(nodoActual);
        }

        buscoSolucionVecinaMejor(*nodosVisitados);

        delete nodosVisitados;
    } else{
        vector<Nodo*>* pokeparadas = new vector<Nodo*>;

        for(int i = 0; i < grafo().nodos().size(); i++){
            if(!grafo().nodos()[i].gimnasio){
                pokeparadas->push_back(&grafo().nodos()[i]);
            }
        }

        buscoSolucionVecinaMejor(*pokeparadas);
        
        delete pokeparadas;
    }
}

void CaminoBL::buscoSolucionVecinaMejor(vector<Nodo*>& nodosIntercambiables){
    bool busco = true;
    bool vengoDeUnaSolucionMejor = true;
    while(busco){
        while(encuentroSolucionVecinaMejor(nodosIntercambiables)){
            if(!vengoDeUnaSolucionMejor){
                vengoDeUnaSolucionMejor = true;
            }
        }
        if(encuentroSolucionVecinaIgual(nodosIntercambiables) && vengoDeUnaSolucionMejor){
            vengoDeUnaSolucionMejor = false;
        } else{
            busco = false;
        }
    }
}

bool CaminoBL::encuentroSolucionVecinaMejor(vector<Nodo*>& nodosIntercambiables){
    bool busco = true;
    int cantNodos = nodosIntercambiables.size();

    for(int i = 0; i < cantNodos && busco; i++){
        for(int j = 0; j < cantNodos && busco; j++){
            if(i != j && intercambiarMejora(nodosIntercambiables[i], nodosIntercambiables[j])){
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

bool CaminoBL::encuentroSolucionVecinaIgual(vector<Nodo*>& nodosIntercambiables){
    bool busco = true;
    int cantNodos = nodosIntercambiables.size();

    for(int i = 0; i < cantNodos && busco; i++){
        for(int j = 0; j < cantNodos && busco; j++){
            if(i != j && intercambiarMantieneIgual(nodosIntercambiables[i], nodosIntercambiables[j])){
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
    
    int tamCamino = 1;

    Nodo* nodoActual = nodoInicial();
    while(nodoActual->siguiente != NULL){
        camino.push(nodoActual->siguiente->id);
        tamCamino++;
        nodoActual = nodoActual->siguiente;
    }

    cout << distancia() << " " << tamCamino;
    while(!camino.empty()){
        cout << " " << camino.top() + 1;
        camino.pop();
    }
}

#endif