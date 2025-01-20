#include <iostream>
#include <queue>
#include "maxstack.h"
#include <cassert>

using namespace std;

MaxStack::MaxStack() {
    contenedorValores = queue<int>();
    contenedorMaximos = priority_queue<int>();
    elemento = {0,0};
}

MaxStack::MaxStack(const MaxStack &S) {
    assert (this!=&S);
    contenedorValores = S.contenedorValores;
    contenedorMaximos = S.contenedorMaximos;
    elemento = S.elemento;
}

MaxStack::~MaxStack() {
    contenedorValores = queue<int>();
    contenedorMaximos = priority_queue<int>();
}

bool MaxStack::empty() const {
    return contenedorValores.empty();
}

void MaxStack::clear() {
    while (!contenedorValores.empty()) {
        contenedorValores.pop();
    }
    while (!contenedorMaximos.empty()) {
        contenedorMaximos.pop();
    }
}

void MaxStack::swap(MaxStack &S) {
    contenedorValores.swap(S.contenedorValores);
    contenedorMaximos.swap(S.contenedorMaximos);
}

element& MaxStack::top() {

    if (contenedorValores.empty() && contenedorMaximos.empty()) {
        cout << "Error: La pila está vacía." << endl;
        exit(0);
    }

    elemento.value = contenedorValores.front();
    elemento.maximum = contenedorMaximos.top();

    return elemento;
}

const element& MaxStack::top() const {

    if (contenedorValores.empty() && contenedorMaximos.empty()) {
        cout << "Error: La pila está vacía." << endl;
        exit(0);
    }

    int valor = contenedorValores.front();
    int maximo = contenedorMaximos.top();

    return {valor,maximo};
}


void MaxStack::push(const int &value) {

   queue<int> aux;

    while(!contenedorValores.empty()){
        aux.push(contenedorValores.front());
        contenedorValores.pop();
    }

    contenedorValores.push(value);

    while(!aux.empty()) {
        contenedorValores.push(aux.front());
        aux.pop();
    }

    if (contenedorMaximos.empty()){
        contenedorMaximos.push(value);
    } else if (value > contenedorMaximos.top()) {
        contenedorMaximos.push(value);
    }
}


void MaxStack::pop() {

    if (contenedorValores.empty() && contenedorMaximos.empty()) {
        cout << "Error: La pila está vacía." << endl;
        exit(0);
    }

    if (contenedorValores.front() == contenedorMaximos.top()) {
        contenedorMaximos.pop();
    }
    contenedorValores.pop();
}

int MaxStack::size() const {
    return contenedorValores.size();
}








