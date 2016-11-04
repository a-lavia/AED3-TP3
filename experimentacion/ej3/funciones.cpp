#include "funciones.h"

int aleatEnRango(int min, int max){
    return min + (rand() % (int)(max - min + 1));
}

int max(int a, int b){
    if(a >= b){
        return a;
    } else{
        return b;
    }
}

int min(int a, int b){
    if(a <= b){
        return a;
    } else{
        return b;
    }
}

void generarGrafosAleat(vector<Grafo>& grafos){

}

void generarGrafosOpAleat(vector<Grafo>& grafos){

}

void generarGrafosMejor(vector<Grafo>& grafos){

}

void generarGrafosOpMejor(vector<Grafo>& grafos){

}

void generarCaminos(vector<Grafo>& grafos, vector<int> tamMochilas, vector<Camino>& caminos){

}

void medirTiempos(vector<Camino>& caminos, ofstream& salida){

}

void expAleat(ofstream& salida){
    vector<Grafo> grafos;
    vector<int> tamMochilas;
    vector<Camino> caminos;

    generarGrafosAleat(grafos);
    
    generarCaminos(grafos, tamMochilas, caminos);
    
    medirTiempos(caminos, salida);
}

void expOpAleat(ofstream& salida){

}

void expMejor(ofstream& salida){

}

void expOpMejor(ofstream& salida){

}