#ifndef FUNCIONES_EXP3_H
#define FUNCIONES_EXP3_H

#include "aux.h"
#include "../../implementacion/ej3/aux.h"
#include "../../implementacion/ej3/Grafo.h"
#include "../../implementacion/ej3/Camino.h"

int aleatEnRango(int min, int max);
int max(int a, int b);  
int min(int a, int b);

// Todos los caminos generados en estas funciones tienen una solucion hallable por medio de una heuristica golosa:
void generarCaminosAleat(vector<Camino>& caminos, bool paraCompOp);

void generarSalida(vector<Camino>& caminos, Vecindad criterio, ofstream& salida);

void expAleat(ofstream& salida, Vecindad criterio);
void expOpAleat(ofstream& salidad, Vecindad criterio);
void expMejor(ofstream& salida, Vecindad criterio);
void expOpMejor(ofstream& salida, Vecindad criterio);

#endif