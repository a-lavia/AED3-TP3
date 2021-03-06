#include "exp.h"

using namespace std;

int main(int argc, char* argv[]) {

	//Parseo la entrada
	int n;
	cin >> n;
	int m;
	cin >> m;
	int mochila;
	cin >> mochila;

	vector<pos> gimnasios(n);
	vector<int> gimnasiosPoder(n);
	vector<pos> paradas(m);

	for(int i = 0; i < n; i++) {
		cin >> gimnasios[i].first;
		cin >> gimnasios[i].second;
		cin >> gimnasiosPoder[i];
	}
	for(int i = 0; i < m; i++) {
		cin >> paradas[i].first;
		cin >> paradas[i].second;
	}

	ofstream salida,camino;
	salida.open("salida.csv", std::ios_base::app);
	camino.open("camino.csv", std::ios_base::app);
	double cantCiclosTotal = 0;
	float distancia = 0;


	for(int i = 0; i < CANT_REPETICIONES;i++){

		auto inicio = RELOJ();
		queue<int> solucion = solucionHeuristica(gimnasios, gimnasiosPoder, paradas, mochila);
		distancia = distanciaCamino(solucion, gimnasios, paradas);
		auto fin = RELOJ();
		

		if(i == 0){
			if(distancia == 0 && solucion.size() == 0){
				distancia = -1;
			}
			imprimirSolucionAOstream(camino,solucion,gimnasios,paradas);
			camino.close();
		}

		cantCiclosTotal += (double) chrono::duration_cast<std::chrono::nanoseconds>(fin-inicio).count();
	}

	salida << n << "," << m << "," << mochila << "," << distancia << "," << cantCiclosTotal / (double) CANT_REPETICIONES << endl;
	salida.close();

	return 0;
}
