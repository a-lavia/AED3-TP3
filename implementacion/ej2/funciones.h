#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

struct gym {
	float x;
	float y;
	int p;
	bool visitado;
};

struct parada {
	float x;
	float y;
	bool visitado;
};

struct solucion {
	float d;
	priority_queue<int, vector<int>, greater<int> > gym;
	priority_queue<int, vector<int>, greater<int> > paradas;
};


void solHeuristicaGolosa(unsigned int mochila_size, vector<struct gym>& gimnasios, 
							vector<struct parada>& paradas, vector<vector<float>>& matriz_dist);

bool solucionCasosParticulares(unsigned int mochila_size, vector<struct gym> gimnasios, 
								vector<struct parada> paradas, vector<vector<float>>& matriz_dist);

void solucionCasoGeneral(int idx_comienzo, struct solucion& sol, unsigned int mochila_size, vector<struct gym> gimnasios, 
						 vector<struct parada> paradas, vector<vector<float>>& matriz_dist);

bool leGanoAAlgunGym(vector<struct gym>& gimnasios);
void leGanoAlGymConMenosPocionesMasCercano(struct solucion& sol, vector<struct gym>& gimnasios, vector<vector<float>>& matriz_dist);
void voyParadaMasCercana(int mochila_size, struct solucion& sol, vector<struct parada>& paradas, vector<vector<float>>& matriz_dist);
int dameIdxMejorSolucion(vector<solucion>& soluciones);

void imprimirSolucion(struct solucion& sol);
void imprimirCola(priority_queue<int, vector<int>, greater<int> >& cola, int cant);
void imprimirMatriz(vector<vector<float>>& matriz_dist);
void imprimirVector(vector<struct gym>& gimnasios);
void imprimirVector(vector<struct parada>& paradas);

float distancia(const gym &g1, const gym &g2);
float distancia(const parada &p1, const parada &p2);
float distancia(const parada &p, const gym &g);
float distancia(const gym &g, const parada &p);
float distancia(float x1, float x2, float y1, float y2);