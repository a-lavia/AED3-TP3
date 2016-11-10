#include "funciones.h"


solucion* solHeuristicaGolosa(unsigned int mochilaSize, vector<struct gym>& gimnasios, 
	                          vector<struct parada>& paradas)
{
	int cantGym = gimnasios.size();
	int cantParadas = paradas.size();

	// Genero Matriz de distancias
	int fila = cantParadas + cantGym;
	vector<vector<float>> matrizDistancias(fila, vector<float>(fila) );

	for(int i = 0; i < fila; i++){
		matrizDistancias[i] = vector<float>(fila);
	}

	for(int i = 0; i < fila; i++){
		for(int j = 0; j < fila; j++){
			// Primero los gym y luego las paradas
			if(i == j){
				matrizDistancias[i][j] = 0.0;
			 } else if(i < cantGym && j < cantGym){
				matrizDistancias[i][j] = distancia2(gimnasios[i], gimnasios[j]);
			} else if(i >= cantGym && j < cantGym){
				matrizDistancias[i][j] = distancia2(paradas[i-cantGym], gimnasios[j]);
			} else if(i < cantGym && j >= cantGym){
				matrizDistancias[i][j] = distancia2(gimnasios[i], paradas[j-cantGym]);
			} else if(i >= cantGym && j >= cantGym){
				matrizDistancias[i][j] = distancia2(paradas[i-cantGym], paradas[j-cantGym]);
			}
		}
	}


	// Imprimo la matrizDistancias
	// imprimirMatriz(matrizDistancias);


	solucion* mejorSolucion = new solucion;
	mejorSolucion->d = -1;

	// CASOS EN DONDE PUEDO SABER UNA SOLUCIÓN SIN CORRER LA HEURISTICA
	// Caso: No hay gimnasios => Gane
	if(gimnasios.size() == 0){
		mejorSolucion->d = 0;
		return mejorSolucion;
	}

	int sumaTotalPociones = 0;
	for(vector<gym>::iterator it = gimnasios.begin(); it != gimnasios.end(); it++){
		sumaTotalPociones += (*it).p;
	}

	// Caso: Si la cantidad de paradas*3 < suma total de pociones para ganarle a todos los gimasios => -1
	// Caso: (No hay pokeparadas o mochilaSize == 0) y al menos un gimnasio tiene p > 0 => -1
	if((sumaTotalPociones > paradas.size()*3) || 
	   ((paradas.size() == 0 || mochilaSize == 0) && sumaTotalPociones > 0))
	{
		return mejorSolucion;
	}

	// Caso patologico: sumaTotalPociones=0, genero un camino por un gimnasio
	if(sumaTotalPociones == 0){
		struct solucion solucionNueva;
		solucionNueva.d = 0;
		correrHeuristica(0, solucionNueva, mochilaSize, gimnasios, paradas, matrizDistancias);
		if((mejorSolucion->d == -1 && solucionNueva.d != -1) || 
			(solucionNueva.d != -1 && solucionNueva.d < mejorSolucion->d))
		{
			*mejorSolucion = solucionNueva;
		}
	}

	// Busco la mejor solución comenzando por cada parada
	for(int i = gimnasios.size(); i < paradas.size() + gimnasios.size(); i++){
		struct solucion solucionNueva;
		solucionNueva.d = 0;
		correrHeuristica(i, solucionNueva, mochilaSize, gimnasios, paradas, matrizDistancias);

		if((mejorSolucion->d == -1 && solucionNueva.d != -1) || 
			(solucionNueva.d != -1 && solucionNueva.d < mejorSolucion->d))
		{
			*mejorSolucion = solucionNueva;
		}
	}

	return mejorSolucion;
}

/************************************************************************/

void correrHeuristica(int idxComienzo, struct solucion& sol, unsigned int mochilaSize, vector<struct gym> gimnasios, 
						 vector<struct parada> paradas, vector<vector<float>>& matrizDistancias){

	// Si puedo ganarle a algún gym, voy al de menor distancia y le gano
	// Si no hay mas pokeparadas y si gyms -> -1
	// Si hay pokeparadas y no gyms -> gane
	
	int gymNoRecorridos = gimnasios.size();
	int paradasNoRecorridas = paradas.size();
	int mochila;

	// Comienzo dependiendo de idxComienzo
	int idxActual = idxComienzo;
	sol.camino.push(idxActual);
	
	// idxComienzo es indice de paradas + gimnasios.size, entonces para conocer el indice real lo tengo que restar
	if(idxComienzo != 0 ){
		paradas[idxComienzo - gimnasios.size()].visitado = true;
		mochila = 3;
		paradasNoRecorridas--;
	} else {
		//Caso patologico: sumaTotalPociones=0, genero un camino por un gimnasio
		gimnasios[idxComienzo].visitado = true;
		mochila = 0;
		gymNoRecorridos--;
	}

	while(gymNoRecorridos > 0){

		if(leGanoAAlgunGym(mochila, gimnasios)){

			leGanoAlGymMasCercano(mochila, idxActual, sol, gimnasios, matrizDistancias);
			gymNoRecorridos--;

		} else if(mochila == mochilaSize || paradasNoRecorridas == 0){
			// No le gano a ningún gym y la mochila está llena => -1
			// No le gana a ningún gym y no hay mas paradas
			break;

		} else {
			voyParadaMasCercana(mochila, idxActual, mochilaSize, gimnasios.size(), sol, paradas, matrizDistancias);
			paradasNoRecorridas--;
		}
	}

	// Si no recorrio todos los gimnasios entonces no hay solucion
	if(gymNoRecorridos > 0){
		sol.d = -1;
	}

	return;
}

/************************************************************************/

bool leGanoAAlgunGym(int mochila, vector<struct gym>& gimnasios){
	bool le_gano = false;
	for(int i = 0; i < gimnasios.size(); i++){
		if(!gimnasios[i].visitado && mochila >= gimnasios[i].p){ // No fue visitado y las pociones de la mochila son las necesarias
			le_gano = true;
			break;
		}
	}
	return le_gano;
}

/************************************************************************/

void leGanoAlGymMasCercano(int& mochila, int& idxActual, struct solucion& sol, 
						  vector<struct gym>& gimnasios, vector<vector<float>>& matrizDistancias)
{
	// Busco al gym que le gano con menor cant de pociones
	int idx_gym = -1;
	int dist;
	for(int i = 0; i < gimnasios.size(); i++){
		if(idx_gym == -1){
			if(!gimnasios[i].visitado && mochila >= gimnasios[i].p){
				idx_gym = i;
				dist = matrizDistancias[idxActual][i];
			}

		} else {
			if(!gimnasios[i].visitado && 
				mochila >= gimnasios[i].p && 
				matrizDistancias[idxActual][i] < dist)
			{
				idx_gym = i;
				dist = matrizDistancias[idxActual][i];
			}
		}
	}

	mochila -= gimnasios[idx_gym].p;
	sol.d += sqrt(matrizDistancias[idxActual][idx_gym]);
	sol.camino.push(idx_gym);
	gimnasios[idx_gym].visitado = true;
	idxActual = idx_gym;

	return;
}

/************************************************************************/

void voyParadaMasCercana(int& mochila, int& idxActual, int mochilaSize, int cantGym, struct solucion& sol, vector<struct parada>& paradas, vector<vector<float>>& matrizDistancias){
	// Busco parada mas cercana
	int cantParadas = paradas.size();
	int idx_parada = -1;

	for(int i = 0; i < cantParadas; i++){
		if(idx_parada == -1){
			if(!paradas[i].visitado)
				idx_parada = i;
		
		} else {
			if(idxActual == i+cantParadas)
				continue;

			if(!paradas[i].visitado && matrizDistancias[idxActual][i+cantGym] < matrizDistancias[idxActual][idx_parada+cantGym])
				idx_parada = i;
		}
	}

	mochila = (mochila+3) > mochilaSize ? mochilaSize : (mochila+3);
	sol.d += sqrt(matrizDistancias[idxActual][idx_parada+cantGym]);
	paradas[idx_parada].visitado = true;
	idxActual = idx_parada + cantGym;
	sol.camino.push(idxActual);

	return;
}

/************************************************************************/

void imprimirSolucion(struct solucion& sol){
	// Imprimo soluciones
	cout << sol.d;
	if(sol.d == -1){
        cout << endl;
		return;
    }

	cout << " " << sol.camino.size();
	imprimirCola(sol.camino);
	cout << endl;

	return;
}

/************************************************************************/

void imprimirCola(queue<int>& cola){
	// b == true => paradas  || b == false => gimnasios
	int nodo;
	int size = cola.size();
	for(int i = 0; i < size; i++){
		nodo = cola.front();
		cola.pop();
		cout << " " << nodo + 1;
	}
	return;
}

/************************************************************************/

void imprimirMatriz(vector<vector<float>>& matrizDistancias){
	cout << endl << "Matriz" << endl;
	for(int i = 0; i < matrizDistancias.size(); i++){
		for(int j = 0; j < matrizDistancias.size(); j++){
			cout << "(" << matrizDistancias[i][j] << ")";

		}
		cout << endl;
	}
	cout << endl;
	return;
}

/************************************************************************/

void imprimirVector(vector<struct gym>& gimnasios){
	cout << endl << "Gimnasios" << endl;
	for(int i = 0; i < gimnasios.size(); i++){
		cout << gimnasios[i].x << " " << gimnasios[i].y << " " << gimnasios[i].p << " " << gimnasios[i].visitado << endl;
	}
	return;
}

/************************************************************************/

void imprimirVector(vector<struct parada>& paradas){
	cout << endl << "Paradas" << endl;
	for(int i = 0; i < paradas.size(); i++){
		cout << paradas[i].x << " " << paradas[i].y << " " << paradas[i].visitado << endl;
	}
	return;
}

/************************************************************************/

float distancia2(const nodo &n1, const nodo &n2){
	float x = n2.x - n1.x;
	float y = n2.y - n1.y;

	return (x*x + y*y);
}
