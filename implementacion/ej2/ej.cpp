#include "heuristica.h"

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


	queue<int> solucion = solucionHeuristica(gimnasios, gimnasiosPoder, paradas, mochila);
	imprimirSolucion(solucion, gimnasios, paradas);


	return 0;
}
