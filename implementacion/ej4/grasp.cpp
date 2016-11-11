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

float grasp::correr_grasp(int maxIteraciones, float alfa, float omega, int semilla) {
	correr_grasp(maxIteraciones, alfa, omega, semilla, NULL);
}

float grasp::correr_grasp(int maxIteraciones, float alfa, float omega, int semilla, queue<int>* solucion) {


	//Vecinidad para la búsqueda local
	//permutaCamino,
    //permutaYReemplazaPokeparadas
	Vecindad vecindad = permutaCamino;
	
	//Criterio de parada
	bool continuarCuandoMejora = true;

	//
	srand(semilla);

	queue<int> mejorSolucion;
	float mejorDistancia = FLOAT_MAX;

	for(int i = 0; i < maxIteraciones; i++) {
		cout << "it " << i << endl;
		queue<int> solucionGimnasios = graspSolucionGimnasios(alfa);
		queue<int> solucionAleatoria = graspSolucionAleatoria(solucionGimnasios, alfa, omega);
		//float distActual = distanciaCamino(solucionAleatoria);

		Camino bl = Camino(grafo, mochila);
		bl.asignarSolucion(distanciaCamino(solucionAleatoria), solucionAleatoria);
		bl.busquedaLocal(vecindad);
		float distActual = bl.devolverSolucion(solucionAleatoria);

		if(distActual < mejorDistancia) {
			mejorDistancia = distActual;
			mejorSolucion = solucionAleatoria;
			if(continuarCuandoMejora) i = 0;
		}
	}

	if(solucion != NULL)
		*solucion = mejorSolucion;

	return mejorDistancia;
}

//

int grasp::int_aleatorio(int min, int max) {
	return rand() % (max-min) + min;
}

bool grasp::bool_aleatorio(float prob) {
    return rand() < prob * (RAND_MAX+1.0);
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

//

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

queue<int> grasp::graspSolucionGimnasios(float alfa) {

	queue<int> solucionGimnasios;
	
	//Faltan visitar todos los gimnasios
	int gimnasiosRestantes = gimnasios.size();

	//Inicialmente no visite nada
	vector<bool> visitados(gimnasios.size());
	for(int i = 0; i < gimnasios.size(); i++) visitados[i] = false;

	while(gimnasiosRestantes > 0) {

		//Pongo todos los gimnasios como candidatos iniciales 
		list<pair<int, float>> candidatos;
		for(int i = 0; i < gimnasios.size(); i++) {
			if(visitados[i]) continue;
			float costo = solucionGimnasios.empty() ? 0 : distancia(i, solucionGimnasios.back());
			candidatos.push_back(pair<int, float>(i, costo));
		}

		//Restrinjo los candidatos a los mejores segun un threshold alfa (parte greedy)
		vector<int> candidatosRestringidos = obtenerCandidatosRestringidos(candidatos, alfa);

		//Obtengo un candidato aleatorio (parte probabilistica)
		int candidatoAleatorio = candidatosRestringidos[int_aleatorio(0, candidatosRestringidos.size() )];

		//Lo marco como visitado
		visitados[candidatoAleatorio] = true;

		//Lo agrego a la solución a construir (parte adaptativa)
		solucionGimnasios.push(candidatoAleatorio);

		//
		gimnasiosRestantes--;

	}

	return solucionGimnasios;
}

queue<int> grasp::graspSolucionAleatoria(queue<int>& caminoGimnasios, float alfa, float omega) {

	queue<int> solucionAleatoria;

	//
	int paradasRestantes = paradas.size();

	//Inicialmente arranco con cero pociones	
	int pociones = 0;
	
	//Inicialmente no visite nada
	vector<bool> visitados(gimnasios.size()+paradas.size());
	for(int i = 0; i < gimnasios.size()+paradas.size(); i++) visitados[i] = false;

	while(!caminoGimnasios.empty()) {

		//Visito paradas
		while(paradasRestantes > 0 && (pociones < gimnasiosPoder[caminoGimnasios.front()] || (pociones < mochila && bool_aleatorio(omega)))) {

			//Lista de candidatos
			list<pair<int, float>> candidatos;
			for(int i = gimnasios.size(); i < gimnasios.size()+paradas.size(); i++) {
				if(visitados[i]) continue;
				candidatos.push_back(pair<int, float>(i, distancia(i, caminoGimnasios.front())));
			}

			//Restrinjo los candidatos a los mejores segun un threshold alfa (parte greedy)
			vector<int> candidatosRestringidos = obtenerCandidatosRestringidos(candidatos, alfa);

			//Obtengo un candidato aleatorio (parte probabilistica)
			int candidatoAleatorio = candidatosRestringidos[int_aleatorio(0, candidatosRestringidos.size() )];

			//Sumo pociones
			pociones = min(pociones+3, mochila);

			//Lo marco como visitado
			visitados[candidatoAleatorio] = true;

			//Lo agrego a la solución a construir (parte adaptativa)
			solucionAleatoria.push(candidatoAleatorio);

			//
			paradasRestantes--;
		}

		//Resto las pociones del gimnasio
		pociones -= gimnasiosPoder[caminoGimnasios.front()];

		//
		if(pociones < 0) cout << "ERRORRR" << endl;

		//Lo marco como visitado
		visitados[caminoGimnasios.front()] = true;

		//Lo agrego a la solución
		solucionAleatoria.push(caminoGimnasios.front());
		
		//Lo saco
		caminoGimnasios.pop();

	}

	return solucionAleatoria;
}
