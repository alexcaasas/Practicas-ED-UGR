/**
  * @file jugador.h
  * @brief Fichero cabecera del TDA Jugador
  *
  */
#ifndef __JUGADOR__H__
#define __JUGADOR__H__

/* ***************************************** */

#include <iostream>
#include <string>
#include "ficha.h"
#include "tablero.h"

/* ***************************************** */

class Jugador {
  private:
  /**
    * @page repJugador Rep del TDA Jugador
    * @section abtraccionJugador Función de abstracción
    * Un objeto válido rep nuestro TDA Jugador representa un jugador con:
    * - nombre: El nombre del jugador
    * - fic: El color de la ficha que usa (cruz o círculo)
    * - nivel: El nivel de habilidad del jugador
    * - tipo: Si es un jugador Local ('L') o Remoto ('R')
    * - ip: La dirección IP en caso de que sea un jugador remoto
    */

    std::string nombre;   /** <Nombre del jugador> */
    Ficha fic;            /** <Color de la ficha (cruz o circulo) */
    int nivel;            /** <Nivel del jugador */
    char tipo;            /** <Tipo de jugador (L)ocal o (R)emoto */
    std::string ip;       /** <En el caso de jugador remoto la ip. */


  /**
     * @brief Implementa la estrategia de juego del nivel 0 (nivel humano)
     * @param tab Referencia al tablero actual
     * @param fil Referencia a la fila donde se colocará la ficha
     * @param col Referencia a la columna donde se colocará la ficha
     */
     void piensa_nivel_0(const Tablero &tab, int &fil, int &col) const;

  /**
    * @brief Implementa la estrategia de juego del nivel 1 (nivel CPU básica)
    * @param tab Referencia al tablero actual
    * @param fil Referencia a la fila donde se colocará la ficha
    * @param col Referencia a la columna donde se colocará la ficha
    */
    void piensa_nivel_1(const Tablero &tab, int &fil, int &col) const;

  public:
  /**
    * @brief Constructor por defecto de la clase. Crea el jugador con nombre vacío, ficha en blanco, nivel 0 y tipo local
    */
    Jugador();

  /**
    * @brief Constructor con parámetros de la clase Jugador
    * @param n Nombre del jugador
    * @param f Ficha del color del jugador
    * @param ni Nivel del jugador
    * @param tip Tipo de jugador: 'L' para Local, 'R' para Remoto
    * @param direc Dirección IP en caso de ser jugador remoto
    * @pre El tipo debe ser 'L' o 'R'. Si el tipo es 'R', la dirección IP debe estar definida
    * @pre El nombre del jugador no puede estar vacío
    * @pre El color de la ficha no puede estar vacío
    * @return Crea un jugador con el nombre, ficha, nivel, tipo y dirección IP especificados
    */
    Jugador(const std::string &n, const Ficha &f, int ni, char tip, std::string direc);



  /**
    * @brief Sobrecarga del operador de asignación para la clase Jugador
    * @param orig Jugador origen del que se copiarán los datos
    * @return Asigna los valores del jugador origen al nuevo jugador
    */
    Jugador& operator=(const Jugador &orig);
    
  /**
    * @brief Función que obtiene el nombre del jugador
    * @return Devuelve el nombre del jugador
    */
    std::string Nombre() const         { return nombre; };
    
  /**
    * @brief Función set que pone el nombre a un jugador
    * @param nom Nombre nuevo del jugador
    * @pre El nombre no puede estar vacío
    */
    void setNombre(std::string nom)         { nombre=nom; };
    
  /**
    * @brief Función que obtiene el color de la ficha del jugador
    * @return Devuelve el color de la ficha
    */
    Ficha Color() const                { return fic; };
    
  /**
    * @brief Función get que obtiene el tipo de jugador, L ó R
    * @return Devuelve el tipo de jugador
    */
    char gettipo() const                { return tipo; };
    
  /**
    * @brief Función get que obtiene la dirección ip del jugador remoto
    * @return Devuelve la dirección ip remota
    */
    std::string getip() const {return ip;};
    
  /**
    * @brief Función get que obtiene el nivel del jugador, 0 ó 1
    * @return Devuelve el nivel
    */
    int getnivel() const {return nivel;};
    
  /**
    * @brief Establece el nivel del jugador
    * @param ni Nivel a asignar al jugador
    * @pre El nivel debe ser 0 ó 1
    */
    void setnivel(int ni) {nivel=ni;};
       
  /**
    * @brief Piensa la jugada que desea realizar el jugador
    * @param tab Referencia al tablero
    * @param fil Referencia a la fila donde el jugador quiere colocar la ficha
    * @param col Referencia a la columna donde el jugador quiere colocar la ficha
    * @post Modifica las variables fil y col para indicar la posición donde el jugador colocará su ficha
    */
    void PiensaJugada(const Tablero &tab, int &fil, int &col) const;
};

/* ***************************************** */

/**
 * @brief Sobrecarga del operador de salida para mostrar los datos del jugador
 * @param salida stream de salida
 * @param jug Jugador cuyos atributos se van a sacar por pantalla
 * @post Obtenemos el stream de salida con los datos del jugador
 */
std::ostream& operator<<(std::ostream &salida, const Jugador &jug);

/* ***************************************** */

#endif
