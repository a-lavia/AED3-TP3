.PHONY: all clean

BIN = exp.out

all:
	g++ exp.cpp funciones.cpp ../../implementacion/ej3/aux.cpp ../../implementacion/ej3/Grafo.cpp ../../implementacion/ej3/Camino.cpp ../../implementacion/ej2/heuristica.cpp ../../implementacion/ej1/backtracking.cpp ../../implementacion/ej4/grasp.cpp -std=c++11 -o exp.out

clean:
	rm -f $(BIN)