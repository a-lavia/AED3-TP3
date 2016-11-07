#include "grasp.h"

int main(int argc, char* argv[]) {

	int iteraciones;
	cin >> iteraciones;
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
	cout << g.correr_grasp(iteraciones, semilla) << endl;

	return 0;
}
