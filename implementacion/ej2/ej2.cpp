#include "funciones.h"

vector<solucion> soluciones;

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

	// cout << endl << "Mochila: " << mochila << endl;
	// Imprimir vectores por pantalla
	// imprimirVector(gimnasios);
	// imprimirVector(paradas);

	solucion* mejor_sol = solHeuristicaGolosa(mochila, gimnasios, paradas);
    
    if(mejor_sol != NULL){
        imprimirSolucion(*mejor_sol);
        delete mejor_sol;
    }

	return 0;
}