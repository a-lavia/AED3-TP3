#include "funciones.h"

float distancia(Nodo& n1, Nodo& n2){
    int x = n1.x - n2.x;
    int y = n1.y - n2.y;
    return sqrt((x*x) + (y*y));
}

void magicBacktracking(int& cantGimnasios, list<Nodo>& visitados, list<Nodo>& noVisitados, int gimnasiosVencidos, int pociones, int& mochila, float distanciaRecorrida, Solucion& mejorSolucionActual){
    
    list<Nodo>::reverse_iterator fin = visitados.rbegin();
    if(visitados.size() > 0){
        pociones += fin->pociones;
    }

    if(visitados.size() > 1){
        fin++;
        distanciaRecorrida += distancia(*fin, visitados.back());
    }
    if((visitados.size() > 0) && (visitados.back().id < cantGimnasios+1)){
        gimnasiosVencidos++;
    }
    for(list<Nodo>::iterator itNodos = visitados.begin(), end = visitados.end(); itNodos != end; ++itNodos){
        itNodos->showMe();
    }cout <<endl;
    
    if(subsolucionFactible(pociones, distanciaRecorrida, mejorSolucionActual.distanciaRecorrida)){
        if(cantGimnasios != gimnasiosVencidos){
            for (list<Nodo>::iterator itNoVisitados = noVisitados.begin(); itNoVisitados != noVisitados.end();){
                // remember this
                Nodo nodoBackup = *itNoVisitados;
                visitados.push_back(nodoBackup);
                itNoVisitados = noVisitados.erase(itNoVisitados);
            
                magicBacktracking(cantGimnasios, visitados, noVisitados, gimnasiosVencidos, pociones, mochila, distanciaRecorrida, mejorSolucionActual);
            
                noVisitados.insert(itNoVisitados, nodoBackup);
                visitados.pop_back();
            }
        } else{
            mejorSolucionActual.distanciaRecorrida = distanciaRecorrida;
            cout << "Solucion: " << distanciaRecorrida;
            for (list<Nodo>::iterator it = visitados.begin(); it != visitados.end(); it++){
                cout << " " << it->id;
            }
            // mejorSolucionActual.camino.clear();
            //COPIAR EL CAMINO GENERA EXPLOSIONES Y MAS
            // mejorSolucionActual.camino.assign(visitados.begin(), visitados.end());
        }
    }
}

bool subsolucionFactible(int pociones, float distanciaRecorrida, float mejorDistanciaActual){
    bool res = pociones >= 0;
    if(mejorDistanciaActual == -8){
        return res;
    }
    res = res && (distanciaRecorrida <= mejorDistanciaActual);
    return res;
}