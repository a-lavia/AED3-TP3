#ifndef AUX_EJ3_H
#define AUX_EJ3_H

#include <iostream>
#include <cassert>
#include <math.h>
#include <vector>
#include <queue>
#include <map>
#include <set>

#define POCIONES_POKEPARADA 3
#define INV -1
// #define DEBUG   // Descomentando esta linea se imprimen por pantalla datos intermedios del ejercicio.

using namespace std;
    
struct Nodo{
    int id;
    int x;
    int y;
    int pociones;   
    bool gimnasio;

    Nodo* anterior;
    Nodo* siguiente;

    Nodo() : id(INV), anterior(NULL), siguiente(NULL){

    }
};

struct Cambios{
    int cantPermutacionesParaMejorar;
    int cantPermutacionesParaMantener;
    int cantReemplazosParaMejorar;
    int cantReemplazosParaMantener;

    Cambios() : cantPermutacionesParaMejorar(0), cantPermutacionesParaMantener(0), cantReemplazosParaMejorar(0), cantReemplazosParaMantener(0){

    }
};

enum Vecindad{
    permutaCamino,
    permutaYReemplazaPokeparadas
};

double distanciaNodos(Nodo n1, Nodo n2);

#endif
