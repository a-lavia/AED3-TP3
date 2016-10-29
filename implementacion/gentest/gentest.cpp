#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;


int min_val	= 0;
int max_val	= 100;


int dameRand();

int main(int argc, char* argv[]){

	/*								AYUDA DE ENTRADA
	 *	
	 *	./gentest tipoTest cantTestAleat cantGym cantParadas minRand maxRand mochila rangoPociones
	 *	
	 *	Si tipoTest == 0 entonces la entrada es: 
	 *	
	 *				./gentest 0 cantTestAleat cantGym cantParadas
	 *	
	 *	Y se generan tests con posiciones/pociones/mochila randomizados con un rango entre 0 y 100
	 *
	 *
	 *	Si tipoTest == 1 entonces la entrada es: 
	 *
	 *				./gentest 1 cantTestAleat cantGym cantParadas minRand maxRand mochila rangoPociones
	 *
	 *	Y se puede agregar también el rango de valores random, el valor de la mochila a mano, 
	 *	y el rango de valores de pociones [0;rangoPociones], para tener mayor control sobre el test.
	 *
	 *
	 *	Si tipoTest == 2 entonces la entrada es: 
	 *
	 *				./gentest 1 cantTestAleat cantGym cantParadas minRand maxRand mochila pocionesFija
	 *
	 *	Igual que el test anterior pero con la diferencia que las pociones tienen el valor fijo.
	 */


	int tipoTest = atoi(argv[1]);
	
	if(tipoTest != 0 && tipoTest != 1 && tipoTest != 2){
		cout << argv[1] << endl;
		cout << "Tipo de test no correcto leer ayuda en código." << endl;
		return 0;
	}

	int cantTestAleat = atoi(argv[2]);
	int cantGym = atoi(argv[3]);
	int cantParadas = atoi(argv[4]);
	int mochila = dameRand();
	int pociones;


	if(tipoTest != 0){
		min_val = atoi(argv[5]);
		max_val = atoi(argv[6]);
		mochila = atoi(argv[7]);
		pociones = atoi(argv[8]);
	}


	for(int i = 0; i < cantTestAleat; i++){
		ofstream test;
		test.open("test" + to_string(i) + ".txt");

		test << cantGym << " " << cantParadas << " " << mochila << endl;

		for(int g = 0; g < cantGym + cantParadas; g++){

			test << dameRand() << " " << dameRand();
			if(g < cantGym){
				if(tipoTest == 0){
					test << " " << dameRand() << endl;
				} else if(tipoTest == 1){
					test << " " << (dameRand()%(pociones+1)) << endl;
				} else {
					test << " " << pociones << endl;
				}

			} else {
				test << endl;
			}
		}

		test.close();
	}

	return 0;
}

int dameRand(){
	return rand()%(max_val + min_val + 1) + min_val;
}