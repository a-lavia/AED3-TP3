#ifndef FUNCIONES_EXP3_H
#define FUNCIONES_EXP3_H

#include "aux.h"
#include "../../implementacion/ej3/aux.h"
#include "../../implementacion/ej3/Grafo.h"
#include "../../implementacion/ej3/Camino.h"

void expAleat(ofstream& salida, Vecindad criterio);
void expAleatOp(ofstream& salida, ofstream& salidaOp, Vecindad criterio);
void expMejor(ofstream& salida, Vecindad criterio);
void expMejorOp(ofstream& salida, Vecindad criterio);

void generarCaminosAleat(vector<Camino>& caminos);
void generarCaminosAleatOp(vector<Camino>& caminos);
Grafo generarGrafoAleat(int cantGimnasios);

void generarSalida(vector<Camino>& caminos, Vecindad criterio, ofstream& salida);
void generarSalidaOp(vector<Camino>& caminos, Vecindad criterio, ofstream& salidaOp);

int aleatEnRango(int min, int max);
int max(int a, int b);  
int min(int a, int b);

#endif