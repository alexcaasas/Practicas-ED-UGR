/**
* @file maxstack.h
 * @brief Fichero de cabecera del TDA MaxStack
 *
 * Implementación del TDA MaxStack
 */

#ifndef MAXSTACK_H
#define MAXSTACK_H

#include <iostream>
#include <queue>

using namespace std;

/**
 * @brief Struct element que almacena el valor y el máximo de los valores almacenados en la pila.
 * Incluye un operador de salida para mostrar el contenido del struct, que es el valor y el máximo
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
  @brief T.D.A. MaxStack

  Una instancia del TDA MaxStack permite almacenar una pila de elementos tipo <element>, cada uno con un valor y un valor máximo.
  Internamente, se implementa con una cola y una cola con prioridad.

  El TDA MaxStack proporciona herramientas para trabajar con pilas de elementos, como la posibilidad de insertar y eliminar elementos,
  consultar el elemento superior y obtener el tamaño de la pila.

  \#include <maxstack.h>

    @authors Alejandro Martín Casas y José Miguel Aguado Coca
    @date Noviembre 2024
**/

class MaxStack {

 /**
     * @page repMaxStack Representación del TDA MaxStack
     *
     * @section invMaxStack Invariante de la representación
     * Un objeto válido del TDA MaxStack debe cumplir:
     * - El elemento superior de la pila debe contener el último valor insertado, y el máximo.
     * - En cada instante, el máximo de un valor será el máximo de lo que tiene por delante, si el valor es menor que este máximo.
     * - Por el contrario, si el valor insertado es mayor que lo ya presente, el máximo será el valor insertado.
     *
     *   Por ejemplo si inserto 1,5,2,6 en ese orden. Nuestra pila sería:
     *   MaxStack = top { {6,6} {2,5} {5,5} {1,1} } bottom
     *
     * @section faMaxStack Función de abstracción del TDA MaxStack
     * Un objeto válido del TDA MaxStack representa una pila de elementos, dónde cada elemento está
     * formado por "value" y "maximum". "value" es el valor que se inserta en la pila y "maximum" es el
     * máximo valor de los elementos. Internamente, MaxStack es una cola y una cola con prioridad.
     *
     */


private:

    /**
     * @brief Contenedor subyacente de MaxStack para los valores, una cola
    */
    queue<int> contenedorValores;

    /**
     * @brief Contenedor subyacente de MaxStack para los valores, una cola con prioridad
    */
    priority_queue<int> contenedorMaximos;

    /**
     * @brief Elemento para almacenar el valor y el máximo de los valores almacenados en la pila
    */
    element elemento{};

public:

    /**
     *@brief Constructor por defecto
     *@post Genera una instancia de MaxStack vacía
    */
    MaxStack();

    /**
     *@brief Constructor de copia
     *@param S Pila a copiar
     *@pre S no puede ser igual a la instancia actual
     *@post Genera una copia de la pila S
    */
    MaxStack(const MaxStack &S);

    /**
     *@brief Destructor de MaxStack
     *@pre La pila debe existir para poder destruirla
     *@post Destruye la pila
    */
    ~MaxStack();

    /**
     *@brief Comprueba si la pila está vacía
     *@return Devuelve true si la pila está vacía y false si contiene algún elemento
    */
    bool empty() const;

    /**
     *@brief Elimina todos los elementos de la pila
     *@post La pila queda vacía
    */
    void clear();

    /**
     *@brief Intercambia el contenido de dos pilas
     *@param S Pila con la que se intercambia el contenido de nuestra pila actual
     *@pre Debemos tener una pila creada para poder intercambiarla con la pila S
     *@post Los contenidos de las dos pilas se intercambian
    */
    void swap(MaxStack &S);

    /**
     *@brief Consulta el elemento superior de la pila
     *@pre La pila no debe estar vacía para poder consultar el elemento superior
     *@return Devuelve el elemento superior de la pila con su valor y el máximo hasta ese punto
    */
    element& top();

    /**
     *@brief Consulta constante del elemento superior de la pila
     *@pre La pila no debe estar vacía para poder consultar el elemento superior
     *@return Devuelve el elemento superior de la pila con su valor y el máximo hasta ese punto
    */
    const element& top() const;

    /**
     *@brief Inserta un elemento en la pila
     *@param value Valor a insertar en la pila
     *@post El valor ha sido insertado en la pila
    */
    void push (const int &value);

    /**
     *@brief Elimina el elemento superior de la pila
     *@pre Para poder eliminar un elemento, la pila no puede estar vacía
     *@post Se elimina el elemento superior de la pila
    */
    void pop();

    /**
     *@brief Consulta el tamaño de la pila
     *@return Devuelve el tamaño de la pila
    */
    int size() const;


};


#endif