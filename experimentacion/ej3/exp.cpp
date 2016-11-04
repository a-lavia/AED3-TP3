#include "aux.h"
#include "funciones.h"

int main(int argc, char* argv[]){
    ofstream salida;
    salida.open(argv[1]); 

    switch(atoi(argv[2])){
        case 0 :
            // Instancias aleatorias
            expAleat(salida);
            break;
        case 1 :
            // Instancias aleatorias comparadas con el optimo
            expOpAleat(salida);
            break;
        case 2 :
            // Instancias de mejor caso para la busqueda local
            expMejor(salida);
            break;
        case 3 :
            // Instancias de mejro caso para la busqueda local comparadas con el optimo
            expOpMejor(salida);
            break;
        default :
            // Todos los experimentos anteriores. Uso archivos que se llamen como salida + "Aleat", etc.
            ofstream salidaAleat, salidaOpAleat, salidaMejor, salidaOpMejor;

            
            
            expAleat(salidaAleat);
            expOpAleat(salidaOpAleat);
            expMejor(salidaMejor);
            expOpMejor(salidaOpMejor);
    }

    salida.close();
    
    return 0;
}