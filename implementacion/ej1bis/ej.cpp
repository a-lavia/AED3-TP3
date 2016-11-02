#include <iostream>
#include <utility> //pair
#include <math.h>  //sqrt min
#include <queue>
#include "heuristica.h"

using namespace std;

//CONSTANTES GLOBALES
vector<pos> posiciones;
vector<int> gimnasiosPoder;
int mochila;

//VARIABLES GLOBALES
float mejorDistancia;
queue<int> mejorRecorrido;

//FUNCIONES AUXILIARES
bool esGimnasio(int id) {
	return id < gimnasiosPoder.size();
}

//BACKTRACK
void backTrack(float distanciaActual, int pociones, int gimnasiosPorVisitar, queue<int>& restantes, queue<int>& recorridos) {
	if(gimnasiosPorVisitar == 0) {
		if(distanciaActual < mejorDistancia) { //Ajustamos la mejor distancia encontrada y el camino recorrido
			mejorDistancia = distanciaActual;
			mejorRecorrido = recorridos;
		}
	} else if(distanciaActual < mejorDistancia) {
		int ultimo = restantes.back();
		int visitar;
		
		do {
			visitar = restantes.front();
			restantes.pop();

			float dist = recorridos.size() == 0 ? 0 : distancia(posiciones[recorridos.back()], posiciones[visitar]);

			queue<int> restantesCopia = restantes;
			queue<int> recorridosCopia = recorridos;
			recorridosCopia.push(visitar);

			//Si es un gimnasio
			if(esGimnasio(visitar) && (pociones >= gimnasiosPoder[visitar]) )
				backTrack(distanciaActual+dist, pociones-gimnasiosPoder[visitar], gimnasiosPorVisitar-1, restantesCopia, recorridosCopia);
			//Es una pokeparada
			else if(!esGimnasio(visitar))
				backTrack(distanciaActual+dist, min(pociones+3, mochila), gimnasiosPorVisitar, restantesCopia, recorridosCopia);

			restantes.push(visitar); //Lo volvemos a agregar (al final) para la siguiente iteración	
	
		} while (visitar != ultimo);

	}
}

int main(int argc, char* argv[]) {

	//Parseo la entrada
	int n;
	cin >> n;
	int m;
	cin >> m;

	cin >> mochila;

	vector<pos> gimnasios(n);
	vector<pos> paradas(m);
	gimnasiosPoder.resize(n);

	for(int i = 0; i < n; i++) {
		cin >> gimnasios[i].first;
		cin >> gimnasios[i].second;
		cin >> gimnasiosPoder[i];
	}
	for(int i = 0; i < m; i++) {
		cin >> paradas[i].first;
		cin >> paradas[i].second;
	}

    posiciones.insert(posiciones.end(), gimnasios.begin(), gimnasios.end());
    posiciones.insert(posiciones.end(), paradas.begin(), paradas.end());

	//Obtengo algun recorrido de una solución heuristica
	mejorRecorrido = solucionHeuristica(gimnasios, gimnasiosPoder, paradas, mochila);

	if(mejorRecorrido.size() != 0)
		mejorDistancia = distanciaCamino(mejorRecorrido, gimnasios, paradas);
	else
		mejorDistancia = FLOAT_MAX;

	//Preparamos los parametros del backtracking, agrego todos los nodos por verificar a una cola
	queue<int> restantes;
	for(int i = 0; i < n+m ; i++)
		restantes.push(i);

	 //Inicialmente no recorri nada
	queue<int> recorridos;

	//Corremos el backtracking
	backTrack(0, 0, gimnasiosPoder.size(), restantes, recorridos);

	if(mejorRecorrido.size() != 0) {
		cout << mejorDistancia << ' ' << mejorRecorrido.size() << ' ';
		while(!mejorRecorrido.empty()) {
			cout << (mejorRecorrido.front()+1) << ' '; //La salida pide enumerarlos desde el 1
			mejorRecorrido.pop();
		}
		cout << endl;
	} else cout << -1 << endl;

	return 0;
}
