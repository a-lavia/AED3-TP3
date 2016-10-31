#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

int rnd(int min, int max) {
	return rand() % (max+1-min) + min;
}

int main(int argc, char* argv[]) {

	//entrada x y gimnasios pokeparadas mochila
	int xMax;
	int yMax;

	int gimnasios;
	int pokeparadas;

	int mochila;

	int seed = rand();

	if(argc < 6) {
		cout << "./gen x y gym paradas mochila [seed]" << endl;
		return 0;
	} else {
		xMax = strtol(argv[1], NULL, 10);
		yMax = strtol(argv[2], NULL, 10);
		gimnasios = strtol(argv[3], NULL, 10);
		pokeparadas = strtol(argv[4], NULL, 10);
		mochila = strtol(argv[5], NULL, 10);
		if(argc > 6) seed = strtol(argv[6], NULL, 10);
	}

	srand(seed);

	ofstream mapa;
	mapa.open("mapa");

	mapa << gimnasios << ' ' << pokeparadas << ' ' << mochila << endl;

	int pociones = pokeparadas*3;
	int poderGymPromedio = ((int) (pociones / (float) gimnasios));

	for(int i = 0; i < gimnasios; i++) {

		int poderGym = rnd(1, poderGymPromedio*2);
		poderGym = poderGym > mochila ? mochila : poderGym;
		pociones -= poderGym;
		if(pociones < 0) {
			poderGym += pociones;
			pociones = 0;
		}

		mapa << rnd(0, xMax) << ' ' << rnd(0, yMax) << ' ' << poderGym << endl;
	}

	for(int i = 0; i < pokeparadas; i++)
		mapa << rnd(0, xMax) << ' ' << rnd(0, yMax) << endl;


	mapa.close();
	return 0;
}
