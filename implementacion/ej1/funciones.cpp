#include "funciones.h"

float distancia(Nodo& n1, Nodo& n2){
    int x = n1.x - n2.x;
    int y = n1.y - n2.y;
    return sqrt((x*x) + (y*y));
}

void magicBacktracking(int cantGimnasios, list<Nodo>& visitados, list<Nodo>& noVisitados, int& gimnasiosVencidos){
    cout << "Caso " << gimnasiosVencidos << ": ";
    gimnasiosVencidos++;
/*    if(noVisitados.size() == 1){
        noVisitados.front().showMe();
        cout << endl;
        return;
    }*/
    for(list<Nodo>::iterator itNodos = visitados.begin(), end = visitados.end(); itNodos != end; ++itNodos){
        itNodos->showMe();
    }
    cout <<endl;

    for (list<Nodo>::iterator itNoVisitados = noVisitados.begin(); itNoVisitados != noVisitados.end();){
        // remember this
        Nodo nodoBackup = *itNoVisitados;
        visitados.push_back(nodoBackup);
        itNoVisitados = noVisitados.erase(itNoVisitados);

        magicBacktracking(cantGimnasios, visitados, noVisitados, gimnasiosVencidos);

        noVisitados.insert(itNoVisitados, nodoBackup);
        visitados.pop_back();
    }
}