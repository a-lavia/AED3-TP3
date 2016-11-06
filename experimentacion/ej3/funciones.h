#ifndef FUNCIONES_EXP3_H
#define FUNCIONES_EXP3_H

#include "aux.h"
#include "../../implementacion/ej3/aux.h"
#include "../../implementacion/ej3/Grafo.h"
#include "../../implementacion/ej3/Camino.h"
#include "../../implementacion/ej1bis/backtracking.h"

// Todos los grafos generados tienen solucion:
void generarCaminosAleat(vector<Camino>& caminos);
void generarCaminosAleatOp(vector<Camino>& caminos);
Grafo generarGrafoAleat(int cantGimnasios);
Grafo generarGrafoAleatOp(int cantGimnasios, int cantPokeparadas);

void asignarSolucionesJ(vector<Camino>& caminos);

void generarSalidaBL(vector<Camino>& caminos, Vecindad criterio, ofstream& salida);
void generarSalidaOp(vector<Camino>& caminos, ofstream& salida);

int aleatEnRango(int min, int max);
int max(int a, int b);  
int min(int a, int b);

#endif