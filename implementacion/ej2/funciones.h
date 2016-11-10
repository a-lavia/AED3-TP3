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

solucion* solHeuristicaGolosa(unsigned int mochilaSize, vector<struct gym>& gimnasios, 
							vector<struct parada>& paradas);

void correrHeuristica(int idxComienzo, struct solucion& sol, unsigned int mochilaSize, vector<struct gym> gimnasios, 
				      vector<struct parada> paradas, vector<vector<float>>& matrizDistancias);

bool leGanoAAlgunGym(int mochila, vector<struct gym>& gimnasios);

void leGanoAlGymMasCercano(int& mochila, int& idxActual, struct solucion& sol, vector<struct gym>& gimnasios, 
	                       vector<vector<float>>& matrizDistancias);

void voyParadaMasCercana(int& mochila, int& idxActual, int mochilaSize, int cantGym, struct solucion& sol, 
						 vector<struct parada>& paradas, vector<vector<float>>& matrizDistancias);

void imprimirSolucion(struct solucion& sol);
void imprimirCola(queue<int>& cola);
void imprimirMatriz(vector<vector<float>>& matrizDistancias);
void imprimirVector(vector<struct gym>& gimnasios);
void imprimirVector(vector<struct parada>& paradas);

float distancia2(const nodo &n1, const nodo &n2);

#endif