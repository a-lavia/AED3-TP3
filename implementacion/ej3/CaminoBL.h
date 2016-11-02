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
        int tamMochila() const;
        Nodo* nodoInicial();
        float distancia() const;

        void solucionInicial();

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
        
        void buscoSolucionVecinaMejor(vector<Nodo*>& nodosIntercambiables);
        
        bool encuentroSolucionVecinaMejor(vector<Nodo*>& nodosIntercambiables);
        bool intercambiarMejora(Nodo* n1, Nodo* n2);

        bool encuentroSolucionVecinaIgual(vector<Nodo*>& nodosIntercambiables, map<Nodo*, Nodo*>& nodosIntercambiados);
        bool intercambiarMantieneIgual(Nodo* n1, Nodo* n2);

        float distanciaIntercambiar(const Nodo* n1, const Nodo* n2);
        bool intercambiarSiPuedo(Nodo* n1, Nodo* n2);
        void intercambiar(Nodo* n1, Nodo* n2);
};

CaminoBL::CaminoBL(Grafo g, int tamMochila){
    _grafo = g;
    _tamMochila = tamMochila;
    _nodoInicial = NULL;
    _distancia = 0;
}

CaminoBL::CaminoBL(){
    _tamMochila = INV;
    _nodoInicial = NULL;
    _distancia = 0;
}

void CaminoBL::leerEntrada(){
    assert(_tamMochila == INV);

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
    _nodoInicial = &_grafo.nodo(otro._nodoInicial->id);
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

void CaminoBL::asignarDistancia(float distancia){
    _distancia = distancia;
}

void CaminoBL::solucionInicial(){
    assert(!encontreSolucion());

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

    if(solucionInicial != NULL){
        asignarDistancia(solucionInicial->d);

        int tamCamino = solucionInicial->camino.size();
        vector<int> camino(tamCamino);
        for(int i = 0; i < tamCamino; i++){
            camino[i] = solucionInicial->camino.front();
            solucionInicial->camino.pop();
        }

        asignarNodoInicial(&grafo().nodos()[camino[0]]);

        if(tamCamino > 1){
            grafo().nodos()[camino[0]].siguiente = &grafo().nodos()[camino[1]];
            for(int i = 1; i < tamCamino - 1; i++){
                grafo().nodos()[camino[i]].anterior = &grafo().nodos()[camino[i-1]];
                grafo().nodos()[camino[i]].siguiente = &grafo().nodos()[camino[i+1]];
            }
            grafo().nodos()[camino[tamCamino - 1]].anterior = &grafo().nodos()[camino[tamCamino - 2]];
        }
    }
}

bool CaminoBL::encontreSolucion(){
    return nodoInicial() != NULL;
}

void CaminoBL::busquedaLocal(Vecindad criterio){
    assert(encontreSolucion());

    if(criterio == intercambiaNodosVisitados){
        vector<Nodo*> nodosVisitados;
        
        Nodo* nodoActual = nodoInicial();
        nodosVisitados.push_back(nodoActual);
        while(nodoActual->siguiente != NULL){
            nodoActual = nodoActual->siguiente;
            nodosVisitados.push_back(nodoActual);
        }

        buscoSolucionVecinaMejor(nodosVisitados);
    } else{
        vector<Nodo*> pokeparadas;

        for(int i = 0; i < grafo().nodos().size(); i++){
            if(!grafo().nodos()[i].gimnasio){
                pokeparadas.push_back(&grafo().nodos()[i]);
            }
        }

        buscoSolucionVecinaMejor(pokeparadas);
    }
}

void CaminoBL::buscoSolucionVecinaMejor(vector<Nodo*>& nodosIntercambiables){
    bool busco = true;
    map<Nodo*, Nodo*> nodosIntercambiados;

    cout << "Distancia actual = " << distancia() << endl;

    while(busco){

        cout << "   Busco una solucion mejor:" << endl;

        while(encuentroSolucionVecinaMejor(nodosIntercambiables)){
            if(nodosIntercambiados.size() > 0){
                nodosIntercambiados.clear();
            }
        }

        cout << "   Bueno una solucion igual:" << endl;

        if(!encuentroSolucionVecinaIgual(nodosIntercambiables, nodosIntercambiados)){
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
    
    cout << "       Distancia si intercambio " << n1->id << " con " << n2->id << " = " << distanciaNueva << endl;
    
    if(distanciaNueva < distancia() && intercambiarSiPuedo(n1, n2)){ 
        asignarDistancia(distanciaNueva);
        mejora = true;

        cout << "¡MEJORE!" << endl;
        cout << "Intercambie " << n1->id << " con " << n2->id << endl;
        imprimirSolucion();
    }
    
    return mejora;
}

bool CaminoBL::encuentroSolucionVecinaIgual(vector<Nodo*>& nodosIntercambiables, map<Nodo*, Nodo*>& nodosIntercambiados){
    bool busco = true;
    int cantNodos = nodosIntercambiables.size();

    for(int i = 0; i < cantNodos && busco; i++){
        for(int j = 0; j < cantNodos && busco; j++){
            if(i != j && intercambiarMantieneIgual(nodosIntercambiables[i], nodosIntercambiables[j])){
                if(!(nodosIntercambiados.count(nodosIntercambiables[i]) > 0 && nodosIntercambiados[nodosIntercambiables[i]] == nodosIntercambiables[j])){
                    busco = false;
                    nodosIntercambiados[nodosIntercambiables[i]] = nodosIntercambiables[j];
                }
            }
        }
    }

    return !busco;
}

bool CaminoBL::intercambiarMantieneIgual(Nodo* n1, Nodo* n2){
    bool mantiene = false;
    float distanciaNueva = distanciaIntercambiar(n1, n2);

    cout << "       Distancia si intercambio " << n1->id << " con " << n2->id << " = " << distanciaNueva << endl;
    
    if(distanciaNueva == distancia() && intercambiarSiPuedo(n1, n2)){  
        asignarDistancia(distanciaNueva);
        mantiene = true;

        cout << "CAMBIE POR UNA DISTANCIA IGUAL" << endl;
        cout << "Intercambie " << n1->id << " con " << n2->id << endl;
        imprimirSolucion();
    }
    
    return mantiene;
}

float CaminoBL::distanciaIntercambiar(const Nodo* n1, const Nodo* n2){
    float distanciaNueva = distancia();

    if(n2->siguiente != n1){
        if(n1->anterior != NULL){
            distanciaNueva -= grafo().distancia(*(n1->anterior), *n1);
            distanciaNueva += grafo().distancia(*(n1->anterior), *n2);
        }

        if(n2->siguiente != NULL){
            distanciaNueva -= grafo().distancia(*(n2->siguiente), *n2);
            distanciaNueva += grafo().distancia(*(n2->siguiente), *n1);
        }
    }

    if(n1->siguiente != n2){
        if(n1->siguiente != NULL){
            distanciaNueva -= grafo().distancia(*(n1->siguiente), *n1);
            distanciaNueva += grafo().distancia(*(n1->siguiente), *n2);
        }

        if(n2->anterior != NULL){
            distanciaNueva -= grafo().distancia(*(n2->anterior), *n2);
            distanciaNueva += grafo().distancia(*(n2->anterior), *n1);
        }
    }

    return distanciaNueva;
}

bool CaminoBL::intercambiarSiPuedo(Nodo* n1, Nodo* n2){
    int pocionesDisponibles = 0;

    intercambiar(n1, n2);

    Nodo* nodoActual = nodoInicial();
    while(pocionesDisponibles >= 0 && nodoActual != NULL){
        if(nodoActual->gimnasio){
            pocionesDisponibles -= nodoActual->pociones;
        } else{
            pocionesDisponibles += POCIONES_POKEPARADA;
        }
        nodoActual = nodoActual->siguiente;
    }

    cout << "       Pociones disponibles si intercambio = " << pocionesDisponibles << endl;

    if(pocionesDisponibles >= 0){
        return true;
    } else{
        intercambiar(n1, n2);
        return false;
    }
}

void CaminoBL::intercambiar(Nodo* n1, Nodo* n2){
    if(n1->siguiente == n2){
        if(n2->siguiente != NULL){
            n2->siguiente->anterior = n1;
        }

        if(n1->anterior != NULL){
            n1->anterior->siguiente = n2;
        } else{
            asignarNodoInicial(n2);
        }

        Nodo* n1AnteriorCopia = n1->anterior;
        n1->anterior = n2;
        n1->siguiente = n2->siguiente;
        n2->anterior = n1AnteriorCopia;
        n2->siguiente = n1;
    } else if(n2->siguiente == n1){
        if(n1->siguiente != NULL){
            n1->siguiente->anterior = n2;
        }

        if(n2->anterior != NULL){
            n2->anterior->siguiente = n1;
        } else{
            asignarNodoInicial(n1);
        }

        Nodo* n1SiguienteCopia = n1->siguiente;
        n1->anterior = n2->anterior;
        n1->siguiente = n2;
        n2->anterior = n1;
        n2->siguiente = n1SiguienteCopia;
    } else{
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

        Nodo* n1AnteriorCopia = n1->anterior;
        Nodo* n1SiguienteCopia = n1->siguiente;
        n1->anterior = n2->anterior;
        n1->siguiente = n2->siguiente;
        n2->anterior = n1AnteriorCopia;
        n2->siguiente = n1SiguienteCopia;
    }

    bool n1Visitado = n1->visitado;
    n1->visitado = n2->visitado;
    n2->visitado = n1Visitado;
}

void CaminoBL::imprimirSolucion(){
    assert(encontreSolucion());

    queue<int> camino;
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
        cout << " " << camino.front();
        camino.pop();
    }
    cout << endl;
}

#endif