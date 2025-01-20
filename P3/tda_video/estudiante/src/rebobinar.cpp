/**
 * @file rebobinar.cpp
 * @brief Fichero para la prueba del ejercicio "Rebobinar"
*/

#include <cstdlib>
#include <iostream>
#include <string>

#include <video.h>

using namespace std;


int main (int argc, char ** argv) {

    Video lectura;
    Video rebobinado;

    string path_lectura = argv[1];
    string prefijo = argv[2];


    if (argc != 4){
        cerr << endl << "Error: Número de parámetros incorrecto. " << endl;
        cerr << "Uso: " << argv[0] << " <RutaVideo> <Prefijo> " << endl << endl;
        exit (1);
    }

    //Rebobinar un video leido, y su escritura
    lectura.LeerVideo(path_lectura);
    rebobinado = rebobinado.Rebobinar(lectura);
    rebobinado.EscribirVideo(argv[3], prefijo);

    cout << endl << "*****************************************************************" << endl <<
                    "Rebobinado finalizado." << endl <<
                    "*****************************************************************" << endl;
}


