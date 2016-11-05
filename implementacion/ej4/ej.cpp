
//float distanciaCamino(queue<int> camino, vector<pos>& posGym, vector<pos>& posParada);


list<pair<int, float>> obtenerCandidatos() {
	list<pair<int, float>> candidatos;

	//Agrego como candidatos iniciales todas las paradas y gimnasios que pueden derrotarse inicialmente
	for(int i = 0; i < nodos; i++) {
		if(!(esGimnasio(i) && gimnasiosPoder[i] == 0)) continue;
		candidatos.push_back(pair<int, float>(i, 0));
	}

	return candidatos;
}

vector<int> obtenerCandidatosRestringidos(list<pair<int, float>>& candidatos, float alfa) {
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
		if(candidato.second < threshold) candidatosRestringidos.insert(candidato.first);
	}

	return candidatosRestringidos;
}

void actualizarCandidatos(list<pair<int, float>>& candidatos, queue<int>& solucionParcial, int pociones) {

	//Actualizo todos los candidatos
	for(list<pair<int, float>>::iterator it = candidatos.begin(); it != candidatos.end(); it++) {

		pair<int, float>& candidato = *it;

		//Remuevo gimnasios a los que no puedo ganarle
		if(esGimnasio(candidato.first) && gimnasioPoder[candidato.first] > pociones) {
			it = candidatos.erase(it);
			it--;
			continue;
		}

		//Actualizo las distancias con respecto a la última posición
		candidato.second = distancia(candidato.first, solucionParcial.back());
		
	}

	//Me fijo que gimnasios visite en la solucion parcial
	bool gymVisitado[gimnasios.size()];
	for(int i = 0; i < gimnasios.size(); i++) gymVisitado[i] = false;

	queue<int> sol = solucionParcial;
	while(!sol.empty()) {
		int n = sol.front(); sol.pop();
		if(esGimnasio(n)) gymVisitado[n] = true;
	}

	//Agrego todos los nuevos gimnasios que puedo visitar
	for(int i = 0; i < gimnasios.size(); i++) {
		if(!gymVisitado[i] && gimnasioPoder[i] <= pociones) 
			candidato.push_back(pair<int, float>(i, distancia(i, solucionParcial.back()));
	}

}

queue<int> graspSolucionAleatoria(float alfa) {

	queue<int> solucionParcial;

	//Obtengo todos los candidatos iniciales
	list<pair<int, float>> candidatos = obtenerCandidatos();
	
	int pociones = 0;
	int gimnasiosRestantes = gimnasios.size();
	while(gimnasiosRestantes > 0) {

		//Restrinjo los candidatos a los mejores segun un threshold alfa (parte greedy)
		vector<int> candidatosRestringidos = obtenerCandidatosRestringidos(candidatos, alfa);

		//Obtengo un candidato aleatorio (parte probabilistica)
		int candidatoAleatorio = candidatosRestringidos[random(0, candidatosRestringidos.size())];

		if(esGimnasio(candidatoAleatorio)) {
			gimnasiosRestantes--;
			pociones -= 3;
		}
		else pociones = min(pociones+3, mochila);

		//Lo agrego a la solución a construir (parte adaptativa)
		solucionParcial.push(candidatoAleatorio);

		//Actualizo la lista de candidatos
		actualizarCandidatos(candidatos, solucionParcial, pociones);
	}

	return solucionParcial;
}

void grasp(int maxIteraciones, int semilla) {
	srand(semilla);
	queue<int> solucion;
	float dist;
	for(int i = 0; i < maxIteraciones; i++) {
		queue<int> solucion = graspSolucionAleatoria(0.5, 0);

		Camino bl = Camino(g, mochila);
        //void asignarDistancia(float distancia);
        //void asignarCamino(queue<int>& caminoCola);
		//bl.busquedaLocal(permutaCamino);
		//bl.obtenerSolucion()...
		//si es mejor solución que la actual reemplazar
	}
}

int main(int argc, char* argv[]) {

	int n;
	cin >> n;
	int m;
	cin >> m;
	int mochila;
	cin >> mochila;

	vector<pos> gimnasios(n);
	vector<int> gimnasiosPoder(n);
	vector<pos> paradas(m);

	for(int i = 0; i < n; i++) {
		cin >> gimnasios[i].first;
		cin >> gimnasios[i].second;
		cin >> gimnasiosPoder[i];
	}
	for(int i = 0; i < m; i++) {
		cin >> paradas[i].first;
		cin >> paradas[i].second;
	}

	//Armo el grafo para la búsqueda local
	Grafo g(n+m);

	for(int nodo = 0; i < n+m; i++) {
		bool esGym = i < n;
		Nodo nodoNuevo;
		nodoNuevo.id = nodo;
		nodoNuevo.x = esGym ? gimnasios[i].first : paradas[i].first;
		nodoNuevo.y = esGym ? gimnasios[i].second : paradas[i].second;
		nodoNuevo.pociones = esGym ? gimnasiosPoder[i] : 3;
		nodoNuevo.gimnasio = esGym;
		g.asignarNodo(nodoNuevo);
	}
    for(int i = 0; i < n+m; i++){
        for(int j = 0; j < n+m; j++){
            Nodo& n1 = g.nodos()[i];
            Nodo& n2 = g.nodos()[j];
            g.asignarDistancia(n1, n2, distanciaNodos(n1, n2));
        }
    }

}

