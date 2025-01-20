/**
 * @file video.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Video
 *
*/

#include <iostream>
#include <vector>
#include <image.h>
#include <video.h>
#include <cassert>
#include <iomanip>
#include <sys/stat.h>
#include <dirent.h>
#include <cmath>

using namespace std;

int Video::numero = 0;

string obtenerCualquierArchivoDir(const string &path) {

    DIR* directorio = opendir(path.c_str());

    if (directorio == nullptr) {
        std::cerr << "No se pudo abrir el directorio." << std::endl;
    }

    struct dirent* inicio;

    while ((inicio = readdir(directorio)) != nullptr) {
        string archivo = inicio->d_name;

        if (archivo != "." && archivo != "..") {
            closedir(directorio);
            return archivo;
        }
    }

    return "";
}

void obtenerNumero(const string &path) {

    string archivo = obtenerCualquierArchivoDir(path);

    int contador = 0;

    for (char c:archivo) {
        if(isdigit(c)) {
            contador++;
        }
    }

    Video::numero = contador;
}

string obtenerPrefijo(const string &path) {
    size_t pos = path.find_last_of("/");

    if (pos != std::string::npos) {
        return path.substr(pos + 1);
    }

    return path;

}

//1.1: Constructor por defecto (Falta por probar)

Video::Video() {
    video = vector<Image>();
}

//1.2: Constructor de copia (Falta por probar)

Video::Video(const Video &J) {
    assert (this != &J);
    video = J.video;
}

//1.3: Constructor de vídeo a partir de n imagenes vacías (basura)  (Falta por probar)

Video::Video(int n) {
    assert(n >= 0);
    video = vector<Image>(n);
}

//2: Destructor (Falta por probar)

Video::~Video() {
    video.clear();
}

//3: Consultar numero de fotogramas (Falta por probar)

int Video::size() const {
    return video.size();
}

//4: Consultar/Asignar imagen al video  (Falta por probar)

Image &Video::operator[](int foto) {
    assert(0 <= foto && foto < video.size());
    return video[foto];
}

const Image &Video::operator[](int foto) const {
    assert(0 <= foto && foto < video.size());
    return video[foto];
}


//5: Insertar un nuevo fotograma
void Video::Insertar(int k, const Image&I) {
    assert(0 <= k && k < video.size());
    video[k] = I;
}


//6: Borrar fotograma (Falta por probar)

void Video::Borrar(int k) {
    assert(0<=k && k<=video.size());
    video.erase(video.begin()+k);
}

//7: Leer un video en disco

bool Video::LeerVideo(const string &path) {
    int i = 0;
    const string prefijo = obtenerPrefijo(path);

    obtenerNumero(path);

    video.clear();

    while(true) {
        std::ostringstream archivo;
        archivo << path << "/" << prefijo << std::setw(Video::numero) << std::setfill('0') << i << ".pgm";
        // Crear una nueva imagen y cargar el archivo
        Image img;
        if (!img.Load(archivo.str().c_str())) {
            break;
        }

        video.push_back(img);
        i++;
    }

    if (video.empty()) {
        cout << endl << "Error al leer el video, no hay nada a leer. Pruebe a cambiar el directorio de lectura." << endl;
        return false;
    }

    cout << endl << "Lectura exitosa de " <<  path << endl;

    return true;
}


//8: Almacenar un video en disco
bool Video::EscribirVideo(const string &path, const string &prefijo) const {

    bool directorio = mkdir(path.c_str(), 0777);

    if (directorio != 0) {
        cout << endl << "Directorio " << path << " ya existe. Cambie el directorio de escritura." << endl;
        return false;
    }
    else {
        cout << endl << "Directorio " << path << " creado. " << endl << "Escribiendo video..." << endl;
        for (int i = 0; i < video.size(); i++) {
            std::ostringstream archivo;
            archivo << path << "/" << prefijo << std::setw(Video::numero) << std::setfill('0') << i << ".pgm";
            video[i].Save(archivo.str().c_str());
        }

        cout << endl << "Escritura exitosa." << endl;

        return true;
    }
}


//9: Ejercicio 1, Rebobinar
Video Video::Rebobinar(const Video &v) {

    Video videoRebobinado(v.size());

    for (int i = 0; i < v.size(); i++) {
        videoRebobinado.Insertar(i, v[v.size() - i - 1]);
    }

    cout << endl << "EXITO AL REBOBINAR EL VIDEO" << endl;

    return videoRebobinado;
}


//10: Ejercicio 2, Morphing
Video Video::Morphing(const Image &I1, const Image &I2, int nf) {

    Video videoMorphing(nf);
    Image pasoImagen(I1.get_rows(), I1.get_cols());

    //Obtengo pixeles imagen inicial
    vector<vector<int>> pixelesInicial;
    for (int i=0; i<I1.get_rows(); i++) {
        vector<int> fila;
        for (int j=0; j<I1.get_cols(); j++) {
            fila.push_back(I1.get_pixel(i, j));
        }
        pixelesInicial.push_back(fila);
    }

    //Obtengo pixeles imagen final
    vector<vector<int>> pixelesFinal;
    for (int i=0; i<I2.get_rows(); i++) {
        vector<int> fil;
        for (int j=0; j<I2.get_cols(); j++) {
            fil.push_back(I2.get_pixel(i, j));
        }
        pixelesFinal.push_back(fil);

    }

    //Dependiendo del número de saltos, se hará haciendo el suavizado en base a la fórmula
    for (int k=0; k<nf; k++) {

        if (k == 0) {
            videoMorphing.Insertar(k, I1);
        }

        if (k+1 == nf) {
            videoMorphing.Insertar(k, I2);
        }

        if (0<k && k<nf) {

            for (int i=0; i<I1.get_rows(); i++) {
                for (int j=0; j<I1.get_cols(); j++) {
                    float valorInterpolado = pixelesInicial[i][j] * (1.0f - (float)k / nf) + pixelesFinal[i][j] * ((float)k / nf);
                    byte valorFinal = static_cast<byte>(std::round(valorInterpolado));
                    pasoImagen.set_pixel(i, j, valorFinal);
                }
            }

            videoMorphing.Insertar(k, pasoImagen);
        }
    }

    while (nf != 0) {
        nf/=10;
        numero ++;
    }

    cout << endl << "EXITO AL HACER MORPHING" << endl;

    return videoMorphing;
}

