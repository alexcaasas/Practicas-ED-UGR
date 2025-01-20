//
// Created by jossemmii on 11/10/24.
//

#include <iostream>
#include "video.h"  // Incluye tu archivo de encabezado Video

using namespace std;

int main() {

    Video v;

    //*********************************************************************************************
    //Prueba 1: leer un video
    //*********************************************************************************************

    const string leerPath = "../videos/missa";  //Cambiar el path de lectura a dónde se quiera leer
    bool videoLeido = v.LeerVideo(leerPath);

    if (videoLeido) {
        cout << "VIDEO LEIDO EXITOSAMENTE";
    }
    else
        cout << "EL VIDEO NO HA PODIDO SER LEIDO";


    //*********************************************************************************************
    //Prueba 2: escribir video (leido de la carpeta missa, escrito en una nueva carpeta /nuevoVideo
    //*********************************************************************************************

    const string pathAescribir = "../videos/nuevoVideo"; //Cambiar el path de escritura a la nueva carpeta que se quiera escribir
    bool videoEscrito = v.EscribirVideo(pathAescribir,"nuevoVideo");

    if (videoEscrito) {
        cout << "El video se ha escrito correctamente." << std::endl;
        cout << "Número de fotogramas escritos: " << v.size() << std::endl;
    } else {
        cout << "Error al escribir el video." << std::endl;
    }

}