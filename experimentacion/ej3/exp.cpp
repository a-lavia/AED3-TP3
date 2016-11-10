#include "aux.h"
#include "funciones.h"

int main(int argc, char* argv[]){
    string stringPrincipio = "exp-ej3";

    switch(atoi(argv[1])){
        case 0 : {
            cout << "Experimento con instancias aleatorias:" << endl << endl;

            vector<Camino> caminos(CANT_CASOS);
            generarCaminosAleat(caminos);
            asignarSoluciones(caminos);

            string stringExperimento = stringPrincipio + "-aleat";

            cout << "Vecindad = permutaCamino..." << endl;
            string stringPermutaCamino = stringExperimento + "-permutaCamino.csv";
            ofstream salidaPermutaCamino;
            salidaPermutaCamino.open(stringPermutaCamino.c_str());
            generarSalidaBL(caminos, permutaCamino, salidaPermutaCamino);
            salidaPermutaCamino.close();
            cout << "Listo" << endl;

            cout << endl << "Vecindad = permutaYReemplazaPokeparadas..." << endl;
            string stringPermutaYReemplazaPokeparadas = stringExperimento + "-permutaYReemplazaPokeparadas.csv";
            ofstream salidaPermutaYReemplazaPokeparadas;
            salidaPermutaYReemplazaPokeparadas.open(stringPermutaYReemplazaPokeparadas.c_str());
            generarSalidaBL(caminos, permutaYReemplazaPokeparadas, salidaPermutaYReemplazaPokeparadas);
            salidaPermutaYReemplazaPokeparadas.close();
            cout << "Listo" << endl;

            break;
        }
        case 1 : {
            cout << "Experimento con instancias aleatorias y sus soluciones optimas:" << endl << endl;

            vector<Camino> caminos(CANT_NODOS_MAX_OP + 1);
            generarCaminosAleatOp(caminos);
            asignarSoluciones(caminos);

            string stringExperimento = stringPrincipio + "-aleatOp";

            cout << "Busqueda local con vecindad = permutaCamino..." << endl;
            string stringPermutaCamino = stringExperimento + "-permutaCamino.csv";
            ofstream salidaPermutaCamino;
            salidaPermutaCamino.open(stringPermutaCamino.c_str());
            generarSalidaBL(caminos, permutaCamino, salidaPermutaCamino);
            salidaPermutaCamino.close();
            cout << "Listo" << endl;

            cout << endl << "Busqueda local con vecindad = permutaYReemplazaPokeparadas..." << endl;
            string stringPermutaYReemplazaPokeparadas = stringExperimento + "-permutaYReemplazaPokeparadas.csv";
            ofstream salidaPermutaYReemplazaPokeparadas;
            salidaPermutaYReemplazaPokeparadas.open(stringPermutaYReemplazaPokeparadas.c_str());
            generarSalidaBL(caminos, permutaYReemplazaPokeparadas, salidaPermutaYReemplazaPokeparadas);
            salidaPermutaYReemplazaPokeparadas.close();
            cout << "Listo" << endl;
            
            /*cout << endl << "Soluciones optimas..." << endl;
            string stringOp = stringExperimento + "-Op.csv";
            ofstream salidaOp;
            salidaOp.open(stringOp.c_str());
            generarSalidaOp(caminos, salidaOp);
            salidaOp.close();
            cout << "Listo" << endl;*/
            
            break;
        }
        case 2 : {
            cout << "Experimento con instancias donde la busqueda local corrige mejor:" << endl << endl;

            vector<Camino> caminos(CANT_CASOS);
            generarCaminosMejor(caminos);
            asignarSoluciones(caminos);

            string stringExperimento = stringPrincipio + "-mejor";

            cout << "Vecindad = permutaCamino..." << endl;
            string stringPermutaCamino = stringExperimento + "-permutaCamino.csv";
            ofstream salidaPermutaCamino;
            salidaPermutaCamino.open(stringPermutaCamino.c_str());
            generarSalidaBL(caminos, permutaCamino, salidaPermutaCamino);
            salidaPermutaCamino.close();
            cout << "Listo" << endl;

            cout << endl << "Vecindad = permutaYReemplazaPokeparadas..." << endl;
            string stringPermutaYReemplazaPokeparadas = stringExperimento + "-permutaYReemplazaPokeparadas.csv";
            ofstream salidaPermutaYReemplazaPokeparadas;
            salidaPermutaYReemplazaPokeparadas.open(stringPermutaYReemplazaPokeparadas.c_str());
            generarSalidaBL(caminos, permutaYReemplazaPokeparadas, salidaPermutaYReemplazaPokeparadas);
            salidaPermutaYReemplazaPokeparadas.close();
            cout << "Listo" << endl;

            break;
        }
        case 3 : {
            cout << "Experimento con instancias donde la busqueda local corrige mejor y sus soluciones optimas" << endl << endl;

            vector<Camino> caminos(CANT_NODOS_MAX_OP + 1);
            generarCaminosMejorOp(caminos);
            asignarSoluciones(caminos);

            string stringExperimento = stringPrincipio + "-mejorOp";

            cout << "Busqueda local con vecindad = permutaCamino..." << endl;
            string stringPermutaCamino = stringExperimento + "-permutaCamino.csv";
            ofstream salidaPermutaCamino;
            salidaPermutaCamino.open(stringPermutaCamino.c_str());
            generarSalidaBL(caminos, permutaCamino, salidaPermutaCamino);
            salidaPermutaCamino.close();
            cout << "Listo" << endl;

            cout << endl << "Busqueda local con vecindad = permutaYReemplazaPokeparadas..." << endl;
            string stringPermutaYReemplazaPokeparadas = stringExperimento + "-permutaYReemplazaPokeparadas.csv";
            ofstream salidaPermutaYReemplazaPokeparadas;
            salidaPermutaYReemplazaPokeparadas.open(stringPermutaYReemplazaPokeparadas.c_str());
            generarSalidaBL(caminos, permutaYReemplazaPokeparadas, salidaPermutaYReemplazaPokeparadas);
            salidaPermutaYReemplazaPokeparadas.close();
            cout << "Listo" << endl;
            
            /*cout << endl << "Soluciones optimas..." << endl;
            string stringOp = stringExperimento + "-Op.csv";
            ofstream salidaOp;
            salidaOp.open(stringOp.c_str());
            generarSalidaOp(caminos, salidaOp);
            salidaOp.close();
            cout << "Listo" << endl;*/
            
            break;
        }
        default : {
            cout << "Modo de uso: ./exp.out [opcion]" << endl;
            cout << "[opcion] == 0: experimento con instancias aleatorias" << endl;
            cout << "[opcion] == 1: experimento con instancias aleatorias y sus soluciones optimas" << endl;
            cout << "[opcion] == 2: experimento con instancias donde la busqueda local corrige mejor" << endl;
            cout << "[opcion] == 3: experimento con instancias donde la busqueda local corrige mejor y sus soluciones optimas" << endl;
        }
    }
    
    return 0;
}