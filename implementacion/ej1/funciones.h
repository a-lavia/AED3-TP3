#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>
#include <vector>
#include <list>
#include <math.h>

using namespace std;

    struct Nodo{
        int id;
        int x;
        int y;
        int pociones;
        Nodo(int id, int x, int y, int pociones): x(x), y(y), pociones(pociones), id(id) {};
        void showMe(){
            cout << " Id: " << id /*<< " X: " << x << " Y: " << y << " P: " << pociones << endl*/;
        }
    };

    float distancia(Nodo& n1, Nodo& n2);
    void magicBacktracking(int cantGimnasios, list<Nodo>& visitados, list<Nodo>& noVisitados, int& gimnasiosVencidos);

#endif