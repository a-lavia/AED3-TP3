#ifndef GRASP_H
#define GRASP_H

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

		float correr_grasp(int maxIteraciones, float alfa, int semilla);

		float correr_grasp(int maxIteraciones, float alfa, int semilla, queue<int>* solucion);

		//float correr_grasp_reactivo(int maxIteraciones);

	private:

		//
		int aleatorio(int min, int max);

		bool esGym(int i);

		float distancia(int a, int b);

		float distanciaCamino(queue<int> camino);

		//
		list<pair<int, float>> obtenerCandidatos();

		void actualizarCandidatos(list<pair<int, float>>& candidatos, vector<bool>& visitados, int actual, int pociones);

		vector<int> obtenerCandidatosRestringidos(list<pair<int, float>>& candidatos, float alfa);

		queue<int> graspSolucionAleatoria(float alfa);

		//
		vector<pos> gimnasios;
		vector<int> gimnasiosPoder;
		vector<pos> paradas;
		int mochila;

		Grafo grafo;

};

#endif
