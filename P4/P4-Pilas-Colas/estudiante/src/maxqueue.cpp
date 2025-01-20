#include <iostream>
#include <list>
#include "maxqueue.h"
#include <cassert>

using namespace std;

ostream& operator<<(ostream& os, const element& elem) {
    os << "Value: " << elem.value << ", Max: " << elem.maximum;
    return os;
}

// Constructor por defecto
MaxQueue::MaxQueue() {
    contenedorSubyacente = list<element>();
}

//Constructor de copia
MaxQueue::MaxQueue(const MaxQueue &Q) {
    assert (this!=&Q);
    contenedorSubyacente = Q.contenedorSubyacente;
}

//Destructor
MaxQueue::~MaxQueue() {
    contenedorSubyacente.clear();
}

//Función size
int MaxQueue::size() const  {
    return contenedorSubyacente.size();
}

//Función empty
bool MaxQueue::empty() const {
    return contenedorSubyacente.empty();
}

//Función front
element & MaxQueue::front() {
    if (contenedorSubyacente.empty()) {
        cout << "Error: La cola está vacía." << endl;
        exit(0);
    }
    return contenedorSubyacente.front();
}

//Funcion front constante
const element & MaxQueue::front() const {
    if (contenedorSubyacente.empty()) {
        cout << "Error: La cola está vacía." << endl;
        exit(0);
    }
    return contenedorSubyacente.front();
}

//Función push
void MaxQueue::push(const int &value) {

    int maxActual = value;

    if (contenedorSubyacente.empty()) {
        contenedorSubyacente.push_back({value, maxActual});
    }
    else {

        list<element>::reverse_iterator rit;

        for (rit=contenedorSubyacente.rbegin(); rit!=contenedorSubyacente.rend(); rit++) {

            if (rit->maximum < value) {
                rit->maximum = maxActual;
            }

        }

        contenedorSubyacente.push_back({value, maxActual});
    }

}

//Funcion pop
void MaxQueue::pop() {
    if (contenedorSubyacente.empty()) {
        cout << "Error: La cola está vacía." << endl;
        exit(0);
    }
    contenedorSubyacente.pop_front();
}

void MaxQueue::clear() {
    while(!contenedorSubyacente.empty()) {
        contenedorSubyacente.pop_front();
    }
}

//Funcion swap
void MaxQueue::swap(MaxQueue & c) {
    contenedorSubyacente.swap(c.contenedorSubyacente);
}

