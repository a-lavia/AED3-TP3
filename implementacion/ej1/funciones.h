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

    struct Solucion{
        list<Nodo> camino;
        float distanciaRecorrida;
        void showMe(){
            if(distanciaRecorrida == -8){
                cout << -1 << endl;;
            }else{
                cout << distanciaRecorrida << " " << camino.size() << " ";
                for(list<Nodo>::iterator it = camino.begin(), end = camino.end(); it != end; it++){
                    cout << it->id << " ";
                }
                cout << endl;
            }
        }
    };

    float distancia(Nodo& n1, Nodo& n2);
    void magicBacktracking(int& cantGimnasios, list<Nodo>& visitados, list<Nodo>& noVisitados, int gimnasiosVencidos, int pociones, int& mochila, float distanciaRecorrida, Solucion& mejorSolucionActual);
    bool subsolucionFactible(int pociones, float distanciaRecorrida, float mejorDistanciaActual);

#endif