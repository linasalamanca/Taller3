#include "ArbolBinarioOrdenado.h"
#include "NodoBinario.h"
#include <queue>
#include <iostream>

template< class T >
ArbolBinarioOrdenado<T>::ArbolBinarioOrdenado(){
    this->raiz = nullptr;
}

template< class T >
ArbolBinarioOrdenado<T>::~ArbolBinarioOrdenado(){
    if(this->raiz != nullptr){
        delete this->raiz;
        this->raiz = nullptr;
    }

}

template< class T >
bool ArbolBinarioOrdenado<T>::esVacio(){
    return this->raiz==nullptr;
}

template< class T >
T ArbolBinarioOrdenado<T>::datoRaiz(){
    return (this->raiz)->obtenerDato();
}
//recurrente
template< class T >
int ArbolBinarioOrdenado<T>::altura(){
    if(this->esVacio())
        return -1;
    else
        return this-> altura(this->raiz);
}

template< class T >
int ArbolBinarioOrdenado<T>::altura(NodoBinario<T>* nodo){
    int valt;

    if(nodo->esHoja()){
        valt = 0;
    }else{
        int valt_izq = -1;
        int valt_der = -1;

        if(nodo->obtenerHijoIzq() != nullptr)
            valt_izq = this -> altura(nodo->obtenerHijoIzq());
        if(nodo->obtenerHijoDer() != nullptr)
            valt_der = this -> altura(nodo->obtenerHijoDer());
        if(valt_izq > valt_der)
            valt = valt_izq +  1;
        else
            valt = valt_der + 1;
    }

    return valt;
}
//recurrente
template<class T>
int ArbolBinarioOrdenado<T>::tamano() {
    return tamano(this->raiz);
}

template<class T>
int ArbolBinarioOrdenado<T>::tamano(NodoBinario<T>* nodo) {
    if (nodo == nullptr) {
        return -1;
    } else {
        return 1 + tamano(nodo->obtenerHijoIzq()) + tamano(nodo->obtenerHijoDer());
    }
}

//iterativa
template< class T >
bool ArbolBinarioOrdenado<T>::insertar(T val){
    NodoBinario<T>* nodo = this->raiz;
    NodoBinario<T>* padre = this->raiz;
    bool insertado = false;
    bool duplicado = false;

    while (nodo!=nullptr){
        padre = nodo;
        if(val < nodo->obtenerDato()){
            nodo = nodo->obtenerHijoIzq();
        } else if(val > nodo->obtenerDato()){
            nodo = nodo->obtenerHijoDer();
        }else{
            duplicado = true;
            break;
        }
    }

    if(!duplicado){
        NodoBinario<T>* nuevo = new NodoBinario<T>(val);
        if(nuevo!=nullptr){
            if(val < padre->obtenerDato())
                padre->fijarHijoIzq(nuevo);
            else
                padre->fijarHijoDer(nuevo);
        }
        insertado = true;
    }
    return insertado;
}
//iterativa
/*template< class T >
ArbolBinarioOrdenado<T>::eliminar(T val){
    //comparar con dato en nodo para bajar por izquierda o derecha
    //y para saber si val está en el árbol

    //Si val está en el árbol y ya baje
    //verificar situación de eliminación
    //1. Nodo hoja, borrarlo
    //2. Nodo con un solo hijo, usar hijo para reemplazar nodo
    //3. Nodo con dos hijos, usar elmaximo del subarbol izquierdo
    //   para reemplazazr nodo
}*/

template<class T>
bool ArbolBinarioOrdenado<T>::eliminar(T val) {
    NodoBinario<T>* nodo = this->raiz;
    NodoBinario<T>* padre = this->raiz;

    while (nodo != nullptr && nodo->obtenerDato() != val) {
        padre = nodo;
        if (val < nodo->obtenerDato())
            nodo = nodo->obtenerHijoIzq();
        else
            nodo = nodo->obtenerHijoDer();
    }

    if (nodo == nullptr) {
        return false;
    }

    //3. Nodo con dos hijos, usar elmaximo del subarbol izquierdo
    //   para reemplazazr nodo
    if (nodo->obtenerHijoIzq() != nullptr && nodo->obtenerHijoDer() != nullptr) {
        NodoBinario<T>* sucesor = nodo->obtenerHijoDer();
        NodoBinario<T>* sucesorPadre = nodo;

        while (sucesor->obtenerHijoIzq() != nullptr) {
            sucesorPadre = sucesor;
            sucesor = sucesor->obtenerHijoIzq();
        }

        nodo->fijarDato(sucesor->obtenerDato());

        nodo = sucesor;
        padre = sucesorPadre;
    }

   //2. Nodo con un solo hijo, usar hijo para reemplazar nodo
    NodoBinario<T>* hijo;
    if (nodo->obtenerHijoIzq() != nullptr) {
        hijo = nodo->obtenerHijoIzq();
    } else {
        hijo = nodo->obtenerHijoDer();
    }

    // 1. Nodo hoja, borrarlo
    if (padre == nullptr) {
        this->raiz = hijo;
    } else {
        if (nodo == padre->obtenerHijoIzq())
            padre->fijarLeft(hijo);
        else
            padre->fijarRight(hijo);
    }

    delete nodo;
    return true;
}

//iterativa
template< class T >
bool ArbolBinarioOrdenado<T>::buscar(T val){
    NodoBinario<T>* nodo = this->raiz;
    bool encontrado = false;

    while (nodo!=nullptr && !encontrado){
        if(val < nodo->obtenerDato()){
            nodo = nodo->obtenerHijoIzq();
        } else if(val > nodo->obtenerDato()){
            nodo = nodo->obtenerHijoDer();
        }else{
            encontrado = true;
        }
    }

    return encontrado;
}
//recurrente
template< class T >
void ArbolBinarioOrdenado<T>::preOrden(NodoBinario<T>* nodo){
    if(nodo!=nullptr){
        std::cout << nodo->obtenerDato()<<" ";
        this->preOrden(nodo->obtenerHijoIzq());
        this->preOrden(nodo->obtenerHijoDer());
    }

}
//recurrente
template< class T >
void ArbolBinarioOrdenado<T>::inOrden(){
    if(!this->esVacio())
        this->inOrden(this->raiz);
}

template< class T >
void ArbolBinarioOrdenado<T>::inOrden(NodoBinario<T>* nodo){
    if(nodo!=nullptr){
        this->inOrden(nodo->obtenerHijoIzq());
        std::cout << nodo->obtenerDato()<<" ";
        this->inOrden(nodo->obtenerHijoDer());
    }
}
//Recurrente
template< class T >
void ArbolBinarioOrdenado<T>::posOrden(NodoBinario<T>* nodo){
    if(nodo!=nullptr){
        this->posOrden(nodo->obtenerHijoIzq());
        this->posOrden(nodo->obtenerHijoDer());
        std::cout << nodo->obtenerDato()<<" ";
    }

}
//iterativo
template< class T >
void ArbolBinarioOrdenado<T>::nivelOrden(){
    if(!this->esVacio()){
        std::queue<NodoBinario<T>*>cola;
        cola.push(this->raiz);
        NodoBinario<T>* nodo;
        while(!cola.empty()){
            nodo = cola.front();
            cola.pop();
            std::cout<< nodo->obtenerDato() << " ";
            if(nodo->obtenerHijoIzq != nullptr){
                cola.push(nodo->obtenerHijoIzq());
            }
            if(nodo->obtenerHijoDer != nullptr){
                cola.push(nodo->obtenerHijoDer());
            }
        }
    }
}

