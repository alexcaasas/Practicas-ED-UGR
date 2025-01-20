/**
 * @file ficha.h
 * @brief Fichero de cabecera de la enumeración Ficha
 */
#ifndef __FICHA__H__
#define __FICHA__H__

/* ***************************************** */

#include <iostream>

/**
 * @brief Enumerado Ficha
 *
 * La enumeración Ficha se utiliza para representar los distintos tipos de fichas que se pueden poner en el tablero.
 *
 * Un ejemplo de su uso:
 * @include ficha.cpp
 *
 * @author Josemi
 * @date Septiembre 2024
 */


/* ***************************************** */

/**
 * @page ficha Tipos de Ficha
 *
 * @section ficha_sec Tipos admitidos por la ficha
 *
 * Los valores posibles son:
 * - BLANCO
 * - CIRCULO
 * - CRUZ
 *
 */
enum Ficha {BLANCO, CIRCULO, CRUZ};

/* ***************************************** */

/**
 * @brief Sobrecarga del operador << para mostrar en ostream el símbolo de la ficha.
 *
 * @param salida Flujo de salida donde se escribirá el símbolo de la ficha.
 * @param fic Ficha a escribir, debe ser una de BLANCO, CIRCULO o CRUZ.
 *
 * @pre fic == BLANCO || fic == CIRCULO || fic == CRUZ
 *
 * @return salida El flujo de salida con el contenido:
 * - Si `fic == BLANCO`, escribe "   ".
 * - Si `fic == CIRCULO`, escribe " O ".
 * - Si `fic == CRUZ`, escribe " X ".
 */
std::ostream& operator<<(std::ostream &salida, const Ficha &fic);

/* ***************************************** */

#endif
