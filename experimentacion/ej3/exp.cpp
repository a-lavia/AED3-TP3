#include "aux.h"
#include "funciones.h"

int main(int argc, char* argv[]){
    string stringPrincipio = "exp-ej3";

    switch(atoi(argv[1])){
        case 0 : {
            cout << "Experimento con instancias aleatorias:" << endl << endl;

            string stringExperimento = stringPrincipio + "-aleat";

            cout << "Vecindad = permutaCamino" << endl;
            
            string stringPermutaCamino = stringExperimento + "-permutaCamino.csv";
            ofstream salidaPermutaCamino;
            salidaPermutaCamino.open(stringPermutaCamino.c_str());
            expAleat(salidaPermutaCamino, permutaCamino);
            salidaPermutaCamino.close();

            cout << endl << "Vecindad = permutaYReemplazaPokeparadas" << endl;

            string stringPermutaYReemplazaPokeparadas = stringExperimento + "-permutaYReemplazaPokeparadas.csv";
            ofstream salidaPermutaYReemplazaPokeparadas;
            salidaPermutaYReemplazaPokeparadas.open(stringPermutaYReemplazaPokeparadas.c_str());
            expAleat(salidaPermutaYReemplazaPokeparadas, permutaYReemplazaPokeparadas);
            salidaPermutaYReemplazaPokeparadas.close();

            break;
        }
        case 1 : {
            // Instancias aleatorias comparadas con el optimo



            break;
        }
        case 2 : {
            // Instancias de mejor caso para la busqueda local



            break;
        }
        case 3 : {
            // Instancias de mejro caso para la busqueda local comparadas con el optimo



            break;
        }
        case 4 : {
            // Comparacion de las dos heuristicas con las dos vecindades



            break;
        }
        default : {
            // Todos los experimentos anteriores. Uso archivos que se llamen como salida + "Aleat", etc.
            int sinoNoCompila;

            
            
        }
    }
    
    return 0;
}