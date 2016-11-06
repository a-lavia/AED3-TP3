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
            cout << "Experimento con instancias aleatorias y sus soluciones optimas:" << endl << endl;

            string stringExperimento = stringPrincipio + "-aleatOp";

            cout << "Vecindad = permutaCamino" << endl;
            
            string stringPermutaCamino = stringExperimento + "-permutaCamino";
            
            string stringPermutaCaminoBL = stringPermutaCamino + "-BL.csv";
            ofstream salidaPermutaCaminoBL;
            salidaPermutaCaminoBL.open(stringPermutaCaminoBL.c_str());

            string stringPermutaCaminoOp = stringPermutaCamino + "-Op.csv";
            ofstream salidaPermutaCaminoOp;
            salidaPermutaCaminoOp.open(stringPermutaCaminoOp.c_str());

            expAleatOp(salidaPermutaCaminoBL, salidaPermutaCaminoOp, permutaCamino);
            salidaPermutaCaminoBL.close();
            salidaPermutaCaminoOp.close();

            cout << endl << "Vecindad = permutaYReemplazaPokeparadas" << endl;

            string stringPermutaYReemplazaPokeparadas = stringExperimento + "-permutaYReemplazaPokeparadas";
            
            string stringPermutaYReemplazaPokeparadasBL = stringPermutaYReemplazaPokeparadas + "-BL.csv";
            ofstream salidaPermutaYReemplazaPokeparadasBL;
            salidaPermutaYReemplazaPokeparadasBL.open(stringPermutaYReemplazaPokeparadasBL.c_str());

            string stringPermutaYReemplazaPokeparadasOp = stringPermutaYReemplazaPokeparadas + "-Op.csv";
            ofstream salidaPermutaYReemplazaPokeparadasOp;
            salidaPermutaYReemplazaPokeparadasOp.open(stringPermutaYReemplazaPokeparadasOp.c_str());

            expAleatOp(salidaPermutaYReemplazaPokeparadasBL, salidaPermutaYReemplazaPokeparadasOp, permutaYReemplazaPokeparadas);
            salidaPermutaYReemplazaPokeparadasBL.close();
            salidaPermutaYReemplazaPokeparadasOp.close();

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
            cout << "Modo de uso: ./exp.out [opcion]" << endl;
            cout << "[opcion] == 0: experimento con instancias aleatorias" << endl;
            cout << "[opcion] == 1: experimento con instancias aleatorias y sus soluciones optimas" << endl;
        }
    }
    
    return 0;
}