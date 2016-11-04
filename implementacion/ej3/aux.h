#ifndef AUX_EJ3_H
#define AUX_EJ3_H

#include <iostream>
#include <cassert>
#include <math.h>
#include <vector>
#include <queue>
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

float distanciaNodos(Nodo n1, Nodo n2);

#endif