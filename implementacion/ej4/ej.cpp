#include "grasp.h"

int main(int argc, char* argv[]) {

	int iteraciones;
	cin >> iteraciones;
	float alfa;
	cin >> alfa;
	float omega;
	cin >> omega;
	int semilla;
	cin >> semilla;

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

	grasp g = grasp(gimnasios, gimnasiosPoder, paradas, mochila);

	queue<int> solucion;
	float distancia =  g.correr_grasp(iteraciones_fijas, iteraciones, alfa, omega, semilla, &solucion);

	cout << distancia << ' ' << solucion.size() << ' ';
	while(!solucion.empty()) {
		cout << solucion.front() << ' ';
		solucion.pop();
	}
	cout << endl;

	return 0;
}
