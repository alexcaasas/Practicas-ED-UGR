/**
 * @file maxqueue.h
 * @brief Fichero de cabecera del TDA MaxQueue
 *
 * Implementación del TDA MaxQueue
 */

#ifndef MAXQUEUE_H
#define MAXQUEUE_H

#include <iostream>
#include <list>

using namespace std;


/**
 * @brief Struct element que almacena el valor y el máximo de los valores almacenados en la cola.
 * Incluye un operador de salida para mostrar el contenido del struct, que es el valor y el máximo.
 */
struct element {
    int value;
    int maximum;

     /**
    * @brief Sobrecarga del operador de salida
    * @param os Flujo de salida
    * @param elem Elemento de salida
    * @return Salida
    */
     friend ostream& operator<<(ostream& os, const element& elem);
};


/**
 *
 * @brief T.D.A. MaxQueue
 * Una instancia del tipo MaxQueue representa una queue de la STL. La diferencia es que internamente
 * se está implementando con una lista.
 * El TDA MaxQueue proporciona todas las herramientas disponibles en la STL de queue, como son
 * push, pop, front, empty, size, swap, constructor y destructor.
 * Otra característica es que en la instancia del tipo MaxQueue, cada elemento en la list de la capa de abajo
 * es de tipo element, un struct con un campo value y un campo maximum.
 * Este element permite almacenar el valor a insertar en la instancia MaxQueue, en el campo value, y el máximo de los values.
 *
 * \#include <maxqueue.h>
 *
 * @authors Alejandro Martín Casas y José Miguel Aguado Coca
 * @date Noviembre 2024
 *
 */

class MaxQueue {

    /**
    * @page repMaxQueue Representación del TDA MaxQueue
    *
    * @section invMaxQueue Invariante de la representación
    * Un objeto válido del TDA MaxQueue debe cumplir:
    *
    * - En cada instante, el valor maximum de un element, debe ser el mayor máximo entre ese value y los values
    *   insertados anteriormente. Si inserto 1, 3, 6, el estado de MaxQueue sería:
    *   MaxQueue = { {1,6}, {3,6}, {6,6} }
    *
    * - Si se añade en MaxQueue un elemento con value menor al máximo actual, el máximo de este nuevo value será el mismo
    *   value. Esto se debe a que los máximos deben ir de forma creciente.
    *   Por ejemplo: Inserto 1, 3, 6, 2, el estado de MaxQueue sería:
    *   MaxQueue = { {1,6}, {3,6}, {6,6}, {2,2} }
    *
    * @section faMaxQueue Función de abstracción
    * Un objeto válido del TDA MaxQueue representa una cola de elementos, dónde cada elemento está
    * formado por "value" y "maximum". "value" es el valor que se inserta en la cola y "maximum" es el
    * máximo valor de los elementos. Internamente, MaxQueue es una lista de elementos.
    *
    * { {value1, maximum1}, {value2, maximum2}, ..., {valueN, maximumN} }
    *
    */

    private:

        /**
        * @brief Contenedor subyacente de MaxQueue, una lista
        */
        list <element> contenedorSubyacente;

    public:

        /**
         * @brief Constructor por defecto de la cola
         * @post Genera una instancia de MaxQueue vacía
         */
        MaxQueue();

        /**
         * @brief Constructor de copia
         * @param Q Cola a copiar
         * @pre Q tiene que ser distinto a la instancia actual
         * @post Genera una copia de la cola Q
         */
        MaxQueue(const MaxQueue &Q);

        /**
         * @brief Destructor
         * @pre La cola debe existir para poder destruirla
         * @post Destruye la cola, y no puede volverse a usar
         */
        ~MaxQueue();

        /**
        * @brief Consulta el tamaño de la cola
        * @return Tamaño de la cola
        */
        int size() const;


        /**
        * @brief Consulta si la cola está vacía
        * @return True si la cola está vacía y  false si hay algún elemento
        */
        bool empty() const;

        /**
        * @brief Consulta el primer elemento de la cola, su front.
        * El front de la cola MaxQueue equivale al front de su lista subyacente.
        * @pre La cola no puede estar vacía
        * @return Devuelve el elemento que está en el frente de la cola (value y maximum)
        */
        element &front();

        /**
        * @brief Consulta constante del primer elemento de la cola
        * El front de la cola MaxQueue equivale al front de su lista subyacente.
        * @pre La cola no puede estar vacía
        * @return Devuelve el elemento que está en el frente de la cola (value y maximum)
        */
        const element &front() const;

       /**
       * @brief Inserta un elemento en la cola MaxQueue.
       * @post Se ha insertado un elemento en la cola
       */
        void push(const int &value);

        /**
        * @brief Elimina el primer elemento de la cola. Este pop es equivalente al pop_front de la lista subyacente.
        * @pre La cola MaxQueue no puede estar vacía
        * @post Queda eliminado el primer elemento de la cola
        */
        void pop();

        /**
        *@brief Elimina todos los elementos de la cola
        *@post La pila queda vacía
        */
        void clear();

        /**
        * @brief Intercambia el contenido de dos colas
        * @param c Cola con la que se intercambia el contenido de nuestra cola actual
        * @post Quedan intercambiados los contenidos de las dos colas
*/
        void swap(MaxQueue & c);

};


#endif
