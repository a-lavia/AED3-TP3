#ifndef EJ_H_
#define EJ_H_

#include <iostream>
#include <vector>
#include <math.h>
#include <stack>
#include <map>
#include <cassert>

#define INV -1

using namespace std;
    
struct Nodo{
    int id;
    int x;
    int y;
    int pociones;   
    bool gimnasio;

    bool visitado;
    int anterior;
    int siguiente;

    Nodo() : visitado(false), anterior(INV), siguiente(INV){

    }
};

enum Vecindad{
    vecindad1,  // Nombres provisorios
    vecindad2
};

float distanciaNodos(Nodo n1, Nodo n2){
    int x = n1.x - n2.x;
    int y = n1.y - n2.y;
    return sqrt((x*x) + (y*y));
}

#endif