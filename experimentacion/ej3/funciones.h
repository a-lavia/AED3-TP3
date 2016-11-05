#ifndef FUNCIONES_EXP3_H
#define FUNCIONES_EXP3_H

#include "aux.h"
#include "../../implementacion/ej3/aux.h"
#include "../../implementacion/ej3/Grafo.h"
#include "../../implementacion/ej3/Camino.h"

int aleatEnRango(int min, int max);
int max(int a, int b);  
int min(int a, int b);

void generarGrafosAleat(vector<Grafo>& grafos);
void generarGrafosOpAleat(vector<Grafo>& grafos);
void generarGrafosMejor(vector<Grafo>& grafos);
void generarGrafosOpMejor(vector<Grafo>& grafos);

void generarCaminos(vector<Grafo>& grafos, vector<int>& tamMochilas, vector<Camino>& caminos);

void generarSalida(vector<Camino>& caminos, Vecindad criterio, ofstream& salida);

void expAleat(ofstream& salida, Vecindad criterio);
void expOpAleat(ofstream& salidad, Vecindad criterio);
void expMejor(ofstream& salida, Vecindad criterio);
void expOpMejor(ofstream& salida, Vecindad criterio);

#endif