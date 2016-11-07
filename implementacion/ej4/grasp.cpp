#include "grasp.h"

//Recibe un vector con las posiciones de los gimnasios, un vector con el poder de los gimnasios, y otro vector con la posicion de las paradas
grasp::grasp(vector<pos>& g, vector<int>& gp, vector<pos>& p, int m) : gimnasios(g), gimnasiosPoder(gp), paradas(p), mochila(m), grafo(g.size()+p.size()) {

	//Armo el grafo para la búsqueda local
	for(int nodo = 0; nodo < grafo.nodos().size(); nodo++) {
		Nodo nodoNuevo;
		nodoNuevo.id = nodo + 1;
		nodoNuevo.x = esGym(nodo) ? gimnasios[nodo].first : paradas[nodo-gimnasios.size()].first;
		nodoNuevo.y = esGym(nodo) ? gimnasios[nodo].second : paradas[nodo-gimnasios.size()].second;
		nodoNuevo.pociones = esGym(nodo) ? gimnasiosPoder[nodo] : 3;
		nodoNuevo.gimnasio = esGym(nodo);
		grafo.asignarNodo(nodoNuevo);
	}

}

float grasp::correr_grasp(int maxIteraciones, float alfa, int semilla) {
	correr_grasp(maxIteraciones, alfa, semilla, NULL);
}

float grasp::correr_grasp(int maxIteraciones, float alfa, int semilla, queue<int>* solucion) {

	srand(semilla);

	queue<int> mejorSolucion;
	float mejorDistancia = FLOAT_MAX;

	for(int i = 0; i < maxIteraciones; i++) {

		queue<int> solucionAleatoria = graspSolucionAleatoria(alfa);
		Camino bl = Camino(grafo, mochila);
		bl.asignarSolucion(distanciaCamino(solucionAleatoria), solucionAleatoria);
		bl.busquedaLocal(permutaCamino);
		float distActual = bl.devolverSolucion(solucionAleatoria);

		if(distActual < mejorDistancia) {
			mejorDistancia = distActual;
			mejorSolucion = solucionAleatoria;
		}
	}

	if(solucion != NULL)
		*solucion = mejorSolucion;

	return mejorDistancia;
}

//

int grasp::aleatorio(int min, int max) {
	return rand() % (max-min) + min;
}

bool grasp::esGym(int i) {
	return i < gimnasios.size();
}

float grasp::distancia(int a, int b) {

	pos& posA = esGym(a) ? gimnasios[a] : paradas[a-gimnasios.size()];
	pos& posB = esGym(b) ? gimnasios[b] : paradas[b-gimnasios.size()];

    float x = posA.first - posB.first;
    float y = posA.second - posB.second;

    return sqrt((x*x) + (y*y));
}

float grasp::distanciaCamino(queue<int> camino) {
	float dist = 0;
	while(camino.size() > 1) {

		int nodoA = camino.front();
		camino.pop();

		int nodoB = camino.front();

		dist += distancia(nodoA, nodoB);
	}
	return dist;
}

list<pair<int, float>> grasp::obtenerCandidatos() {
	list<pair<int, float>> candidatos;

	//Agrego como candidatos iniciales todas las paradas y gimnasios que pueden derrotarse inicialmente
	for(int i = 0; i < gimnasios.size()+paradas.size(); i++) {
		if(esGym(i) && gimnasiosPoder[i] != 0) continue;
		candidatos.push_back(pair<int, float>(i, 0));
	}
	return candidatos;
}

void grasp::actualizarCandidatos(list<pair<int, float>>& candidatos, vector<bool>& visitados, int actual, int pociones) {

	candidatos.clear();
	for(int i = 0; i < gimnasios.size()+paradas.size(); i++) {
		//Ignoro nodos visitados, gimnasios que no se les puede ganar, pokeparadas teniendo la mochila llena
		if(visitados[i] || (esGym(i) && gimnasiosPoder[i] > pociones) || (!esGym(i) && pociones == mochila)) continue;
		candidatos.push_back(pair<int, float>(i, distancia(actual, i)));
	}

}

vector<int> grasp::obtenerCandidatosRestringidos(list<pair<int, float>>& candidatos, float alfa) {
	//alfa  [0..1], 0=greedy, 1=random
	vector<int> candidatosRestringidos;

	//Obtengo la maxima y minima distancia
	float cMax = candidatos.front().second;
	float cMin = candidatos.front().second;
	for(pair<int, float>& candidato : candidatos) {
		if(candidato.second > cMax) cMax = candidato.second;
		if(candidato.second < cMin) cMin = candidato.second;
	}

	//Agrego los candidatos que cumplen con el threshold
	float threshold = cMin + alfa * (cMax - cMin);
	for(pair<int, float>& candidato : candidatos) {
		if(candidato.second <= threshold) candidatosRestringidos.insert(candidatosRestringidos.end(), candidato.first);
	}

	return candidatosRestringidos;
}

queue<int> grasp::graspSolucionAleatoria(float alfa) {

	queue<int> solucionParcial;

	//Obtengo todos los candidatos iniciales
	list<pair<int, float>> candidatos = obtenerCandidatos();

	//Inicialmente arranco con cero pociones	
	int pociones = 0;
	
	//Faltan visitar todos los gimnasios
	int gimnasiosRestantes = gimnasios.size();

	//Inicialmente no visite nada
	vector<bool> visitados(gimnasios.size()+paradas.size());
	for(int i = 0; i < gimnasios.size()+paradas.size(); i++) visitados[i] = false;

	while(gimnasiosRestantes > 0) {

		//Restrinjo los candidatos a los mejores segun un threshold alfa (parte greedy)
		vector<int> candidatosRestringidos = obtenerCandidatosRestringidos(candidatos, alfa);

		//Obtengo un candidato aleatorio (parte probabilistica)
		int candidatoAleatorio = candidatosRestringidos[aleatorio(0, candidatosRestringidos.size() )];

		if(esGym(candidatoAleatorio)) {
			gimnasiosRestantes--;
			pociones -= gimnasiosPoder[candidatoAleatorio];
		}
		else pociones = min(pociones+3, mochila);

		//Lo marco como visitado
		visitados[candidatoAleatorio] = true;

		//Lo agrego a la solución a construir (parte adaptativa)
		solucionParcial.push(candidatoAleatorio);

		//Actualizo la lista de candidatos
		actualizarCandidatos(candidatos, visitados, candidatoAleatorio, pociones);
	}

	return solucionParcial;
}
