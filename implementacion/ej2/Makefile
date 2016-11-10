.PHONY: all clean

BIN = ej2 ej2SH

all:
	g++ ej2.cpp funciones.cpp -std=c++11 -o ej2
	# g++ SegundaHeuristica.cpp -std=c++11 -o ej2SH

borrartests:
	rm -f *.txt

clean:
	rm -f $(BIN)