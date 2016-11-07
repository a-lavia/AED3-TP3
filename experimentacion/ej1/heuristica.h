#ifndef HEURISTICA_H_
#define HEURISTICA_H_

#include <iostream>
#include <utility> //pair
#include <math.h>  //sqrt min
#include <queue>
#include <list>

#define FLOAT_MAX 3.4028234664e+38

using namespace std;

typedef pair<int, int> pos;

float distancia(pos& a, pos& b);

float distanciaCamino(queue<int> camino, vector<pos>& posGym, vector<pos>& posParada);

queue<int> heuristicaVecinoCercano(vector<pos>& posiciones, list<int>& nodos);

queue<int> heuristicaParadasCercanas(queue<int>& caminoGimnasios, vector<pos>& posGimnasios, vector<int>& gimnasiosPoder, vector<pos>& posParadas, list<int>& paradas, int mochila);

queue<int> solucionHeuristica(vector<pos>& gimnasios, vector<int>& gimnasiosPoder, vector<pos>& paradas, int mochila);

#endif
