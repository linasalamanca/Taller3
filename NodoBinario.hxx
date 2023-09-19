#include "NodoBinario.h"

template<class T>
NodoBinario<T>::NodoBinario() {
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
}

template<class T>
NodoBinario<T>::NodoBinario(T val) {
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
    this->dato = val;
}

template<class T>
NodoBinario<T>::~NodoBinario() {
    if(this->hijoIzq != nullptr){
        delete this->hijoIzq;
        this->hijoIzq = nullptr;
    }
    if(this->hijoDer != nullptr){
        delete this->hijoDer;
        this->hijoDer = nullptr;
    }
}

template<class T>
T NodoBinario<T>::obtenerDato() {
    return this->dato;
}

template<class T>
void NodoBinario<T>::fijarDato(T val) {
    this->dato = val;
}

template<class T>
NodoBinario<T>* NodoBinario<T>::obtenerHijoIzq() {
    return this->hijoIzq;
}

template<class T>
NodoBinario<T>* NodoBinario<T>::obtenerHijoDer() {
    return this->hijoDer;
}

template<class T>
void NodoBinario<T>::fijarHijoIzq(NodoBinario<T>* izq) {
    this->hijoIzq = izq;
}

template<class T>
void NodoBinario<T>::fijarHijoDer(NodoBinario<T>* der) {
    this->hijoDer = der;
}

template<class T>
bool NodoBinario<T>::esHoja(){
    return (this->hijoIzq == nullptr && this->hijoDer == nullptr);
}
