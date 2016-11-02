#ifndef CAMINO_H
#define CAMINO_H

#include "ej.h"
#include "Grafo.h"
#include "../ej2/funciones.h"

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

        void solucionGolosa();

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

Camino::Camino(Grafo g, int tamMochila){
    _grafo = g;
    _tamMochila = tamMochila;
    _nodoInicial = NULL;
    _distancia = 0;
}

Camino::Camino(){
    _tamMochila = INV;
    _nodoInicial = NULL;
    _distancia = 0;
}

void Camino::leerEntrada(){
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

    _grafo = g;
    _tamMochila = tamMochila;
}

Camino& Camino::operator=(const Camino& otro){
    _grafo = otro._grafo;
    _tamMochila = otro._tamMochila;
    _nodoInicial = &_grafo.nodo(otro._nodoInicial->id);
    _distancia = otro._distancia;
    return *this;
}

Grafo& Camino::grafo(){
    return _grafo;
}

Nodo* Camino::nodoInicial(){
    return _nodoInicial;
}

float Camino::distancia() const{
    return _distancia;
}

int Camino::tamMochila() const{
    return _tamMochila;
}

void Camino::asignarNodoInicial(Nodo* nodoInicial){
    _nodoInicial = nodoInicial;
}

void Camino::asignarDistancia(float distancia){
    _distancia = distancia;
}

void Camino::solucionGolosa(){
    assert(!encontreSolucion());

    vector<gym> gimnasios;
    vector<parada> paradas;

    for(int i = 0; i < grafo().nodos().size(); i++){
        if(grafo().nodos()[i].gimnasio){
            gym gymNuevo;
            gymNuevo.x = grafo().nodos()[i].x;
            gymNuevo.y = grafo().nodos()[i].y;
            gymNuevo.p = grafo().nodos()[i].pociones;
            gimnasios.push_back(gymNuevo);
        } else{
            parada paradaNueva;
            paradaNueva.x = grafo().nodos()[i].x;
            paradaNueva.y = grafo().nodos()[i].y;
            paradas.push_back(paradaNueva);
        }
    }

    solucion* solucionInicial = solHeuristicaGolosa(tamMochila(), gimnasios, paradas);

    if(solucionInicial != NULL && solucionInicial->d != INV){
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

bool Camino::encontreSolucion(){
    return nodoInicial() != NULL;
}

void Camino::busquedaLocal(Vecindad criterio){
    assert(encontreSolucion());

    if(criterio == permutaCamino){
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

void Camino::buscoSolucionVecinaMejor(vector<Nodo*>& nodosConsiderados){
    bool busco = true;
    map<int, int> nodosCambiados;
    
    #ifdef DEBUG
        cout << "Distancia actual = " << distancia() << endl;
    #endif

    while(busco){

        #ifdef DEBUG
            cout << "   Busco una solucion mejor:" << endl;
        #endif

        while(encuentroSolucionVecinaMejor(nodosConsiderados)){
            if(nodosCambiados.size() > 0){
                nodosCambiados.clear();
            }
        }

        #ifdef DEBUG
            cout << "   Bueno una solucion igual:" << endl;
        #endif

        if(!encuentroSolucionVecinaIgual(nodosConsiderados, nodosCambiados)){
            busco = false;
        }
    }
}

bool Camino::encuentroSolucionVecinaMejor(vector<Nodo*>& nodosConsiderados){
    bool busco = true;
    int cantNodos = nodosConsiderados.size();

    for(int i = 0; i < cantNodos && busco; i++){
        for(int j = 0; j < cantNodos && busco; j++){
            if(i != j && (estaEnElCamino(nodosConsiderados[i]) || estaEnElCamino(nodosConsiderados[j]))
                      && cambiarMejora(nodosConsiderados[i], nodosConsiderados[j])){
                busco = false;
            }
        }
    }

    return !busco;
}

bool Camino::cambiarMejora(Nodo* n1, Nodo* n2){
    bool mejora = false;

    float distanciaNueva;
    if(!estaEnElCamino(n1)){
        distanciaNueva = distanciaReemplazar(n2,n1);
    } else if(!estaEnElCamino(n2)){
        distanciaNueva = distanciaReemplazar(n1,n2);
    } else{
        distanciaNueva = distanciaPermutar(n1,n2);
    }
    
    #ifdef DEBUG
        cout << "       Distancia si cambio " << n1->id << " con " << n2->id << " = " << distanciaNueva << endl;
    #endif

    if(distanciaNueva < distancia() && cambiarSiPuedo(n1, n2)){ 
        asignarDistancia(distanciaNueva);
        mejora = true;

        #ifdef DEBUG
            cout << "¡MEJORE!" << endl;
            cout << "Cambie " << n1->id << " por " << n2->id << endl;
            imprimirSolucion();
        #endif
    }
    
    return mejora;
}

bool Camino::encuentroSolucionVecinaIgual(vector<Nodo*>& nodosConsiderados, map<int, int>& nodosCambiados){
    bool busco = true;
    int cantNodos = nodosConsiderados.size();

    for(int i = 0; i < cantNodos && busco; i++){
        for(int j = 0; j < cantNodos && busco; j++){
            if(i != j && (estaEnElCamino(nodosConsiderados[i]) || estaEnElCamino(nodosConsiderados[j]))
                      && !(nodosCambiados.count(nodosConsiderados[i]->id) > 0 && nodosCambiados[nodosConsiderados[i]->id] == nodosConsiderados[j]->id)
                      && cambiarMantieneIgual(nodosConsiderados[i], nodosConsiderados[j])){
                nodosCambiados[nodosConsiderados[i]->id] = nodosConsiderados[j]->id;
                busco = false;
            }
        }
    }

    return !busco;
}

bool Camino::cambiarMantieneIgual(Nodo* n1, Nodo* n2){
    bool mantiene = false;

    float distanciaNueva;
    if(!estaEnElCamino(n1)){
        distanciaNueva = distanciaReemplazar(n2,n1);
    } else if(!estaEnElCamino(n2)){
        distanciaNueva = distanciaReemplazar(n1,n2);
    } else{
        distanciaNueva = distanciaPermutar(n1,n2);
    }

    #ifdef DEBUG
        cout << "       Distancia si cambio " << n1->id << " con " << n2->id << " = " << distanciaNueva << endl;
    #endif

    if(distanciaNueva == distancia() && cambiarSiPuedo(n1, n2)){  
        asignarDistancia(distanciaNueva);
        mantiene = true;

        #ifdef DEBUG
            cout << "CAMBIE POR UNA DISTANCIA IGUAL" << endl;
            cout << "Cambie " << n1->id << " por " << n2->id << endl;
            imprimirSolucion();
        #endif
    }
    
    return mantiene;
}

bool Camino::cambiarSiPuedo(Nodo* n1, Nodo* n2){
    if(!estaEnElCamino(n1)){
        reemplazar(n2,n1);
    } else if(!estaEnElCamino(n2)){
        reemplazar(n1,n2);
    } else{
        permutar(n1,n2);
    }

    int pocionesDisponibles = 0;
    Nodo* nodoActual = nodoInicial();
    while(pocionesDisponibles >= 0 && nodoActual != NULL){
        if(nodoActual->gimnasio){
            pocionesDisponibles -= nodoActual->pociones;
        } else{
            pocionesDisponibles = min(tamMochila(), pocionesDisponibles + POCIONES_POKEPARADA);
        }
        nodoActual = nodoActual->siguiente;
    }

    #ifdef DEBUG
        cout << "       Pociones disponibles si intercambio = " << pocionesDisponibles << endl;
    #endif

    if(pocionesDisponibles >= 0){  
        return true;
    } else{
        if(!estaEnElCamino(n1)){
            reemplazar(n2,n1);
        } else if(!estaEnElCamino(n2)){
            reemplazar(n1,n2);
        } else{
            permutar(n1,n2);
        }

        return false;
    }
}

bool Camino::estaEnElCamino(const Nodo* n){
    return n->anterior != NULL || n->siguiente != NULL;
}

float Camino::distanciaPermutar(const Nodo* n1, const Nodo* n2){
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

float Camino::distanciaReemplazar(const Nodo* nodoViejo, const Nodo* nodoNuevo){
    float distanciaNueva = distancia();

    if(nodoViejo->anterior != NULL){
        distanciaNueva -= grafo().distancia(*(nodoViejo->anterior), *nodoViejo);
        distanciaNueva += grafo().distancia(*(nodoViejo->anterior), *nodoNuevo);
    }

    if(nodoViejo->siguiente != NULL){
        distanciaNueva -= grafo().distancia(*(nodoViejo->siguiente), *nodoViejo);
        distanciaNueva += grafo().distancia(*(nodoViejo->siguiente), *nodoNuevo);
    }

    return distanciaNueva;
}

void Camino::permutar(Nodo* n1, Nodo* n2){    
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
}

void Camino::reemplazar(Nodo* nodoViejo, Nodo* nodoNuevo){    
    if(nodoViejo->siguiente != NULL){
        nodoViejo->siguiente->anterior = nodoNuevo;
    }

    if(nodoViejo->anterior != NULL){
        nodoViejo->anterior->siguiente = nodoNuevo;
    } else{
        asignarNodoInicial(nodoNuevo);
    }

    nodoNuevo->anterior = nodoViejo->anterior;
    nodoNuevo->siguiente = nodoViejo->siguiente;
    nodoViejo->anterior = NULL;
    nodoViejo->siguiente = NULL;
}

void Camino::imprimirSolucion(){
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