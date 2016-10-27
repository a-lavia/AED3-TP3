#include <iostream>
#include <vector>
#include <math.h>
#include <stack>
#include <map>

#define INV -1

using namespace std;

struct Nodo{
    int x;
    int y;
    int pociones;   
    bool gimnasio;

    int siguiente;

    Nodo() : siguiente(INV) {}
};

float distancia(Nodo n1, Nodo n2);

int solucionInicial(vector<Nodo>& nodos, vector<vector<float>>& distancias, float* distanciaTotal);

void busquedaLocal1(vector<Nodo> nodos, vector<vector<float>>& distancias, float distanciaTotal, int cantGimnasios, int nodoInicial);
bool encuentroSolucionVecinaMejor1(vector<Nodo>& nodos, float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial);

void busquedaLocal2(vector<Nodo> nodos, vector<vector<float>>& distancias, float distanciaTotal, int cantGimnasios, int nodoInicial);
bool encuentroSolucionVecinaMejor2(vector<Nodo>& nodos, float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial);

void imprimirSalida(vector<Nodo>& nodos, int nodoInicial, float distanciaTotal, int cantGimnasios);