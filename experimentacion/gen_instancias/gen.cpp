#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <math.h> //round

using namespace std;

int rnd(int min, int max) {
	return rand() % (max+1-min) + min;
}

float rndF(float min, float max) {
	return ((max-min)*((float)rand()/RAND_MAX))+min;
}

int main(int argc, char* argv[]) {

	//entrada x y gimnasios pokeparadas mochila
	int xMax;
	int yMax;

	int gimnasios;
	int pokeparadas;

	int mochila;

	int seed = rand();
	int dificultad = 50;

	if(argc < 6) {
		cout << "./gen x y gym paradas mochila [dificultad] [seed]" << endl;
		return 0;
	} else {
		xMax = strtol(argv[1], NULL, 10);
		yMax = strtol(argv[2], NULL, 10);
		gimnasios = strtol(argv[3], NULL, 10);
		pokeparadas = strtol(argv[4], NULL, 10);
		mochila = strtol(argv[5], NULL, 10);
		if(argc > 6) dificultad = strtol(argv[6], NULL, 10);
		if(argc > 7) seed = strtol(argv[7], NULL, 10);
	}

	srand(seed);

	ofstream mapa;
	mapa.open("mapa");

	mapa << gimnasios << ' ' << pokeparadas << ' ' << mochila << endl;

	int pociones = pokeparadas*3;

	float poderGymMedio= pociones / (float) gimnasios;
	poderGymMedio = poderGymMedio * ( (float) dificultad / (float) 100);

	//int sumPoder = 0; //DEBUG

	for(int i = 0; i < gimnasios; i++) {

		int poderGym = 0;
		if(dificultad != 0) { 
			poderGym = round(rndF(0, poderGymMedio*2));
			poderGym = poderGym > mochila ? mochila : poderGym;
			pociones -= poderGym;
			if(pociones < 0) {
				poderGym += pociones;
				pociones = 0;
			}
		}

		//sumPoder += poderGym; //DEBUG

		mapa << rnd(0, xMax) << ' ' << rnd(0, yMax) << ' ' << poderGym << endl;
	}

	//DEBUG
	//cout << "poder medio gimnasios objetivo " << poderGymMedio << endl;
	//cout << "suma poder gimnasio " << sumPoder << endl;
	//cout << "medio gimnasio real " << (sumPoder/(float) gimnasios) << endl;


	for(int i = 0; i < pokeparadas; i++)
		mapa << rnd(0, xMax) << ' ' << rnd(0, yMax) << endl;


	mapa.close();
	return 0;
}
