#include "backtracking.h"

backtracking::backtracking(vector<pos>& gimnasios, vector<int>& gimnasiosPoder, vector<pos>& paradas, int mochila) : gimnasios(gimnasios), gimnasiosPoder(gimnasiosPoder), paradas(paradas), mochila(mochila), mejorRecorrido(), mejorDistancia(FLOAT_MAX) {

	//Agrego todos los gimnasios y paradas a un vector de posiciones
    posiciones.insert(posiciones.end(), gimnasios.begin(), gimnasios.end());
    posiciones.insert(posiciones.end(), paradas.begin(), paradas.end());

}

float backtracking::correr_backtracking() {

	//Obtengo algun recorrido de una solución heuristica
	mejorRecorrido = solucionHeuristica(gimnasios, gimnasiosPoder, paradas, mochila);
	mejorDistancia = mejorRecorrido.size() != 0 ? distanciaCamino(mejorRecorrido, gimnasios, paradas) : mejorDistancia = FLOAT_MAX;

	//Preparamos los parametros del backtracking, agrego todos los nodos por verificar a una cola
	queue<int> restantes;
	for(int i = 0; i < posiciones.size() ; i++)
		restantes.push(i);

	 //Inicialmente no recorri nada
	queue<int> recorridos;

	//Corremos el backtracking
	btRecursivo(0, 0, gimnasiosPoder.size(), restantes, recorridos);

	return mejorDistancia;

}

float backtracking::correr_backtracking(queue<int>* solucion) {

	//
	correr_backtracking();

	//Guardamos la solucion en el parametro recibido
	if(solucion != NULL)
		*solucion = mejorRecorrido;

	return mejorDistancia;

}

void backtracking::btRecursivo(float distanciaActual, int pociones, int gimnasiosPorVisitar, queue<int>& restantes, queue<int>& recorridos) {
	if(gimnasiosPorVisitar == 0) {
		if(distanciaActual < mejorDistancia) { //Ajustamos la mejor distancia encontrada y el camino recorrido
			mejorDistancia = distanciaActual;
			mejorRecorrido = recorridos;
		}
	} else if(distanciaActual < mejorDistancia) {
		int ultimo = restantes.back();
		int visitar;
		
		do {
			visitar = restantes.front();
			restantes.pop();

			float dist = recorridos.size() == 0 ? 0 : distancia(posiciones[recorridos.back()], posiciones[visitar]);

			queue<int> restantesCopia = restantes;
			queue<int> recorridosCopia = recorridos;
			recorridosCopia.push(visitar);

			//Si es un gimnasio
			if(esGimnasio(visitar) && (pociones >= gimnasiosPoder[visitar]) )
				btRecursivo(distanciaActual+dist, pociones-gimnasiosPoder[visitar], gimnasiosPorVisitar-1, restantesCopia, recorridosCopia);
			//Es una pokeparada
			else if(!esGimnasio(visitar))
				btRecursivo(distanciaActual+dist, min(pociones+3, mochila), gimnasiosPorVisitar, restantesCopia, recorridosCopia);

			restantes.push(visitar); //Lo volvemos a agregar (al final) para la siguiente iteración	
	
		} while (visitar != ultimo);

	}
}

bool backtracking::esGimnasio(int id) {
	return id < gimnasiosPoder.size();
}
