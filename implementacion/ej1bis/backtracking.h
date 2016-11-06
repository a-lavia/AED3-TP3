#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <iostream>
#include <vector>
#include <queue>
#include "heuristica.h"

using namespace std;

class backtracking {

	public:

		backtracking(vector<pos>& gimnasios, vector<int>& gimnasiosPoder, vector<pos>& paradas, int mochila);

		void correr_backtracking();

		float correr_backtracking(queue<int>& solucion);

		void imprimirSolucion();

	private:

		//
		void btRecursivo(float distanciaActual, int pociones, int gimnasiosPorVisitar, queue<int>& restantes, queue<int>& recorridos);

		bool esGimnasio(int id);

		//
		vector<pos> posiciones;
		vector<int> gimnasiosPoder;
		int mochila;

		//
		float mejorDistancia;
		queue<int> mejorRecorrido;

};


#endif
