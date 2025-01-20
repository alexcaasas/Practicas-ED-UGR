
/**
 * @file morphing.cpp
 * @brief Fichero para la prueba del ejercicio "Morphing"
*/

#include <cstdlib>
#include <iostream> 

#include <image.h>
#include <video.h>

using namespace std; 


int main (int argc, char ** argv) {

  Image origen, destino;
  Video morphing;

  int numero = atoi(argv[4]);

  string path = argv[3];

  string prefijo = argv[5];
  
  if (argc != 6){
    cerr << endl << "Error: Número de parámetros incorrecto. " << endl;
    cerr << "Uso: " << argv[0] << " <fich_E> <fich_S> prefijo" << endl << endl;
    exit (1);
  }

  if (!origen.Load(argv[1])){
    cerr << "Error: " << argv[1] << " no es un fichero PGM válido" << endl;
    exit(1);
  }
  
  if (!destino.Load(argv[2])){
    cerr << "Error: " << argv[2] << " no es un fichero PGM válido" << endl;
    exit(1);
  }

  //Hacer morphing y escribir video
  morphing = morphing.Morphing(origen, destino, numero);
  morphing.EscribirVideo(path, prefijo);

  cout << endl << "*****************************************************************" << endl <<
                "Morphing finalizado." << endl <<
                "*****************************************************************" << endl;

}


