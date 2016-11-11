#include <chrono>
#include <iostream>
#include <fstream>

#include "../../implementacion/ej4/grasp.h"

#define TIEMPO chrono::high_resolution_clock::now

using namespace std;

void generarMapa(int x, int y, int g, int p, int dificultad, int semilla, int mochila, vector<pair<int, int>>& gimnasios, vector<int>& gimnasiosPoder, vector<pair<int, int>>& paradas);

int main(int argc, char* argv[]) {

	//PARAMETROS DEL MAPA
	int x = 100;
	int y = 100;

	int g = 50;
	int p = 50;

	int dificultad = 50;
	int semilla = 141298;
	int mochila = 20;

	vector<pos> gimnasios;
	vector<int> gimnasiosPoder;
	vector<pos> paradas;

	generarMapa(x, y, g, p, dificultad, semilla, mochila, gimnasios, gimnasiosPoder, paradas);

	//IMPRIMIR MAPA
/*
	for(int i = 0; i < g; i++)
		cout << gimnasios[i].first << " " << gimnasios[i].second << " " << gimnasiosPoder[i] << endl;

	for(int i = 0; i < p; i++)
		cout << paradas[i].first << " " << paradas[i].second << endl;
*/

	//PARAMETROS DE GRASP
	int iteraciones = 100;
	criterio_parada criterio = iteraciones_fijas;

	//CORREMOS EL EXPERIMENTO
	ofstream salida;
	salida.open("experimento_1.csv");

	salida << "alfa,omega,distancia" << endl;

	grasp grasp_solver = grasp(gimnasios, gimnasiosPoder, paradas, mochila);

	for(int i = 0; i < 100; i++) {
		cout << i << endl;
		for(int j = 0; j < 100; j++) {
			float alfa = i / (float) 100;
			float omega = j / (float) 100;
			float distancia =  grasp_solver.correr_grasp(criterio, iteraciones, alfa, omega, semilla);
			salida << i << ',' << j << ',' << distancia << endl;
		}
	}

	salida.close();

	return 0;
}
