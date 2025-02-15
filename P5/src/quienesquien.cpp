#include "../include/quienesquien.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <QCoreApplication>

QuienEsQuien::QuienEsQuien(){
}

QuienEsQuien::QuienEsQuien(const QuienEsQuien &quienEsQuien){
}

QuienEsQuien& QuienEsQuien::operator= (const QuienEsQuien &quienEsQuien){
     return *this;
}

QuienEsQuien::~QuienEsQuien(){
     this->limpiar() ;
}

void QuienEsQuien::limpiar(){
     this->personajes.clear();
     this->atributos.clear();
     this->personajes_images.clear();
     for(vector<vector<bool>>::iterator it_tablero = this->tablero.begin();
         it_tablero != this->tablero.end();
         it_tablero++){
          (*it_tablero).clear();
     }
     this->tablero.clear();
     this->arbol.clear() ;
}

template <typename T>
std::ostream& operator<<  (std::ostream& out, const std::vector<T>& v) {
     if ( !v.empty() ) {
          out <<  '[' ;
          std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
          out <<  "\b\b]";
     }

     return out;
}

void QuienEsQuien::mostrar_estructuras_leidas(){
     cout <<  "personajes: " <<  (this->personajes) <<  endl;
     cout <<  "atributos: " <<  (this->atributos) <<  endl;
     cout <<  "tablero:    " <<  endl;
     // Escribe la cabecera del tablero
     for(vector<string>::iterator it_atributos = this->atributos.begin() ;
         it_atributos != this->atributos.end() ;
         it_atributos++){
          cout <<  *it_atributos << "\t";
     }
     cout << endl;

     int indice_personaje = 0;
     for(vector<vector<bool>>::iterator it_tablero_atributos = tablero.begin();
         it_tablero_atributos!= tablero.end();
         it_tablero_atributos++){
          string personaje = this->personajes[indice_personaje];
          int indice_atributo = 0;
          for(vector<bool>::iterator it_atributos_personaje = (*it_tablero_atributos).begin();
              it_atributos_personaje != (*it_tablero_atributos).end() ;
              it_atributos_personaje++){
               cout <<  *it_atributos_personaje<< "\t";
               indice_atributo++;
          }
          cout <<  personaje <<  endl;
          indice_personaje++;
     }
}

/**
  * @brief Devuelve una copia de la cadena original sin las subcadenas no deseadas.
  *
  * @param cadena_original Cadena de la que se eliminan las subcadenas no deseadas.
  * @param cadena_a_eliminar Subcadena que se busca y se elimina.
  *
  * @return Copia de la cadena original sin las subcadenas no deseadas.
  */


string limpiar_string(string cadena_original,string cadena_a_eliminar){
     string linea(cadena_original);
     while(linea.find_first_of(cadena_a_eliminar) != std::string::npos){
          linea.erase(linea.find_first_of(cadena_a_eliminar),cadena_a_eliminar.length());
     }

     return linea;
}

istream& operator >>  (istream& is, QuienEsQuien &quienEsQuien) {
     quienEsQuien.limpiar();
     if(is.good()){ //Lee la linea con los nombres de las columnas
          string linea;
          getline(is, linea, '\n');
          linea = limpiar_string(linea,"\r");
          bool salir=false;
          while(!salir && linea.find('\t') != string::npos ){
               string atributo = linea.substr(0,linea.find('\t'));
               quienEsQuien.atributos.push_back(atributo);
               linea = linea.erase(0,linea.find('\t')+1);
               if (linea.substr(0,linea.find('\t'))=="Nombre personaje")
                   salir=true;
          }
     }
     //LEE los atributos para cada personaje
     while( is.good()) {
          string linea;
          getline(is, linea, '\n');
          linea = limpiar_string(linea,"\r");

          //Si la linea contiene algo extrae el personaje.
          //Si no la ignora.
          if(linea != ""){;
               vector<bool> atributos_personaje;
               int indice_atributo=0;
               bool salir=false;
               while(!salir && linea.find('\t') != string::npos){
                   string valor = linea.substr(0,linea.find('\t'));
                   if (valor == "0" || valor == "1"){
                    bool valor_atributo = valor == "1";
                    atributos_personaje.push_back(valor_atributo);
                    linea = linea.erase(0,linea.find('\t')+1) ;
                    indice_atributo++;
                   }
                   else{
                       salir=true;
                   }
               }
               string nombre_personaje;
               string imagen_personaje;
               if (linea.find('\t') == string::npos){
                nombre_personaje = linea;
                imagen_personaje=""; //no tiene imagen
               }
               else{
                nombre_personaje=linea.substr(0,linea.find('\t'));
                linea = linea.erase(0,linea.find('\t')+1) ;
                imagen_personaje=linea;

               }
               quienEsQuien.personajes.push_back(nombre_personaje);
               quienEsQuien.tablero.push_back(atributos_personaje);
               quienEsQuien.personajes_images.push_back(imagen_personaje);
          }
     }

     quienEsQuien.mostrar_estructuras_leidas();
     quienEsQuien.arbol = quienEsQuien.crear_arbol();
     quienEsQuien.tg=nullptr; //puntero al tablero grafico
     quienEsQuien.con=nullptr; //puntero a la consola
     if (quienEsQuien.modo_graph){
        int nper = quienEsQuien.personajes.size();
        int nrows,ncols=3;
        if (nper<8)
           nrows = nper/ncols;
        else{
            ncols=4;
            nrows = nper/ncols;
        }
        //se crea un tablero grafico
        quienEsQuien.tg = new TableroGrafico(400,400,nrows,ncols);
        //ponemos en el tablero grafico las im�genes
        for (int i=0;i<nper;i++){

            quienEsQuien.tg->putImagen(i/ncols,i%ncols,quienEsQuien.personajes_images[i].c_str());
        }
        //creamos la consola
        quienEsQuien.con=new Consola();
     }
     return is;
}

ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien){
     //Escribimos la cabecera, que contiene los atributos y al final una columna para el nombre

     cout<<"NUmero de Atributos "<<quienEsQuien.atributos.size()<<endl;
     for(vector<string>::const_iterator it_atributos = quienEsQuien.atributos.begin();
         it_atributos != quienEsQuien.atributos.end();
         it_atributos++){
          os << *it_atributos << "\t";
     }

     os << "Nombre personaje" << endl;
     
     //Rellenamos con ceros y unos cada linea y al final ponemos el nombre del personaje.
     for(int indice_personaje=0;indice_personaje<quienEsQuien.personajes.size();indice_personaje++){
          for(int indice_atributo=0;indice_atributo<quienEsQuien.atributos.size();indice_atributo++){
               os << quienEsQuien.tablero[indice_personaje][indice_atributo] << "\t";
          }
          os << quienEsQuien.personajes[indice_personaje] << endl;
     }
     
     return os;
}

/**
* @brief Convierte un numero a un vector de bool que corresponde
*        con su representadon en binario con un numero de digitos
*              f i j o.
*
* @param n Numero a convertir en binario.
* @param digitos Numero de digitos de la representaddn binaria.
*
* @return Vector de booleanos con la representadon en binario de @e n
*      con el numero de elementos especificado por @e digitos.
*/
vector<bool> convertir_a_vector_bool(int n, int digitos) {
     vector<bool> ret;
     while(n) {
          if (n&1)
               ret.push_back(true);
          else
               ret.push_back(false);

          n>>=1;
     }

     while(ret.size()<digitos)
          ret.push_back(false);

     reverse(ret.begin(),ret.end());
     return ret;
}


// Función para obtener personajes restantes

int obtenerPersonajesRestantes(vector<bool> personajes_restantes) {
     int restantes=0;

     for (int i=0; i<personajes_restantes.size(); i++) {
          if (personajes_restantes[i] == 1) {
               restantes++;
          }
     }

     return restantes;
}

// Función para obtener personajes restantes que responden que si, y personajes restantes que responden que no

vector<bool> queResponden(vector<bool> personajes_restantes, bool criterio, vector<vector<bool>> tablero, int pos) {

     vector<bool> personajes_restantes_criterio(personajes_restantes.size(), false);

     for (int i=0; i<personajes_restantes.size(); i++) {
          if (tablero[i][pos] == criterio && personajes_restantes[i] == 1) {
               personajes_restantes_criterio[i] = true;
          }
          else {
               personajes_restantes_criterio[i] = false;
          }
     }

     return personajes_restantes_criterio;

}

//PRIMER TIPO DE ARBOL

bintree<Pregunta> QuienEsQuien::crear_arbol_malo(vector<string> atributos,
                                        int indice_atributo,
                                        vector<string> personajes,
                                        vector<bool> personajes_restantes,
                                        vector<vector<bool>> tablero) {

     //Obtengo personajes restantes
     int restantes=0;

     for (int i=0; i<personajes_restantes.size(); i++) {
          if (personajes_restantes[i] == 1) {
               restantes++;
          }
     }

     //Si solo queda un personaje, crear pregunta con atributo = nombre, y número 1, y devolver este árbol
     if (restantes == 1) {
          Pregunta p(personajes[0], 1);
          bintree<Pregunta> hoja(p);
          return hoja;
     }

     //Si no queda ningún personaje, se coloca una hoja a null
     if (restantes == 0){
          bintree<Pregunta> hoja;
          return hoja;
     }

     //Obtengo string pregunta de indice_atributo
     string pregunta = atributos[indice_atributo];

     //Formo con lo anterior la primera pregunta, nodo del árbol
     Pregunta p(pregunta, restantes);

     //Creo el árbol con el nodo con primera pregunta el primer atributo, y personajes restantes TODOS
     bintree<Pregunta> arbolMalo(p);

     //Obtengo personajes que cumplen la anterior pregunta, y aquellos que no la cumplen
     vector<string> personajes_si;
     vector<string> personajes_no;

     //Actualizar personajes restantes si y no
     vector<bool> personajes_restantes_si(personajes_restantes.size(), false);
     vector<bool> personajes_restantes_no(personajes_restantes.size(), false);
     int i=0;
     for (int j=0; j<personajes_restantes.size(); j++) {
          //Si el personaje está activo
          if(personajes_restantes[j]) {
               string personajeActual = personajes[i];
               bool si_o_no = tablero[j][indice_atributo];
               if (si_o_no) {
                    personajes_si.push_back(personajeActual);
                    personajes_restantes_si[j] = true;
               }
               else {
                    personajes_no.push_back(personajeActual);
                    personajes_restantes_no[j] = true;
               }
               i++;
          }
     }

     //Árbol binario con los que si
     bintree<Pregunta> SI = crear_arbol_malo(atributos, indice_atributo+1, personajes_si, personajes_restantes_si, tablero);

     //Árbol binario con los que no
     bintree<Pregunta> NO = crear_arbol_malo(atributos, indice_atributo+1, personajes_no, personajes_restantes_no, tablero);

     //Inserto arbol SI como hijo a la izquierda de arbolMalo, y arbol NO como hijo a la derecha
     arbolMalo.insert_left(arbolMalo.root(), SI);
     arbolMalo.insert_right(arbolMalo.root(), NO);

     return arbolMalo;

}

//SEGUNDO TIPO DE ARBOL (se construye a partir del primero)

void QuienEsQuien::crear_arbol_medio(bintree<Pregunta> &arbol_malo, bintree<Pregunta>::node nodoRaiz) {

     if (nodoRaiz.null() || (*nodoRaiz).es_personaje()) {
          return;
     }

     //Recorro recursivamente el árbol por la derecha y la izquierda
     if(!nodoRaiz.left().null()) {
          crear_arbol_medio(arbol_malo, nodoRaiz.left());
     }
     if(!nodoRaiz.right().null()) {
          crear_arbol_medio(arbol_malo, nodoRaiz.right());
     }

     if (nodoRaiz.left().null()) {
          bintree<Pregunta> arbolito;
          arbol_malo.prune_right(nodoRaiz, arbolito);
          //Si nos encontramos en la raiz, caso especial, debido a que siempre el padre del root es NULL
          if(arbol_malo.root() == nodoRaiz) {
               //En este caso
               arbol_malo = arbolito;
          }
          else {
               //Obtengo el abuelo e inserto a la derecha o a la izquierda, depende de dónde nos encontremos
               if (nodoRaiz.parent().left() == nodoRaiz) {
                    arbol_malo.insert_left(nodoRaiz.parent(), arbolito);
               }
               else {
                    arbol_malo.insert_right(nodoRaiz.parent(), arbolito);
               }
          }
     }

     //SEGUNDO CASO, NO TIENE HIJO A LA DERECHA -> Insertar el hijo izquierdo como nuevo papa
     else if (nodoRaiz.right().null()) {
          bintree<Pregunta> arbolito;
          arbol_malo.prune_left(nodoRaiz, arbolito);
          //Si nos encontramos en la raiz, caso especial, debido a que siempre el padre del root es NULL
          if(arbol_malo.root() == nodoRaiz) {
               arbol_malo = arbolito;
          }
          else {
               //Obtengo el abuelo e inserto a su derecha el arbol podado
               if (nodoRaiz.parent().left() == nodoRaiz) {
                    arbol_malo.insert_left(nodoRaiz.parent(), arbolito);
               }
               else {
                    arbol_malo.insert_right(nodoRaiz.parent(), arbolito);
               }
          }
     }

}

//Función para obtener la posición del atributo en el vector de atributos con mayor entropia

int obtenerPosGini(vector<vector<bool>> tablero, vector<string> atributos, vector<bool> personajes_restantes) {

     int posMaxGini = -1;

     double personajesRestantes = 0;
     for (int i=0; i<personajes_restantes.size(); i++) {
          if (personajes_restantes[i] != 0) {
               personajesRestantes+=1;
          }
     }

     double entropiaMax = -1;
     for (int i=0; i<atributos.size(); i++) {

          if (atributos[i] == "usado") {
               continue;
          }

          double si = 0;
          double no = 0;
          double p_si = 0;
          double p_no = 0;
          double entropiaActual = 0;

          for (int j=0; j<personajes_restantes.size(); j++) {

               if (personajes_restantes[j] == 0) {
                    continue;
               }

               if (tablero[j][i] == 0) {
                    no+=1;
               }
               else {
                    si+=1;
               }

          }

          p_si = si / personajesRestantes;
          p_no = no / personajesRestantes;

          entropiaActual = - (p_no * log2(p_no) + p_si * log2(p_si));

          if (entropiaActual > entropiaMax) {
               entropiaMax = entropiaActual;
               posMaxGini = i;
          }

     }

     return posMaxGini;

}



//TERCER TIPO DE ARBOL (Usando gini, el mejor)

bintree<Pregunta> QuienEsQuien::crear_arbol_bueno(vector<string> atributos,
                                        vector<string> personajes,
                                        vector<bool> personajes_restantes,
                                        vector<vector<bool>> tablero) {

     //Obtengo personajes restantes
     int restantes = obtenerPersonajesRestantes(personajes_restantes);

     //Criterio de parada, solo queda un personaje
     //Si solo queda un personaje, crear pregunta con atributo = nombre, y número 1, y devolver este árbol
     if (restantes == 1) {
          string nombre;
          for (int i=0; i<personajes_restantes.size(); i++) {
               if (personajes_restantes[i] == 1) {
                    nombre = personajes[i];
                    break;
               }
          }
          Pregunta p(nombre, 1);
          bintree<Pregunta> hoja(p);
          return hoja;
     }

     //Si no queda ningún personaje, se coloca una hoja a null
     if (restantes == 0){
          bintree<Pregunta> hoja;
          return hoja;
     }

     //Obtengo la posición en el vector de atributos del atributo con mayor entropía
     int pos = obtenerPosGini(tablero, atributos, personajes_restantes);

     //Creo una pregunta con ese atributo, y lo marco cómo usado, no lo volveré a usar
     string pregunta = atributos[pos];
     Pregunta p(pregunta, restantes);
     atributos[pos] = "usado";

     //Creo el árbol con la pregunta correspondiente
     bintree<Pregunta> arbolBueno(p);

     //Actualizo personajes que responden si, y personajes que responden no en vector de booleanos
     vector<bool> personajes_restantes_si = queResponden(personajes_restantes, true, tablero, pos);
     vector<bool> personajes_restantes_no = queResponden(personajes_restantes, false, tablero, pos);

     //Llamada recursiva a los que si, y a los que no
     bintree<Pregunta> SI = crear_arbol_bueno(atributos, personajes, personajes_restantes_si, tablero);
     bintree<Pregunta> NO = crear_arbol_bueno(atributos, personajes, personajes_restantes_no, tablero);

     //Inserto arbol SI como hijo a la izquierda de arbol, y arbol NO como hijo a la derecha
     arbolBueno.insert_left(arbolBueno.root(), SI);
     arbolBueno.insert_right(arbolBueno.root(), NO);

     //Devuelvo el árbol
     return arbolBueno;

}

/**
* @brief Esta es una propuesta de cabecera de la funcion para crear el arbol.
*/
bintree<Pregunta> QuienEsQuien::crear_arbol( vector<string> atributos,
                                             int indice_atributo,
                                             vector<string> personajes,
                                             vector<bool> personajes_restantes,
                                             vector<vector<bool>> tablero){

     //TODO :D:D

     //Creación arbol Malo
     //arbol = crear_arbol_malo(atributos, indice_atributo, personajes, personajes_restantes, tablero);

     //Creación arbol Bueno (Gini)
     arbol = crear_arbol_bueno(atributos, personajes, personajes_restantes, tablero);

     return arbol;
}

bintree<Pregunta> QuienEsQuien::crear_arbol(){
     int indice_atributo = 0;
     vector<bool> personajes_restantes;
     for(vector<string>::iterator it = personajes.begin();it!=personajes.end();it++){
          personajes_restantes.push_back(true);
     }

     return crear_arbol( this->atributos, indice_atributo, this->personajes,
                         personajes_restantes, this->tablero);
}

void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){
     arbol = arbol_nuevo;
}

void QuienEsQuien::iniciar_juego(){
     //TODO :D:D
     std::cout << "Antes de Ventana" << std::endl;
     Ventana v(tg, con, "WisW");
     std::cout << "Después de Ventana" << std::endl;
     v.show();

     bintree<Pregunta>::node jugada_actual = arbol.root();
     string respuesta;

     if (modo_graph){
          std::cout << "entro en if" << std::endl;
          v.show();
          std::cout << "salgo if" << std::endl;
     }

     while (!jugada_actual.left().null() || !jugada_actual.right().null()){

          cout << "Personajes no descartados: " << endl;
          set<string> info = informacion_jugada(jugada_actual);
          set<string>::iterator it;
          cout << "[ " ;
          for (it=info.begin(); it!=info.end(); it++) {
               cout << *it << " " ;
          }
          cout << " ]" << endl;

          cout << endl;
          cout << preguntas_formuladas(jugada_actual) << endl;
          cout << endl;

          cout << "Su personaje tiene: " << (*jugada_actual).obtener_pregunta() << endl;
          cout << "Escriba aquí su respuesta (si/no): ";
          cin >> respuesta;
          cout << endl;

          if (respuesta == "si"){
               jugada_actual = jugada_actual.left();
          }
          else if (respuesta == "no"){
               jugada_actual = jugada_actual.right();
          }
          else {
               cout << "Respuesta no válida" << endl;
          }

     }

     cout << "Su personajes es: " << (*jugada_actual).obtener_personaje() << endl;
    
    if (modo_graph){
     con->WriteText("Cuando completes QuienEsQuien, este mensaje lo podr�s quitar");
     char c;
     do{
        con->WriteText("Pulsa 0 para salir");
	c = con->ReadChar();
     
     }while (c!='0');
     
    }
    v.cerrar();
}	

set<string> QuienEsQuien::informacion_jugada(bintree<Pregunta>::node jugada_actual){
     //TODO :)
     set<string> personajes_levantados;
     set<string>::iterator it;

     if (jugada_actual.null()) {
          return {};
     }

     if ((*jugada_actual).es_personaje()) {
          personajes_levantados.insert((*jugada_actual).obtener_personaje());
          return personajes_levantados;
     }

     set<string> personajes_levantados_izq = informacion_jugada(jugada_actual.left());
     set<string> personajes_levantados_der = informacion_jugada(jugada_actual.right());

     for (it = personajes_levantados_izq.begin(); it != personajes_levantados_izq.end(); ++it) {
          personajes_levantados.insert(*it);
     }

     for (it = personajes_levantados_der.begin(); it != personajes_levantados_der.end(); ++it) {
          personajes_levantados.insert(*it);
     }

     return personajes_levantados;
}

void escribir_esquema_arbol(ostream& ss, const bintree <Pregunta>& a,
                            bintree<Pregunta>::node n, string& pre){
     if (n.null())
          ss <<  pre <<  "-- x" <<  endl;
     else {
          ss <<  pre <<  "-- " <<  (*n) <<  endl;
          if ( !n.right().null() || !n.left().null()) {// Si no es una hoja
               pre += "   |";
               escribir_esquema_arbol(ss,a, n.right(), pre);
               pre.replace(pre.size()-4, 4, "    ");
               escribir_esquema_arbol (ss,a, n.left(), pre);
               pre.erase(pre.size()-4, 4);
          }
     }
}

void QuienEsQuien::escribir_arbol_completo() const{
     string pre = "";
     escribir_esquema_arbol(cout,this->arbol,this->arbol.root(),pre);
}

void QuienEsQuien::eliminar_nodos_redundantes(){
// TODO :)

     bintree<Pregunta>::node nodoRaiz = arbol.root();

     //Llamar a mi función crear arbol medio
     crear_arbol_medio(arbol, nodoRaiz);


}

vector<int> QuienEsQuien::profundidades_hojas(const bintree<Pregunta>::node& jugada_actual) const{
     vector<int> profundidades;

     if (jugada_actual.null()) {
          return {};
     }

     if (jugada_actual.left().null() && jugada_actual.right().null()) {
          profundidades.push_back(0);
     }else {

          vector<int> profundidades_izq = profundidades_hojas(jugada_actual.left());
          vector<int> profundidades_der = profundidades_hojas(jugada_actual.right());

          for (int i=0; i<profundidades_izq.size(); i++) {
               profundidades.push_back(profundidades_izq[i]+1);
          }

          for (int i=0; i<profundidades_der.size(); i++) {
               profundidades.push_back(profundidades_der[i]+1);
          }

     }

     return profundidades;
}
float QuienEsQuien::profundidad_promedio_hojas(){

     bintree<Pregunta>::node jugada_actual = arbol.root();

     vector<int> profundidades = profundidades_hojas(jugada_actual);

     float suma = 0;
     float media = 0;

     for (int i = 0; i < profundidades.size(); i++) {
          suma += profundidades[i];
     }

     media = suma / profundidades.size();

     return media;
}

/**
* @brief Genera numero enteros positivos aleatorios en el rango [min,max].
**/
int generaEntero(int min, int max){
     int tam= max-min;
     return ((rand( )%tam)+min) ;
}

void QuienEsQuien::tablero_aleatorio(int numero_de_personajes){
     srand(0);
     this->limpiar();
     float log_2_numero_de_personajes = log(numero_de_personajes)/log(2);
     int numero_de_atributos = ceil(log_2_numero_de_personajes);

     cout <<  "Peticion para generar " <<  numero_de_personajes << " personajes ";
     cout <<  "con " << numero_de_atributos <<  " atributos" << endl;
     cout <<  "Paso 1: generar " <<  pow(2, numero_de_atributos) <<  " personajes" << endl;

     //Fase 1: completar el tablero con todos los personajes posibles
     //Complete el tablero y los nombres de personajes a la vez
     for(int indice_personaje=0;indice_personaje< pow(2,numero_de_atributos);indice_personaje++){
          vector<bool> atributos_personaje =
                                    convertir_a_vector_bool(indice_personaje,numero_de_atributos);
          string nombre_personaje = "Personaje_"+to_string(indice_personaje);

          this->personajes.push_back(nombre_personaje);
          this->tablero.push_back(atributos_personaje);
     }

     // Completo los nombres de los atributos.
     for( int indice_atributo=0;indice_atributo<numero_de_atributos;indice_atributo++){
          string nombre_atributo = "Atributo_"+to_string(indice_atributo);
          this->atributos.push_back(nombre_atributo);
     }
     cout <<  "Paso 2: eliminar " << (pow(2,numero_de_atributos)-numero_de_personajes) <<  "personajes" << endl;

     //Fase 2. Borrar personajes aleatoriamente hasta que quedan solo los que hemos pedido.
     while(personajes.size()>numero_de_personajes){
          int personaje_a_eliminar = generaEntero(0,personajes.size());
          personajes.erase(personajes.begin()+personaje_a_eliminar);
          tablero.erase(tablero.begin()+personaje_a_eliminar);
     }
}
void QuienEsQuien::ocultar_personajes_graph(const set<string> &personajes_activos){
    //ocultamos los personajes
    int idx=0;
    int ncols=tg->getNcols();
    for (auto it=personajes.begin();it!=personajes.end();++it,idx++){
        if ( personajes_activos.find(*it)==personajes_activos.end())
            tg->putImagen(idx/ncols,idx%ncols,imagen_ocultar.c_str());
    }
}


void QuienEsQuien::setImagenOcultar(const char * n){
    imagen_ocultar=n;
}

void QuienEsQuien::setModoGraph(bool m){
    modo_graph=m;
}

//Añadido por mí!

int obtenerPosNombre(vector<string> personajes, string nombre) {
     int pos = 0;
     for (int i=0; i<personajes.size(); i++) {
          if (personajes[i] == nombre) {
               pos = i;
               break;
          }
     }

     return pos;
}


// METODO ADICIONAL 1

string QuienEsQuien::preguntas_formuladas(bintree<Pregunta>::node jugada) {

     string respuesta = "El personaje oculto tiene las siguientes características: \n";
     //Si el padre de la jugada es null, quiere decir que aún no se han formulado preguntas
     if(jugada.parent().null()) {
          respuesta = "Aún no se ha dado ninguna respuesta.";
     }

     bintree<Pregunta>::node nodoActual = jugada;

     //En caso contrario, se va subiendo desde el nodo de la jugada, y se busca dónde está
     while(nodoActual != arbol.root()) {

          if (nodoActual.parent().left() == nodoActual) {
               respuesta = respuesta + (*nodoActual.parent()).obtener_pregunta() + " - si" + "\n";
          }
          if (nodoActual.parent().right() == nodoActual) {
               respuesta = respuesta + (*nodoActual.parent()).obtener_pregunta() + " - no" + "\n";
          }

          nodoActual = nodoActual.parent();
     }

     if ((*jugada).es_personaje()) {
          respuesta = respuesta + "¡¡Personaje encontrado!!: " + (*jugada).obtener_personaje();
     }
     else {
          respuesta = respuesta + "El personaje aún no se ha encontrado";;
     }

     return respuesta;

}

// METODO 2

void QuienEsQuien::aniade_personaje(string nombre, vector<bool> caracteristicas, string nombre_imagen_personaje) {

     bintree<Pregunta>::node nodoActual = arbol.root();
     vector<string> usados;

     for (int i=0; i<caracteristicas.size(); i++) {
          usados.push_back("nousado");
     }

     while (!(*nodoActual).es_personaje()) {

          string preguntaActual = (*nodoActual).obtener_pregunta();
          int posCaracteristica = 0;

          for (int i=0; i<atributos.size(); i++) {
               if (atributos[i] == preguntaActual) {
                    posCaracteristica = i;
                    break;
               }
          }

          if (caracteristicas[posCaracteristica] == 1) {
               nodoActual = nodoActual.left();
          }
          else {
               nodoActual = nodoActual.right();
          }

          usados[posCaracteristica] = "usado";

     }

     if ((*nodoActual).es_personaje()) {

          bintree<Pregunta> arbolito;
          string preguntaDifiere="";
          int respuestaNuevo = 0;
          //Posición actual personaje hoja
          int posHoja = obtenerPosNombre(personajes, (*nodoActual).obtener_personaje());
          //Busco pregunta con la que difieren ambos personajes
          for (int i=0; i<caracteristicas.size(); i++) {
               if(usados[i]!="usado") {
                    if(caracteristicas[i]!=tablero[posHoja][i]) {
                         preguntaDifiere = atributos[i];
                         respuestaNuevo = caracteristicas[i];
                         break;
                    }
               }
          }

          Pregunta preguntita(preguntaDifiere, 2);
          bintree<Pregunta>::node nodoPapa = nodoActual.parent();

          if (nodoActual.parent().left() == nodoActual) {
              arbol.prune_left(nodoActual.parent(), arbolito);
               arbol.insert_left(nodoPapa, preguntita);

          }
          else {
               arbol.prune_right(nodoActual.parent(), arbolito);
               arbol.insert_right(nodoPapa, preguntita);
          }

          Pregunta uno(nombre, 1);
          Pregunta dos(personajes[posHoja], 1);

          if (nodoPapa.parent().left() == nodoPapa) {
               if (respuestaNuevo == 1) {
                    arbol.insert_left(nodoPapa.left(), uno);
                    arbol.insert_right(nodoPapa.left(), dos);
               }
               else if (respuestaNuevo == 0) {
                    arbol.insert_right(nodoPapa.left(), uno);
                    arbol.insert_left(nodoPapa.left(), dos);
               }
          }
          else {
               if (respuestaNuevo == 1) {
                    arbol.insert_left(nodoPapa.right(), uno);
                    arbol.insert_right(nodoPapa.right(), dos);
               }
               else if (respuestaNuevo == 0) {
                    arbol.insert_right(nodoPapa.right(), uno);
                    arbol.insert_left(nodoPapa.right(), dos);
               }
          }


          //ACTUALIZAR TABLERO, PERSONAJES, IMAGENES...
          personajes_images.push_back(nombre_imagen_personaje);
          personajes.push_back(nombre);
          tablero.push_back(caracteristicas);

     }
}



// METODO ADICIONAL 3

void QuienEsQuien::elimina_personaje(string nombre) {

     //¿En que posición está nombre?
     int pos = 0;
     for (int i=0; i<personajes.size(); i++) {
         if (personajes[i] == nombre) {
              pos = i;
              break;
         }
     }

     // ¿Qué características tiene nombre en el tablero?
     vector<bool> caracteristicas;
     for (int j=0; j<atributos.size(); j++) {
          caracteristicas.push_back(tablero[pos][j]);
     }

     //Obtengo la raiz del árbol
     bintree<Pregunta>::node nodo = arbol.root();

     //Mientras que el nodo no sea hoja, ni hijo izd ni hijo drcha null, recorremos el árbol
     //Uso k para llevar cuenta del vector de caracteristicas
     int k = 0;
     int valorUltimaCaracteristica = 0;
     while (!(nodo.left().null() && nodo.right().null()) && k<caracteristicas.size()){

          //Obtengo la posición del atributo por el que se está preguntando en el vector de atributos
          int PosAtributo=0;
          for (int i=0; i<atributos.size(); i++) {
               if (atributos[i] == (*nodo).obtener_pregunta()) {
                    PosAtributo = i;
                    break;
               }
          }

          if (caracteristicas[PosAtributo] == 1) {
               nodo = nodo.left();
          }
          else {
               nodo = nodo.right();
          }

          valorUltimaCaracteristica = caracteristicas[k];

          k++;

     }

     //En el momento que sale del bucle while, tenemos almacenada la hoja
     //Si la ultima característica leida es 1, la hoja es hijo Izd. Si es 0, la hoja es hijo Dcha.
     if (nodo.parent().left() == nodo) {
          bintree<Pregunta>::node abuelo = nodo.parent().parent();
          //Podo lo que hay a la derecha del padre
          bintree<Pregunta> arbolito;
          arbol.prune_right(nodo.parent(), arbolito);
          //Si el padre es hijo izd del abuelo, asignamos lo podado a la izd del abuelo
          //Si es hijo dcha, a la derecha
          if (abuelo.left() == nodo.parent()) {
               arbol.insert_left(abuelo, arbolito);
          }
          else {
               arbol.insert_right(abuelo, arbolito);
          }
     }

     if (nodo.parent().right() == nodo) {
          bintree<Pregunta>::node abuelo = nodo.parent().parent();
          //Podo lo que hay a la derecha del padre
          bintree<Pregunta> arbolito;
          arbol.prune_left(nodo.parent(), arbolito);
          //Si el padre es hijo izd del abuelo, asignamos lo podado a la izd del abuelo
          //Si es hijo dcha, a la derecha
          if (abuelo.left() == nodo.parent()) {
               arbol.insert_left(abuelo, arbolito);
          }
          else {
               arbol.insert_right(abuelo, arbolito);
          }
     }

     //Elimino nombre del vector de personajes y del tablero
     personajes.erase(personajes.begin() + pos);
     for (int i=0; i<atributos.size(); i++) {
          tablero[pos].erase(tablero[pos].begin() + i);
     }

     for (int i=0; i<personajes.size(); i++) {
          cout << personajes[i]<<endl;
     }

}

