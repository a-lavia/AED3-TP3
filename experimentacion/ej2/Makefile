.PHONY: all clean

BIN = exp exp2

all:
	g++ exp.cpp ../../implementacion/ej2/funciones.cpp -std=c++11 -o exp
	g++ expOtraHeuristica.cpp ../../implementacion/ej2/SegundaHeuristica.cpp -std=c++11 -o exp2

clean:
	rm -f $(BIN)