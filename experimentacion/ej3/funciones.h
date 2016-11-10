#ifndef FUNCIONES_EXP3_H
#define FUNCIONES_EXP3_H

#include "aux.h"
#include "../../implementacion/ej3/aux.h"
#include "../../implementacion/ej3/Grafo.h"
#include "../../implementacion/ej3/Camino.h"
#include "../../implementacion/ej1/backtracking.h"

void generarCaminosAleat(vector<Camino>& caminos);
void generarCaminosAleatOp(vector<Camino>& caminos);
void generarCaminosMejor(vector<Camino>& caminos);
void generarCaminosMejorOp(vector<Camino>& caminos);
void generarCaminosCantGimFija(vector<Camino>& caminos);
void generarCaminosCantPokFija(vector<Camino>& caminos);

void asignarSoluciones(vector<Camino>& caminos);

void generarSalidaBL(vector<Camino>& caminos, Vecindad criterio, ofstream& salida);
void generarSalidaOp(vector<Camino>& caminos, ofstream& salida);


// Todos los grafos generados tienen solucion:
void generarGrafoAleat(int cantGimnasios, Grafo& grafo);
void generarGrafoAleatFijo(int cantGimnasios, int cantPokeparadas, Grafo& grafo);
int generarGrafoMejor(int cantGimnasios, Grafo& grafo);
int generarGrafoMejorFijo(int cantGimnasios, int cantPokeparadas, Grafo& grafo);

int aleatEnRango(int min, int max);
int max(int a, int b);  
int min(int a, int b);

#endif