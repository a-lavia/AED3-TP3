#include <iostream>
#include <vector>
#include "backtracking.h"

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

	backtracking bt(gimnasios, gimnasiosPoder, paradas, mochila);

	queue<int> solucion;
	float distancia = bt.correr_backtracking(&solucion);

	if(solucion.size() != 0) {
		cout << distancia << ' ' << solucion.size() << ' ';
		while(!solucion.empty()) {
			cout << (solucion.front()+1) << ' '; //La salida pide enumerarlos desde el 1
			solucion.pop();
		}
		cout << endl;
	} else cout << -1 << endl;

	return 0;
}
