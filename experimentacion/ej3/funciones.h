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

void generarCaminos(vector<Grafo>& grafos, vector<int> tamMochilas, vector<Camino>& caminos);

void medirTiempos(vector<Camino>& caminos, ofstream& salida);

void expAleat(ofstream& salida);
void expOpAleat(ofstream& salida);
void expMejor(ofstream& salida);
void expOpMejor(ofstream& salida);

#endif