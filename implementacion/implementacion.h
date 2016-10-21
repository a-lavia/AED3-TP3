#ifndef IMPLEMENTACION_H_
#define IMPLEMENTACION_H_

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
void leerEntrada(int* cantGimnasios, int* cantPokeparadas, vector<vector<float>>& matrizAdyacencia);

#endif