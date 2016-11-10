#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <iostream>
#include <vector>
#include <queue>
#include "../ej2/SegundaHeuristica.h"

using namespace std;

class backtracking {

	public:

		backtracking(vector<pos>& gimnasios, vector<int>& gimnasiosPoder, vector<pos>& paradas, int mochila);

		//Corre el backtracking, devuelve la distancia
		float correr_backtracking();

		//Igual al anterior pero devuelve la distancia y copia la solucion a la cola del parametro
		float correr_backtracking(queue<int>* solucion);

	private:

		//
		void btRecursivo(float distanciaActual, int pociones, int gimnasiosPorVisitar, queue<int>& restantes, queue<int>& recorridos);

		bool esGimnasio(int id);

		//
		vector<pos> gimnasios;
		vector<int> gimnasiosPoder;
		vector<pos> paradas;
		int mochila;

		vector<pos> posiciones;

		//
		float mejorDistancia;
		queue<int> mejorRecorrido;

};


#endif
