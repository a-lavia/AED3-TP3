#ifndef POKE_GRASP_H
#define POKE_GRASP_H

#include <utility> //pair
#include <vector>
#include <queue>
#include <list>

#include "../ej3/Camino.h"
#include "../ej3/Grafo.h"

using namespace std;

class grasp {

	public:

		grasp(vector<pos>& g, vector<int>& gp, vector<pos>& p, int m);

		float correr_grasp(int maxIteraciones, float alfa, float omega, int semilla);

		float correr_grasp(int maxIteraciones, float alfa, float omega, int semilla, queue<int>* solucion);

		//float correr_grasp_reactivo(int maxIteraciones);

	private:

		//
		int int_aleatorio(int min, int max);

		bool bool_aleatorio(float prob);

		bool esGym(int i);

		float distancia(int a, int b);

		float distanciaCamino(queue<int> camino);

		//

		vector<int> obtenerCandidatosRestringidos(list<pair<int, float>>& candidatos, float alfa);

		queue<int> graspSolucionGimnasios(float alfa);

		queue<int> graspSolucionAleatoria(queue<int>& caminoGimnasios, float alfa, float omeg);

		//
		vector<pos> gimnasios;
		vector<int> gimnasiosPoder;
		vector<pos> paradas;
		int mochila;

		Grafo grafo;

};

#endif
