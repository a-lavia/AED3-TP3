#include <chrono>
#include <iostream>
#include <fstream>

#include "../../implementacion/ej4/grasp.h"

#define REPETICIONES 50
#define TIEMPO chrono::high_resolution_clock::now

using namespace std;

void generarMapa(int x, int y, int g, int p, int dificultad, int semilla, int mochila, vector<pair<int, int>>& gimnasios, vector<int>& gimnasiosPoder, vector<pair<int, int>>& paradas);

int main(int argc, char* argv[]) {

	//PARAMETROS DEL MAPA
	int x = 1000;
	int y = 1000;
	int g = 10;
	int p = 20;
	int dificultad = 50;
	int semilla = 123;
	int mochila = 20;

	vector<pos> gimnasios;
	vector<int> gimnasiosPoder;
	vector<pos> paradas;

	criterio_parada criterio = iteraciones_fijas;
	float alfa = 0.1;
	float omega = 0.1;

	ofstream salida;
	salida.open("tiempos_2.csv");

	salida << "gimnasios,tiempo" << endl;

	grasp grasp_solver = grasp(gimnasios, gimnasiosPoder, paradas, mochila);

	for(int i = g; i < 250; i++) {

		generarMapa(x, y, i, p, dificultad, semilla, mochila, gimnasios, gimnasiosPoder, paradas);

		double tiempoTotal = 0;
		for(int j = 0; j < REPETICIONES; j++) {
			auto inicio = TIEMPO();
			grasp_solver.correr_grasp(criterio, i, alfa, omega, semilla);
			auto fin = TIEMPO();
			double tiempo = (double) chrono::duration_cast<std::chrono::nanoseconds>(fin-inicio).count();
			tiempoTotal += tiempo;
		}

		salida << i << ',' << tiempoTotal / (double) REPETICIONES << endl;

	}

	salida.close();

	return 0;
}
