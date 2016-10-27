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


float distancia(const gym &g1, const gym &g2);
float distancia(const parada &p1, const parada &p2);
float distancia(const parada &p, const gym &g);
float distancia(const gym &g, const parada &p);
float distancia(float x1, float x2, float y1, float y2);

void solucionGolosa(unsigned int mochila_size, vector<struct gym>& gimnasios, vector<struct parada>& paradas, vector<vector<float>>& matriz_dist);
bool leGanoAAlgunGym(vector<struct gym>& gimnasios);
void leGanoAlGymConMenosPociones(vector<struct gym>& gimnasios, vector<vector<float>>& matriz_dist);
void voyParadaMasCercana(int mochila_size, vector<struct parada>& paradas, vector<vector<float>>& matriz_dist);
void imprimirMatriz(vector<vector<float>>& matriz_dist);
void imprimirCola(priority_queue<int, vector<int>, greater<int> >& cola);
void imprimirVector(vector<struct gym>& gimnasios);
void imprimirVector(vector<struct parada>& paradas);
