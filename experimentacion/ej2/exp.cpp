#include "exp.h"


int main(int argc, char* argv[]){
	int cant_gym, cant_paradas, mochila;

    cin >> cant_gym;
	cin >> cant_paradas;
	cin >> mochila;

	vector<struct gym> gimnasios(cant_gym);
	vector<struct parada> paradas(cant_paradas);

	// Gimnasios
	for(int i = 0; i < cant_gym; i++){
		struct gym nuevo_gym;
		cin >> nuevo_gym.x;
		cin >> nuevo_gym.y;
		cin >> nuevo_gym.p;
		nuevo_gym.visitado = false;
		gimnasios[i] = nuevo_gym;
	}

	// Paradas
	for(int i = 0; i < cant_paradas; i++){
		struct parada nueva_parada;
		cin >> nueva_parada.x;
		cin >> nueva_parada.y;
		nueva_parada.visitado = false;
		paradas[i] = nueva_parada;
	}


	ofstream salida;
	salida.open("salida.csv", std::ios_base::app);
	double cantCiclosTotal = 0;
	double distancia_total = 0;

	// salida << "gimnasios,paradas,mochila,distancia,cantciclos" << endl;

	for(int i = 0; i < CANT_REPETICIONES;i++){
	
		auto inicio = RELOJ();
		solucion* mejor_sol = solHeuristicaGolosa(mochila, gimnasios, paradas);

		if(mejor_sol != NULL){
			
			imprimirSolucion(*mejor_sol);
			distancia_total = mejor_sol->d;
			delete mejor_sol;
		}
		auto fin = RELOJ();
	
		cantCiclosTotal += (double) chrono::duration_cast<std::chrono::nanoseconds>(fin-inicio).count();
	}

	salida << cant_gym << "," << cant_paradas << "," << mochila << "," << distancia_total << "," << cantCiclosTotal / (double) CANT_REPETICIONES << endl;
	salida.close();


	return 0;
}