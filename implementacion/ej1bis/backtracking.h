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

		//Corre el backtracking, devuelve la distancia
		float correr_backtracking();

		//Igual al anterior pero devuelve la menor distancia y copia la solucion a la cola del parametro (que debería estar vacía)
		float correr_backtracking(queue<int>& solucion);

		//Imprime la solución (debería correrse el backtracking antes de llamarla)
		void imprimirSolucion();

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
