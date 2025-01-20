/**
* @file conexion.h
  * @brief Fichero cabecera del TDA conexion
  */

#ifndef CONEXION__
#define CONEXION__
#define LINUX
                      
#ifdef WINDOWS
#include <winsock2.h>

#ifdef LINUX
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif // LINUX

#include <iostream>

#define PUERTO 5126

using namespace std;

/*********************************************************************************/
/*                             CLASE conexion                                    */
/* Utilizada tanto por el server como por el cliente.                            */
/* La mecanica de uso es la siguiente primero el server hace Crear_Servidor() y  */
/* Aceptar_Cliente(). Quedando el flujo de control del server parado en este     */
/* ultimo metodo hasta que el cliente hace Establecer_Conexion(). A partir de    */
/* ahi tenemos establecida la conexion y ambos pueden usar Enviar_Msg o          */
/* Recibr_Msg, pero claro siempre un envio en uno debe tener la correspondiente  */
/*recepcion en el otro. Al terminar ambos deben hacer Cerrar_Conexion.           */
/*********************************************************************************/
class Conexion {

  private:
  /**
  * @page repConexion Representación del TDA Conexion
  * @section abstraccionConexion Función de abstracción
  * Un objeto válido de nuestro TDA Conexion representa una conexión de red con:
  * - direccion: La dirección IP utilizada en el servidor y cliente
  * - conectado: El socket del cliente conectado
  * - sock: El socket utilizado en el servidor
  * - bytesenv: El número de bytes enviados
  * - bytesrecv: El número de bytes recibidos
  * - buffer: Un buffer para almacenar los datos enviados y recibidos
  */


    struct sockaddr_in direccion;    /** <direccion ip Usado en servidor y cliente> */
    int conectado;                   /** <socket del cliente conectado> */
    int sock;                        /** <socket usado en el servidor> */
    int bytesenv, bytesrecv;         /** <bytes enviados y recibidos usado en servidor y cliente> */
    char buffer[1024];
    
  public:

  /**
     * @brief Metodo que crea el sock hace el bind y define puerto y tamaño de cola de
     * espera. Se usa solo en el proceso que actua de server para crear el server.
     * Se usa una sola vez al principio para crear el servidor.
     */
     void Crear_Servidor();

  /**
    * @brief Se hace solo en el server y el server se queda a la espera de que un cliente  se conecte.
    * Esta funcion no termina hasta que se conecta un cliente. Esta funcion se usa una sola vez en  el servidor.
    * @return Devuelve el socket al cliente conectado.
    */
     int Aceptar_Cliente();

  /**
    * @brief Establece la conexion del cliente con el server. Se hace solo en el cliente
    * y una sola vez para establecer la conexion con el server. Hay que pasarle la  direccion ip del server.
    * El server puede estar en otra red distinta a la del cliente.
 	*/
     void Establecer_Conexion(const char *dir_ip);

  /**
	* @brief Funcion para enviar un mensaje. Usada tanto por el servidor como el cliente. Envia una cadena de caracteres.
  	* @param msg Puntero al mensaje a enviar
	*/
     void Enviar_Msg(char *msg);

  /**
	* Funcion para recibir un mensaje.lo enviado.Usada tanto por el servidor como el cliente.
	* Tantas veces como se quiera a lo largo de un programa.
 	* @param msg Puntero al buffer donde aparecera lo enviado
	*/
     void Recibir_Msg(char *msg);

  /**
	* @brief Destruye el socket y cierra la conexion. Se usa tanto en el server como en el
	* cliente para cerrar la conexion al terminar el programa. Podria estar
	* perfectamente en el destructor del objeto en lugar de un metodo a parte.
 	*/
     void Cerrar_Conexion();

};


#endif
