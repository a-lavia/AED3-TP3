#ifndef EJ_H_
#define EJ_H_

#include <iostream>
#include <vector>
#include <math.h>
#include <stack>
#include <map>
#include <cassert>

#define POCIONES_POKEPARADA 3

using namespace std;
    
struct Nodo{
    int id;
    int x;
    int y;
    int pociones;   
    bool gimnasio;

    bool visitado;
    Nodo* anterior;
    Nodo* siguiente;

    Nodo() : visitado(false), anterior(NULL), siguiente(NULL){

    }
};

enum Vecindad{
    intercambiaNodosVisitados,
    intercambiaPokeparadas
};

float distanciaNodos(Nodo n1, Nodo n2){
    int x = n1.x - n2.x;
    int y = n1.y - n2.y;
    return sqrt((x*x) + (y*y));
}

#endif