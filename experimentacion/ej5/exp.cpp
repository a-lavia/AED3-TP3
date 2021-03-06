#include "aux.h"
#include "funciones.h"

int main(int argc, char* argv[]){
    srand(420);

    string stringPrincipio = "exp-ej5";

    switch(atoi(argv[1])){
        case 0 : {
            cout << "Instancias aleatorias:" << endl << endl;

            vector<Camino> caminos(CANT_CASOS);
            generarCaminosAleat(caminos);

            string stringExperimento = stringPrincipio + "-aleat";

            cout << "Soluciones golosas..." << endl;
            string stringSolGolosa = stringExperimento + "-solGolosa.csv";
            ofstream salidaSolGolosa;
            salidaSolGolosa.open(stringSolGolosa.c_str());
            generarSalidaSG(caminos, salidaSolGolosa);
            salidaSolGolosa.close();
            cout << "Listo" << endl;

            asignarSoluciones(caminos);

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

            cout << endl << "GRASP..." << endl;
            string stringGRASP = stringExperimento + "-GRASP.csv";
            ofstream salidaGRASP;
            salidaGRASP.open(stringGRASP.c_str());
            generarSalidaGRASP(caminos, salidaGRASP);
            salidaGRASP.close();
            cout << "Listo" << endl;

            break;
        }
        case 1 : {
            cout << "Instancias aleatorias y sus soluciones optimas:" << endl << endl;

            vector<Camino> caminos(CANT_NODOS_MAX_OP);
            generarCaminosAleatOp(caminos);

            string stringExperimento = stringPrincipio + "-aleatOp";

            cout << "Soluciones golosas..." << endl;
            string stringSolGolosa = stringExperimento + "-solGolosa.csv";
            ofstream salidaSolGolosa;
            salidaSolGolosa.open(stringSolGolosa.c_str());
            generarSalidaSG(caminos, salidaSolGolosa);
            salidaSolGolosa.close();
            cout << "Listo" << endl;

            asignarSoluciones(caminos);

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

            cout << endl << "GRASP..." << endl;
            string stringGRASP = stringExperimento + "-GRASP.csv";
            ofstream salidaGRASP;
            salidaGRASP.open(stringGRASP.c_str());
            generarSalidaGRASP(caminos, salidaGRASP);
            salidaGRASP.close();
            cout << "Listo" << endl;
            
            cout << endl << "Soluciones optimas..." << endl;
            string stringOp = stringExperimento + "-Op.csv";
            ofstream salidaOp;
            salidaOp.open(stringOp.c_str());
            generarSalidaOp(caminos, salidaOp);
            salidaOp.close();
            cout << "Listo" << endl;
            
            break;
        }
        default : {
            cout << "Modo de uso: ./exp.out [opcion]" << endl;
            cout << "[opcion] == 0: instancias aleatorias" << endl;
            cout << "[opcion] == 1: instancias aleatorias y sus soluciones optimas" << endl;
        }
    }
    
    return 0;
}
