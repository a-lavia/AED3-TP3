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

    bool visitado;
    int anterior;
    int siguiente;

    Nodo() : visitado(false), anterior(INV), siguiente(INV){

    }
};

enum Vecindad{
    vecindad1,  // Nombres provisorios
    vecindad2
};



float distancia(Nodo n1, Nodo n2);

int solucionInicial(vector<Nodo>& nodos, vector<vector<float>>& distancias, int tamMochila, float* distanciaTotal);

void busquedaLocal(vector<Nodo> nodos, vector<vector<float>>& distancias, float distanciaTotal, int cantGimnasios, int nodoInicial, Vecindad criterio);
bool encuentroSolucionVecinaMejor1(vector<Nodo>& nodos, float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial);
bool encuentroSolucionVecinaMejor2(vector<Nodo>& nodos, float distanciaTotal, vector<Nodo>& nodosSV, float* distanciaTotalSV, int* nodoInicial);

void imprimirSolucion(vector<Nodo>& nodos, int nodoInicial, float distanciaTotal, int cantGimnasios);