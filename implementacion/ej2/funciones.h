#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

struct nodo {
	float x;
	float y;
	bool visitado;
};

struct gym : nodo {
	int p;
};

struct parada : nodo {
};

struct solucion {
	float d;
	queue<int> camino;
};

solucion* solHeuristicaGolosa(unsigned int mochila_size, vector<struct gym>& gimnasios, 
							vector<struct parada>& paradas);

bool solucionCasosParticulares(unsigned int mochila_size, vector<struct gym> gimnasios, vector<struct parada> paradas,
                                vector<vector<float>>& matriz_dist, solucion*& mejor_sol);

void solucionCasoGeneral(int idx_comienzo, struct solucion& sol, unsigned int mochila_size, vector<struct gym> gimnasios, 
						 vector<struct parada> paradas, vector<vector<float>>& matriz_dist);

bool leGanoAAlgunGym(vector<struct gym>& gimnasios);
void leGanoAlGymMasCercano(struct solucion& sol, vector<struct gym>& gimnasios, vector<vector<float>>& matriz_dist);
void voyParadaMasCercana(int mochila_size, struct solucion& sol, vector<struct parada>& paradas, vector<vector<float>>& matriz_dist);

void imprimirSolucion(struct solucion& sol);
void imprimirCola(queue<int>& cola);
void imprimirMatriz(vector<vector<float>>& matriz_dist);
void imprimirVector(vector<struct gym>& gimnasios);
void imprimirVector(vector<struct parada>& paradas);

float distancia(const nodo &n1, const nodo &n2);

#endif