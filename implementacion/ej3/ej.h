#ifndef EJ_H
#define EJ_H

#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
#include <cassert>
#include <map>

#define POCIONES_POKEPARADA 3
#define INV -1
// #define DEBUG   // Descomentando esta linea se imprimen por pantalla datos intermedios de la busqueda local.

using namespace std;
    
struct Nodo{
    int id;
    int x;
    int y;
    int pociones;   
    bool gimnasio;

    Nodo* anterior;
    Nodo* siguiente;

    Nodo() : anterior(NULL), siguiente(NULL){

    }
};

enum Vecindad{
    permutaCamino,
    permutaYReemplazaPokeparadas
};

float distanciaNodos(Nodo n1, Nodo n2){
    float x = n1.x - n2.x;
    float y = n1.y - n2.y;
    return sqrt((x*x) + (y*y));
}

#endif