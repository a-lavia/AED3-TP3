#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

    struct Nodo{
        int x;
        int y;
        int pociones;
    };

    float distancia(Nodo n1, Nodo n2);
    void magicBacktracking(int cantGimnasios, int cantPokeparadas, vector<vector<float>>& matrizDistancias, vector<Nodo>& nodos);

#endif