/**
 * @file juego.h
 * @brief Fichero de cabecera de la clase Juego3Raya
 */
#ifndef __JUEGO__H__
#define __JUEGO__H__

/* ***************************************** */

#include "tablero.h"
#include "jugador.h"

/**
 * @brief Clase Juego3Raya
 * Una instancia @e j del tipo de datos abstracto @c Juego3Raya es un objeto que representa un juego
 * del tres en raya entre dos jugadores.
 *
 * Tablero, Jugador 1, Jugador 2
 *
 * Un ejemplo de su uso:
 * @include juego.cpp
 *
 * @author Josemi
 * @date Septiembre 2024
 */

/* ***************************************** */

class Juego3Raya {
  private:

    /**
  * @page repJuego Representación del TDA Juego3Raya
  *
  * @section jugadores Jugadores
  *
  * Hay dos jugadores, Jugador 1 y Jugador 2
  *
  * @section tab Tablero
  *
  * Hay un tablero de juego
  *
  * @section turno Turno
  *
  * Hay un entero que indica a quien le toca jugar
  *
  * @section juego Funcion de abstraccion
  *
  * Un objeto @e juego del TDA Juego3Raya representa un juego del tres en raya entre dos jugadores.
  *
  * (juego.jug1, juego.jug2, juego.tab, juego.turno)
  *
  */

    Jugador jug1, jug2;    /**< Jugadores */
    Tablero tab;           /**< Tablero */
    int turno;             /**< Turno */

  public:

    /**
     * @brief Constructor de la clase
     * @param t Tablero de juego
     * @param j1 Jugador 1
     * @param j2 Jugador 2
     * @return Crea un nuevo juego con el tablero, jugador 1 y jugador 2
     */
    Juego3Raya(const Tablero &t, const Jugador &j1, const Jugador &j2);

    /**
     * @brief Destructor de la clase
     * @return Destruye el juego
     */
    ~Juego3Raya()  { };

    /**
     * @brief Prepara el juego para comenzar una nueva partida
     */
    void NuevoJuego();

    /**
     * @brief Avanza un turno
     */
    void JugarTurno();

    /**
     * @brief Devuelve una referencia (const) al tablero de juego (consultor)
     * @return tab Tablero de juego
     */
    const Tablero &ElTablero() const { return tab; };


    /**
     * @brief Devuelve una referencia (const) al jugador n-ésimo (n=0 ó 1)
     * @param n Número del jugador
     * @pre n == 0 || n == 1
     * @return Jugador n-ésimo
     */
    const Jugador &ElJugador(int n) const;

    /**
     * @brief Devuelve true si el juego ha terminado
     * @return true si el juego ha terminado, false en caso contrario
     * @post Juego acabado
     */
    bool HemosAcabado() const;

    /**
     * @brief Devuelve el número del jugador al que le toca poner ficha
     * @return turno Número del jugador al que le toca jugar
     */
    int AQuienLeToca() const  { return turno; };

    /**
     * @brief Devuelve el número del jugador que ha ganado
     * @return 0 si hay ganador, -1 si no hay ganador o empate
     */
    int QuienGana() const;
};

/* ***************************************** */

#endif
