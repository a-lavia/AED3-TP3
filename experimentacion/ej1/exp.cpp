#include "exp.h"


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

	ofstream salida;
	salida.open("salida.csv", std::ios_base::app);
	double cantCiclosTotal = 0;
	float distancia_total = 0;

	// salida << "gimnasios,paradas,mochila,distancia,cantciclos" << endl;

	for(int i = 0; i < CANT_REPETICIONES;i++){
		
		auto inicio = RELOJ();
		
		backtracking bt(gimnasios, gimnasiosPoder, paradas, mochila);
		distancia_total = bt.correr_backtracking();
		bt.imprimirSolucion();
		
		auto fin = RELOJ();

		cantCiclosTotal += (double) chrono::duration_cast<std::chrono::nanoseconds>(fin-inicio).count();
	}

	salida << n << "," << m << "," << mochila << "," << distancia_total << "," << cantCiclosTotal / (double) CANT_REPETICIONES << endl;
	salida.close();

	return 0;
}
