/**
* @file video.h
* @brief Fichero de cabecera del TDA Video
*
* Implementación del TDA Video
*/

#ifndef VIDEO__H
#define VIDEO__H

#include <iostream>
#include <vector>
#include <image.h>

using namespace std;

/**
  @brief T.D.A. Video

  Una instancia del tipo de dato abstracto Video permite almacenar una secuencia de fotogramas, que son imágenes en escala de grises.

  El TDA Video proporciona herramientas para trabajar con secuencias de imágenes, como la posibilidad de insertar y borrar imágenes, leer y escribir videos en disco, rebobinar un video y crear un video con el morphing de dos imágenes.
  Para poder usar el TDA Video es necesario incluir el fichero:

  \#include <video.h>

  @authors Alejandro Martín Casas y José Miguel Aguado Coca
  @date Octubre 2024

**/

class Video {

    /**
      @page repVideo Representación del TDA Video .

      @section invVideo Invariante de la representación.

      Un objeto válido del TDA Video debe cumplir:

        - Cada elemento del vector video debe ser una imagen
        - Cada elemento V(t) cumple 0<=t<n, siendo n el número de fotogramas

      @section faVideo Función de abstracción

      Un objeto válido del TDA Video representa un video formado por n fotogramas, siendo cada uno del tipo Image.

    **/

    private:

         /**
          * @brief Vector dinámico que almacena los fotogramas de tipo Image
         */
         vector<Image> video;

    public:

        /**
         * @brief Variable que almacena el número de digitos que contiene el nombre de un fotograma
        */
        static int numero;

        /**
         *@brief Constructor por defecto
         *@post Genera un video vacío
        */
        Video();

        /**
         *@brief Constructor de copia
         *@param J Video a copiar
         *@pre J no puede ser igual a la instancia actual
         *@post Se crea un video igual a J
        */
        Video(const Video &J);

        /**
         *@brief Constructor para crear un video con imágenes vacías
         *@param n Número de imágenes vacías
         *@pre n debe ser mayor a 0
         *@post Se crea un video de tamaño n lleno de valores basura (no inicializado)
        */
        Video(int n);


        /**
         *@brief Destructor de video
         *@post El objeto Video destruido no podrá volverse a usar a menos que se vuelva a construir
        */
        ~Video();


        /**
         *@brief Calcular el tamaño del video
         *@post El objeto Video no es modificado
         *@return Tamaño del video
        */
        int size() const;


        /**
         *@brief Operador de consulta y asignación de imagen en video
         *@param foto Imagen a consultar
         *@pre 0 <= foto < video.size()
         *@return Imagen asociada al fotograma en la posicion foto del video
        */
        Image &operator[](int foto);


        /**
         *@brief Operador constante de consulta y asignación de imagen en video
         *@param foto Imagen a consultar
         *@pre 0 <= foto < video.size()
         *@return Imagen asociada al fotograma en la posicion foto del video
        */
        const Image &operator[](int foto) const;

        /**
         * @brief Insertar una nueva imagen en el video
         * @param k Posición en la que se insertará la imagen
         * @param I Imagen a insertar
         * @pre 0 <= k < video.size()
         * @post El fotograma es insertado en la posición k
        */
        void Insertar(int k, const Image &I);

        /**
         * @brief Borrar una imagen en el video
         * @param k Posición de la imagen a borrar
         * @pre 0 <= k < video.size()
         * @post El fotograma en la posición k es borrado
        */
        void Borrar(int k);

        /**
         * @brief Leer un video del disco
         * @param path Ruta del video a leer
         * @pre En el directorio dado debe de haber una serie de imágenes que forman el vídeo
         * @return true si se ha leído correctamente, false en caso contrario
        */
        bool LeerVideo(const string &path);

        /**
         * @brief Escribir un video en disco
         * @param path Ruta del directorio donde se va a escribir el video
         * @param prefijo Prefijo de las imágenes en el directorio creado
         * @pre En el directorio path se creará una serie de imágenes con nombres <prefijo>_00.pgm <prefijo>_0n-1.pgm sabiendo que n es el número de imágenes del vídeo
         * @return true si se ha escrito correctamente, false en caso contrario
        */
        bool EscribirVideo(const string &path, const string &prefijo) const;

        /**
         * @brief Rebobinar un video. Para rebobinar un video, el fotograma en la posición
         * i se inserta el fotograma de la posición video.size()-i-1(ultima)
         * @param v Video a rebobinar
         * @return Video rebobinado
        */
        Video Rebobinar(const Video &v);

        /**
         * @brief Crear un video con el morphing de dos imágenes. Se calculan tantos fotogramas intermedios como valor tenga
         * nf. El primer fotograma es la imagen I1, el último es la imagen I2, y los intermedios son una interpolación, haciendo
         * uso de la fórmula pixelesInicial[i][j] * (1 - (k / nf) + pixelesFinal[i][j] * (k / nf)
         * @param I1 Primera imagen
         * @param I2 Segunda imagen
         * @param nf Número de fotogramas
         * @pre I1 e I2 tienen que tener el mismo tamaño, y ser formato pgm
         * @return Video con el morphing ya hecho
        */
        Video Morphing (const Image &I1, const Image &I2, int nf);
};

#endif
