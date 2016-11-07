#include "Camino.h"

Camino::Camino(Grafo g, int tamMochila){
    _grafo = g;
    _tamMochila = tamMochila;
    _nodoInicial = NULL;
    _distancia = INV;
}

Camino::Camino(){
    _tamMochila = INV;
    _nodoInicial = NULL;
    _distancia = INV;
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

    _grafo = g;
    _tamMochila = tamMochila;
}

Camino& Camino::operator=(const Camino& otro){
    _grafo = otro._grafo;
    _tamMochila = otro._tamMochila;
    if(otro._nodoInicial != NULL){
        _nodoInicial = &_grafo.nodo(otro._nodoInicial->id);
    }
    _distancia = otro._distancia;
    _cambios = otro._cambios;

    return *this;
}

Grafo& Camino::grafo(){
    return _grafo;
}

double Camino::distancia() const{
    return _distancia;
}

int Camino::tamMochila() const{
    return _tamMochila;
}

void Camino::asignarNodoInicial(Nodo* nodoInicial){
    _nodoInicial = nodoInicial;
}

void Camino::asignarDistancia(double distancia){
    _distancia = distancia;
}

void Camino::asignarSolucion(double distancia, queue<int>& caminoCola){
    asignarDistancia(distancia);

    int tamCamino = caminoCola.size();
    vector<int> camino(tamCamino);
    for(int i = 0; i < tamCamino; i++){
        camino[i] = caminoCola.front();
        caminoCola.pop();
    }

    if(!camino.empty()){
        asignarNodoInicial(&grafo().nodos()[camino[0]]);
    }

    if(tamCamino > 1){
        grafo().nodos()[camino[0]].siguiente = &grafo().nodos()[camino[1]];
        for(int i = 1; i < tamCamino - 1; i++){
            grafo().nodos()[camino[i]].anterior = &grafo().nodos()[camino[i-1]];
            grafo().nodos()[camino[i]].siguiente = &grafo().nodos()[camino[i+1]];
        }
        grafo().nodos()[camino[tamCamino - 1]].anterior = &grafo().nodos()[camino[tamCamino - 2]];
    }
}

void Camino::asignarSolucionGolosaJ(){
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

    if(solucionInicial != NULL && solucionInicial->d != INV){
        asignarSolucion(solucionInicial->d, solucionInicial->camino);
    }
}

void Camino::asignarSolucionGolosaA(){
    vector<pos> gimnasios;
    vector<int> gimnasiosPoder;
    vector<pos> paradas;
    
    for(int i = 0; i < grafo().nodos().size(); i++){
        pos posNueva;
        posNueva.first = grafo().nodos()[i].x;
        posNueva.second = grafo().nodos()[i].y;
        if(grafo().nodos()[i].gimnasio){
            gimnasios.push_back(posNueva);
            gimnasiosPoder.push_back(grafo().nodos()[i].pociones);
        } else{
            paradas.push_back(posNueva);
        }
    }

    queue<int> caminoCola = solucionHeuristica(gimnasios, gimnasiosPoder, paradas, tamMochila());

    if(caminoCola.size() != 0){
        asignarSolucion(distanciaCamino(caminoCola, gimnasios, paradas), caminoCola);
    }
}

bool Camino::encontreSolucion(){
    return _distancia != INV;
}

bool Camino::encontreCamino(){
    return _nodoInicial != NULL;
}

Cambios Camino::busquedaLocal(Vecindad criterio){
    assert(encontreCamino());

    Cambios cambiosVacio;
    _cambios = cambiosVacio;

    if(criterio == permutaCamino){
        vector<Nodo*> nodosVisitados;
        
        Nodo* nodoActual = _nodoInicial;
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

    #ifdef DEBUG
        cout << "Cantidad de permutaciones para mejorar = " << _cambios.cantPermutacionesParaMejorar << endl;
        cout << "Cantidad de permutaciones para mantener = " << _cambios.cantPermutacionesParaMantener << endl;
        cout << "Cantidad de reemplazos para mejorar = " << _cambios.cantReemplazosParaMejorar << endl;
        cout << "Cantidad de reemplazos para mantener = " << _cambios.cantReemplazosParaMantener << endl;
    #endif

    return _cambios;
}

void Camino::buscoSolucionVecinaMejor(vector<Nodo*>& nodosConsiderados){
    int cantCambios = 0;
    bool busco = true;
    map<int, set<int>> nodosCambiados;
    
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

    bool permute = false;

    double distanciaNueva;
    if(!estaEnElCamino(n1)){
        distanciaNueva = distanciaReemplazar(n2,n1);
    } else if(!estaEnElCamino(n2)){
        distanciaNueva = distanciaReemplazar(n1,n2);
    } else{
        distanciaNueva = distanciaPermutar(n1,n2);
        permute = true;
    }
    
    #ifdef DEBUG
        cout << "       Distancia si cambio " << n1->id << " con " << n2->id << " = " << distanciaNueva << endl;
    #endif

    if(distanciaNueva < distancia() && cambiarSiPuedo(n1, n2)){ 
        asignarDistancia(distanciaNueva);
        mejora = true;

        if(permute){
            _cambios.cantPermutacionesParaMejorar++;
        } else{
            _cambios.cantReemplazosParaMejorar++;
        }

        #ifdef DEBUG
            cout << "¡MEJORE!" << endl;
            cout << "Cambie " << n1->id << " por " << n2->id << endl;
            imprimirSolucion();
        #endif
    }
    
    return mejora;
}

bool Camino::encuentroSolucionVecinaIgual(vector<Nodo*>& nodosConsiderados, map<int, set<int>>& nodosCambiados){
    bool busco = true;
    int cantNodos = nodosConsiderados.size();

    for(int i = 0; i < cantNodos && busco; i++){
        for(int j = 0; j < cantNodos && busco; j++){
            if(i != j && (estaEnElCamino(nodosConsiderados[i]) || estaEnElCamino(nodosConsiderados[j]))
                      && !(nodosCambiados.count(nodosConsiderados[i]->id) > 0 && nodosCambiados[nodosConsiderados[i]->id].count(nodosConsiderados[j]->id) > 0)
                      && cambiarMantieneIgual(nodosConsiderados[i], nodosConsiderados[j])){
                nodosCambiados[nodosConsiderados[i]->id].insert(nodosConsiderados[j]->id);
                busco = false;
            }
        }
    }

    return !busco;
}

bool Camino::cambiarMantieneIgual(Nodo* n1, Nodo* n2){
    bool mantiene = false;

    bool permute = false;

    double distanciaNueva;
    if(!estaEnElCamino(n1)){
        distanciaNueva = distanciaReemplazar(n2,n1);
    } else if(!estaEnElCamino(n2)){
        distanciaNueva = distanciaReemplazar(n1,n2);
    } else{
        distanciaNueva = distanciaPermutar(n1,n2);
        permute = true;
    }

    #ifdef DEBUG
        cout << "       Distancia si cambio " << n1->id << " con " << n2->id << " = " << distanciaNueva << endl;
    #endif

    if(distanciaNueva == distancia() && cambiarSiPuedo(n1, n2)){  
        asignarDistancia(distanciaNueva);
        mantiene = true;

        if(permute){
            _cambios.cantPermutacionesParaMantener++;
        } else{
            _cambios.cantReemplazosParaMantener++;
        }

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
    Nodo* nodoActual = _nodoInicial;
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

double Camino::distanciaPermutar(const Nodo* n1, const Nodo* n2){
    double distanciaNueva = distancia();

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

double Camino::distanciaReemplazar(const Nodo* nodoViejo, const Nodo* nodoNuevo){
    double distanciaNueva = distancia();

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
    int tamCamino = 0;

    if(_nodoInicial != NULL){
        camino.push(_nodoInicial->id);
        tamCamino++;

        Nodo* nodoActual = _nodoInicial;
        while(nodoActual->siguiente != NULL){
            camino.push(nodoActual->siguiente->id);
            tamCamino++;
            nodoActual = nodoActual->siguiente;
        }
    }

    cout << distancia() << " " << tamCamino;
    while(!camino.empty()){
        cout << " " << camino.front();
        camino.pop();
    }
    cout << endl;
}

double Camino::devolverSolucion(queue<int>& camino){
    assert(encontreSolucion() && camino.empty());

    if(_nodoInicial != NULL){
        camino.push(_nodoInicial->id);
        Nodo* nodoActual = _nodoInicial;
        while(nodoActual->siguiente != NULL){
            camino.push(nodoActual->siguiente->id);
            nodoActual = nodoActual->siguiente;
        }
    }

    return distancia();
}