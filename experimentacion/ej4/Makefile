.PHONY: all clean

BIN = experimento_1 tiempos_1 tiempos_2 tiempos_3

all:
	g++ experimento_1.cpp ../../implementacion/ej4/grasp.cpp ../../implementacion/ej3/Grafo.cpp ../../implementacion/ej3/Camino.cpp ../../implementacion/ej3/aux.cpp ../../implementacion/ej2/heuristica.cpp ../gen_instancias/gen.cpp -std=c++11 -o experimento_1
	g++ tiempos_1.cpp ../../implementacion/ej4/grasp.cpp ../../implementacion/ej3/Grafo.cpp ../../implementacion/ej3/Camino.cpp ../../implementacion/ej3/aux.cpp ../../implementacion/ej2/heuristica.cpp ../gen_instancias/gen.cpp -std=c++11 -o tiempos_1
	g++ tiempos_2.cpp ../../implementacion/ej4/grasp.cpp ../../implementacion/ej3/Grafo.cpp ../../implementacion/ej3/Camino.cpp ../../implementacion/ej3/aux.cpp ../../implementacion/ej2/heuristica.cpp ../gen_instancias/gen.cpp -std=c++11 -o tiempos_2
	g++ tiempos_3.cpp ../../implementacion/ej4/grasp.cpp ../../implementacion/ej3/Grafo.cpp ../../implementacion/ej3/Camino.cpp ../../implementacion/ej3/aux.cpp ../../implementacion/ej2/heuristica.cpp ../gen_instancias/gen.cpp -std=c++11 -o tiempos_3

clean:
	rm -f $(BIN)
