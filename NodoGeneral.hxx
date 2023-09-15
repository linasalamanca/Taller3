#include "NodoGeneral.h"
#include <list>

template<class T>
NodoGeneral<T>::NodoGeneral(){
    this->desc.clear();
}

template<class T>
NodoGeneral<T>::~NodoGeneral(){
    typename std::list<NodoGeneral<T>*>::iterator it;
    for(it = this->desc.begin(); it != this->desc.end(); it++){
        delete *it;
    }
    this->desc.clear();
}

template<class T>
T& NodoGeneral<T>::obtenerDato(){
    return this->dato;
}

template<class T>
void NodoGeneral<T>::fijarDato(T& val){
    this->dato = val;
}

template<class T>
void NodoGeneral<T>::limpiarLista(){
    typename std::list<NodoGeneral<T>*>::iterator it;
    for(it = this->desc.begin(); it != this->desc.end(); it++){
        delete *it;
    }
    this->desc.clear();
}

template<class T>
void NodoGeneral<T>::adicionarDesc(T& nval){
    NodoGeneral<T> *nodo = new NodoGeneral<T>;
    nodo->fijarDato(nval);
    this->desc.push_back(nodo);
}

template<class T>
bool NodoGeneral<T>::eliminarDesc(T& val){
    typename std::list<NodoGeneral<T>*>::iterator it;
    for(it = this->desc.begin(); it != this->desc.end(); it++){
        if((*it)->obtenerDato() == val){
            delete *it;
            this->desc.erase(it);
            return true;
        }
    }
    return false;
}
