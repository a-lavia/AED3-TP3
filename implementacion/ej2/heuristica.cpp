#include "heuristica.h"

float distancia(pos& a, pos& b){
    float x = a.first - b.first;
    float y = a.second - b.second;
    return sqrt((x*x) + (y*y));
}

float distanciaCamino(queue<int> camino, vector<pos>& posGym, vector<pos>& posParada) {
	float dist = 0;
	while(camino.size() > 1) {

		int nodoA = camino.front();
		camino.pop();

		int nodoB = camino.front();

		bool esGymA = nodoA < posGym.size();
		bool esGymB = nodoB < posGym.size();

		pos& posA = esGymA ? posGym[nodoA] : posParada[nodoA-posGym.size()];
		pos& posB = esGymB ? posGym[nodoB] : posParada[nodoB-posGym.size()];

		dist += distancia(posA, posB);
	}
	return dist;
}

queue<int> heuristicaVecinoCercano(vector<pos>& posiciones, list<int>& nodos) {

	float mejorDist = FLOAT_MAX;
	queue<int> mejorCamino;

	for(int inicial : nodos) {

		list<int> restantes = nodos;
		restantes.remove(inicial);


		float totalDist = 0;
		queue<int> camino;

		int actual = inicial;
		camino.push(actual);

		while(restantes.size() > 0) {

			float minDist = FLOAT_MAX;
			int mejorNodo = -1;
			for(int i : restantes) {
				float dist = distancia(posiciones[actual], posiciones[i]);
				if(dist < minDist) {
					minDist = dist;
					mejorNodo = i;
				}
			}
			totalDist+=minDist;
			camino.push(mejorNodo);
			restantes.remove(mejorNodo);
			actual = mejorNodo;

		}

		if(totalDist < mejorDist) {
			mejorDist = totalDist;
			mejorCamino = camino;
		}

	}

	return mejorCamino;
}

queue<int> heuristicaParadasCercanas(queue<int>& caminoGimnasios, vector<pos>& posGimnasios, vector<int>& gimnasiosPoder, vector<pos>& posParadas, list<int>& paradas, int mochila) {

	queue<int> camino;

	int pociones = 0;

	while(!caminoGimnasios.empty()) {

		int gym = caminoGimnasios.front();
		caminoGimnasios.pop();

		while(pociones < gimnasiosPoder[gym]) {

			float minDist = FLOAT_MAX;
			int mejorParada = -1;

			for(int i : paradas) {
				float dist = distancia(posGimnasios[gym], posParadas[i]);
				if(dist < minDist) {
					minDist = dist;
					mejorParada = i;
				}
			}

			if(mejorParada == -1) return queue<int>(); //

			paradas.remove(mejorParada);
			camino.push(mejorParada+posGimnasios.size());
			pociones = min(pociones+3, mochila);
		}

		pociones -= gimnasiosPoder[gym];
		camino.push(gym);

	}

	return camino;
}

queue<int> solucionHeuristica(vector<pos>& gimnasios, vector<int>& gimnasiosPoder, vector<pos>& paradas, int mochila) {

	//Armo un camino de gimnasios
	list<int> gymAVisitar;
	for(int i = 0; i < gimnasios.size() ; i++)
		gymAVisitar.push_back(i);

	queue<int> caminoGimnasios = heuristicaVecinoCercano(gimnasios, gymAVisitar);

	//Visito las paradas mas cercanas del camino de gimnasios
	list<int> paradasAVisitar;
	for(int i = 0; i < paradas.size() ; i++)
		paradasAVisitar.push_back(i);

	return heuristicaParadasCercanas(caminoGimnasios, gimnasios, gimnasiosPoder, paradas, paradasAVisitar, mochila);

}

void imprimirSolucion(queue<int>& camino, vector<pos>& posGym, vector<pos>& posParadas){
	imprimirSolucionAOstream(cout, camino, posGym, posParadas);
}

void imprimirSolucionAOstream(ostream& sol, queue<int>& camino, vector<pos>& posGym, vector<pos>& posParadas){
	float d = distanciaCamino(camino, posGym, posParadas);

	// si la distancia es 0 y no hay gimnasios gane.
	if(d == 0 && posGym.size() == 0){
		sol << "0 0" << endl;
		return;
	}

	if(camino.size() != 0){
		sol << d << " " << camino.size() << " ";
		while(!camino.empty()){
			sol << (camino.front()+1) << " ";
			camino.pop();
		}
	} else {
		sol << -1;
	}
	sol << endl;

	return;
}