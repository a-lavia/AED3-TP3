#include "funciones.h"

int main(int argc, char* argv[]){
	int cant_gym;
	int cant_paradas;
	int mochila;

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

	// Genero Matriz de distancias
	int fila = cant_paradas + cant_gym;
	vector<vector<float>> matriz_dist(fila, vector<float>(fila) );

	for(int i = 0; i < fila; i++)
		matriz_dist[i] = vector<float>(fila);

	for(int i = 0; i < fila; i++){
		for(int j = 0; j < fila; j++){
			// Primero los gym y luego las paradas
			if(i == j){
				matriz_dist[i][j] = 0.0;
			 } else if(i < cant_gym && j < cant_gym){
				matriz_dist[i][j] = distancia(gimnasios[i], gimnasios[j]);
			} else if(i >= cant_gym && j < cant_gym){
				matriz_dist[i][j] = distancia(paradas[cant_gym-i+1], gimnasios[j]);
			} else if(i < cant_gym && j >= cant_gym){
				matriz_dist[i][j] = distancia(gimnasios[i], paradas[cant_gym-j+1]);
			} else if(i >= cant_gym && j >= cant_gym){
				matriz_dist[i][j] = distancia(paradas[cant_gym-i+1], paradas[cant_gym-j+1]);
			}
		}
	}

	// Imprimo la matriz_dist
	// imprimirMatriz(matriz_dist);

	solucionGolosa(mochila, gimnasios, paradas, matriz_dist);

	return 0;
}

