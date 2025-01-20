/**
  * @file tablero.h
  * @brief Fichero cabecera del TDA Tablero
  *
  */
#ifndef __TABLERO__H__
#define __TABLERO__H__

/* ***************************************** */

#include <iostream>
#include "ficha.h"

/* ***************************************** */

class Tablero {

  private:
  /**
    * @page repTablero Rep del TDA Tablero
    * @section abtraccionTablero Función de abstracción
    * Un objeto válido rep nuestro TDA Jugador representa un jugador con:
    * - tab: Tablero de fichas 3x3
    * - numfichas: Número de fichas que han sido colocadas en el tablero
    */



    Ficha tab[3][3];      /** <Tablero de fichas 3x3> */
    int numfichas;        /** <Número de fichas que han sido puestas en total> */

  /**
    * @brief Copiamos el tablero que tenemos en nuestro parámetro
    * @param orig Tablero origen a copiar
    */
    void copia_tablero(const Tablero &orig);

  /**
     * @brief Verifica si la ficha del tipo del parámetro ha hecho 3 en raya
     * @param fic Ficha de la que se comprobará si tiene 3 en raya
     * @return Devuelve true si la ficha `fic` tiene tres en raya sino devuelve false
     */
    bool hay3raya(const Ficha &fic) const;

  public:
  /**
    * @brief Constructor por defecto de la clase
    */
    Tablero();

  /**
    * @brief Destructor vacío de la clase
    */
    ~Tablero() { };

  /**
  * @brief Constructor de copias de la clase
  * @param orig Tablero origen del que se copian sus datos
  */
    Tablero(const Tablero &orig);

  /**
    * @brief Sobrecarga del operador de asignación para la clase Tablero
    * @param orig Tablero origen del que se copiarán los datos
    * @return Asigna los valores del tablero origen al nuevo tablero
    */
    Tablero& operator=(const Tablero &orig);

  /**
    * @brief Inicializa el tablero poniendo todas las casillas en blanco.
    * @post Todas las posiciones del tablero se ponen en blanco y el contador de fichas se reinicia.
    */
    void PonerEnBlanco();

  /**
   * @brief Coloca una ficha en una posición específica del tablero
   * @param f Fila donde se colocará la ficha
   * @param c Columna donde se colocará la ficha
   * @param fic Tipo de ficha que se colocará en la posición indicada
   * @return Devuelve true si la ficha se pudo colocar y false si no se pudo
   * @pre La casilla con la posición donde vamos a insertar nuestra ficha debe estar en blanco
   */
    bool PonFicha(int f, int c, const Ficha &fic);

  /**
   * @brief Devuelve el tipo de la ficha que está en la posición dada
   * @param f Fila del tablero
   * @param c Columna del tablero
   * @return Devuelve la ficha que está en la posición dada
   */
    Ficha QueFichaHay(int f, int c) const;

  /**
    * @brief Devuelve si hay algún jugador que tenga 3 en raya
    * @return Devuelve el tipo de ficha ganadora y si no hay devuelve en blanco
    */
    Ficha Busca3Raya() const;

  /**
     * @brief Función que cuenta el número de fichas totales colocadas en el tablero
     * @return numfichas que es el número total
     */
    int CuantasFichas() const { return numfichas; };

};

/**
 * @brief Sobrecarga del operador de salida para mostrar el tablero
 * @param salida stream de salida
 * @param tab Tablero a sacar por pantalla
 * @post Obtenemos el stream de salida con el tablero 3x3 y sus fichas
 */
std::ostream& operator<<(std::ostream &salida, const Tablero &tab);

/* ***************************************** */

#endif
