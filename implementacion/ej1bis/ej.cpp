#include <iostream>
#include <utility> //pair
#include <math.h>  //sqrt min
#include <queue>

#define FLOAT_MAX 3.4028234664e+38

using namespace std;

//CONSTANTES GLOBALES
vector<pair<int, int>> posiciones;
vector<int> gimnasiosPoder;
int mochila;

//VARIABLES GLOBALES
float mejorDistancia = FLOAT_MAX;
queue<int> mejorRecorrido;

//FUNCIONES AUXILIARES
bool esGimnasio(int id) {
	return id < gimnasiosPoder.size();
}

float distancia(pair<int, int>& a, pair<int, int>& b){
    int x = a.first - b.first;
    int y = a.second - b.second;
    return sqrt((x*x) + (y*y));
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

	int n;
	cin >> n;
	int m;
	cin >> m;

	cin >> mochila;

	posiciones.resize(n+m);
	gimnasiosPoder.resize(n);

	for(int i = 0; i < n; i++) {
		cin >> posiciones[i].first;
		cin >> posiciones[i].second;
		cin >> gimnasiosPoder[i];
	}
	for(int i = 0; i < m; i++) {
		cin >> posiciones[i+n].first;
		cin >> posiciones[i+n].second;
	}

	queue<int> restantes; 	//Agrego todos los nodos por verificar a una cola
	for(int i = 0; i < n+m ; i++)
		restantes.push(i);

	queue<int> recorridos; //Inicialmente no recorri nada

	backTrack(0, 0, gimnasiosPoder.size(), restantes, recorridos);

	//Imprimo (sumo uno porque la salida pide enumerarlos desde el 1)
	cout << mejorDistancia << ' ' << mejorRecorrido.size() << ' ';
	while(!mejorRecorrido.empty()) {
		cout << (mejorRecorrido.front()+1) << ' ';
		mejorRecorrido.pop();
	}
	cout << endl;

}
