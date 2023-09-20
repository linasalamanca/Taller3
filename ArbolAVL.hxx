#include "ArbolAVL.h"
#include "NodoBinario.h"
#include <queue>
#include <iostream>

template< class T >
ArbolAVL<T>::ArbolAVL(){
    this->raiz = NULL;
}

template< class T >
ArbolAVL<T>::~ArbolAVL(){
    if(this->raiz != NULL){
        delete this->raiz;
        this->raiz = NULL;
    }

}
template< class T >

bool ArbolAVL<T>::esVacio(){
    return this->raiz==NULL;
}

template< class T >
T ArbolAVL<T>::datoRaiz(){
    return (this->raiz)->obtenerDato();
}
//recurrente
template< class T >
int ArbolAVL<T>::altura(){
    if(this->esVacio())
        return -1;
    else
        return this-> altura(this->raiz);
}

template< class T >
int ArbolAVL<T>::altura(NodoBinario<T>* nodo) {
    int valt;

    if (nodo->esHoja()) {
        valt = 0;
    } else {
        int valt_izq = -1;
        int valt_der = -1;

        if (nodo->obtenerHijoIzq() != NULL)
            valt_izq = this->altura(nodo->obtenerHijoIzq());
        if (nodo->obtenerHijoDer() != NULL)
            valt_der = this->altura(nodo->obtenerHijoDer());
        if (valt_izq > valt_der)
            valt = valt_izq + 1;
        else
            valt = valt_der + 1;
    }

    return valt;
}
//recurrente
template<class T>
int ArbolAVL<T>::tamano() {
    return tamano(this->raiz);
}

template<class T>
int ArbolAVL<T>::tamano(NodoBinario<T>* nodo) {
    if (nodo == NULL) {
        return -1;
    } else {
        return 1 + tamano(nodo->obtenerHijoIzq()) + tamano(nodo->obtenerHijoDer());
    }
}

template<class T>
int altura(NodoBinario<T>* nodo) {
    if (!nodo) return 0;
    return nodo->altura; // Asume que cada nodo tiene una propiedad de altura.
}
template<class T>
int ArbolAVL<T>::getBalance(NodoBinario<T>* nodo) {
    if (!nodo) return 0;
    return altura(nodo->obtenerHijoIzq()) - altura(nodo->obtenerHijoDer());
}

template<class T>
NodoBinario<T>* ArbolAVL<T>::rotacionDerecha(NodoBinario<T> *nodo) {
    NodoBinario<T>* nodo2 = nodo->obtenerHijoIzq();
    NodoBinario<T>* T2 = nodo2->obtenerHijoDer();

    nodo2->fijarHijoDer(nodo);
    nodo->fijarHijoIzq(T2);

    nodo->setAltura(std::max(altura(nodo->obtenerHijoIzq()), altura(nodo->obtenerHijoDer())) + 1);
    nodo2->setAltura(std::max(altura(nodo2->obtenerHijoIzq()), altura(nodo2->obtenerHijoDer())) + 1);

    return nodo2;
}
template<class T>
NodoBinario<T>* ArbolAVL<T>::rotacionIzquierda(NodoBinario<T> *nodo) {
    NodoBinario<T>* nodo2 = nodo->obtenerHijoDer();
    NodoBinario<T>* T2 = nodo2->obtenerHijoIzq();

    nodo2->fijarHijoIzq(nodo);
    nodo->fijarHijoDer(T2);

    nodo->setAltura(std::max(altura(nodo2->obtenerHijoIzq()), altura(nodo2->obtenerHijoDer())) + 1);
    nodo2->setAltura(std::max(altura(nodo->obtenerHijoIzq()), altura(nodo->obtenerHijoDer())) + 1);

    return nodo2;
}

template<class T>
NodoBinario<T>* ArbolAVL<T>::insertar(T val) {
    this->raiz = insertAVL(this->raiz, val);
    return this->raiz;
}

template<class T>
NodoBinario<T>* ArbolAVL<T>::insertAVL(NodoBinario<T>* nodo, T val) {

    if (nodo == NULL) {
        return new NodoBinario<T>(val);
    }

    if (val < nodo->obtenerDato()) {
        nodo->fijarHijoIzq(insertAVL(nodo->obtenerHijoIzq(), val));
    } else if (val > nodo->obtenerDato()) {
        nodo->fijarHijoDer(insertAVL(nodo->obtenerHijoDer(), val));
    } else {
        return nodo;
    }

    // Actualizar altura del nodo
    nodo->setAltura( 1 + std::max(altura(nodo->obtenerHijoIzq()), altura(nodo->obtenerHijoDer())));

    int balance = getBalance(nodo);

    // Si este nodo se vuelve desequilibrado, hay 4 posibles casos

    // Rotación simple a la derecha
    if (balance > 1 && val < nodo->obtenerHijoIzq()->obtenerDato()) {
        return rotacionDerecha(nodo);
    }

    // Rotación simple a la izquierda
    if (balance < -1 && val > nodo->obtenerHijoDer()->obtenerDato()) {
        return rotacionIzquierda(nodo);
    }

    // Rotación 1: Izquierda-Derecha
    if (balance > 1 && val > nodo->obtenerHijoIzq()->obtenerDato()) {
        nodo->fijarHijoIzq(rotacionIzquierda(nodo->obtenerHijoIzq()));
        return rotacionDerecha(nodo);
    }

    // Rotación 2: Derecha-Izquierda
    if (balance < -1 && val < nodo->obtenerHijoDer()->obtenerDato()) {
        nodo->fijarHijoDer(rotacionDerecha(nodo->obtenerHijoDer()));
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

/*template<class T>
NodoBinario<T>* insertar(NodoBinario<T>* nodo, T val) {

    *nodo = nodo->raiz;
    NodoBinario<T> *padre = nodo->raiz;
    bool duplicado = false;
    bool insertado = false;

    if(nodo->raiz == NULL){
        nodo->raiz = new NodoBinario<T>(val);
        insertado = true;
        return insertado;
    }else{
        while (nodo != NULL) {
            padre = nodo;
            if (val < nodo->getDato()){
                nodo = nodo->getHijoIzq();
            }else if(val > nodo->getDato()){
                nodo = nodo->getHijoDer();
            }else{
                duplicado = true;
                break;
            }
        }
        if(!duplicado){
            NodoBinario<T>* nuevo = new NodoBinario<T>(val);
            if(nuevo != NULL){
                if(val < padre->getDato()){
                    padre->setHijoIzq(nuevo);
                }else{
                    padre->setHijoDer(nuevo);
                }
                insertado = true;
            }
        }
        return insertado;
    }

    //Actualizar altura de este nodo
    nodo->altura = 1 + max(altura(nodo->getHijoIzq()), altura(nodo->getHijoDer()));

    //  Obtener balance
    int balance = getBalance(nodo);

    // 4. Si este nodo se desequilibra, hay 4 casos

    // Rotación simple a derecha
    if (balance > 1 && val < nodo->getHijoIzq()->getDato())
        return rotacionDerecha(nodo);

    // Rotación simple a izquierda
    if (balance < -1 && val > nodo->getHijoDer()->getDato())
        return rotacionIzquierda(nodo);

    // Rotación 1: Izquierda-Derecha
    if (balance > 1 && val > nodo->getHijoIzq()->getDato()) {
        nodo->setHijoIzq(rotacionIzquierda(nodo->getHijoIzq()));
        return rotacionDerecha(nodo);
    }

    // Rotación 2: Derecha-Izquierda
    if (balance < -1 && val < nodo->getHijoDer()->getDato()) {
        nodo->setHijoDer(rotacionDerecha(nodo->getHijoDer()));
        return rotacionIzquierda(nodo);
    }

    return nodo;
}*/
//iterativa
template<class T>
bool ArbolAVL<T>::eliminar(T val) {
    NodoBinario<T>* nodo = this->raiz;
    NodoBinario<T>* padre = this->raiz;

    while (nodo != NULL && nodo->obtenerDato() != val) {
        padre = nodo;
        if (val < nodo->obtenerDato())
            nodo = nodo->obtenerHijoIzq();
        else
            nodo = nodo->obtenerHijoDer();
    }

    if (nodo == NULL) {
        return false;
    }

    //3. Nodo con dos hijos, usar elmaximo del subarbol izquierdo
    //   para reemplazazr nodo
    if (nodo->obtenerHijoIzq() != NULL && nodo->obtenerHijoDer() != NULL) {
        NodoBinario<T>* sucesor = nodo->obtenerHijoDer();
        NodoBinario<T>* sucesorPadre = nodo;

        while (sucesor->obtenerHijoIzq() != NULL) {
            sucesorPadre = sucesor;
            sucesor = sucesor->obtenerHijoIzq();
        }

        nodo->fijarDato(sucesor->obtenerDato());

        nodo = sucesor;
        padre = sucesorPadre;
    }

   //2. Nodo con un solo hijo, usar hijo para reemplazar nodo
    NodoBinario<T>* hijo;
    if (nodo->obtenerHijoIzq() != NULL) {
        hijo = nodo->obtenerHijoIzq();
    } else {
        hijo = nodo->obtenerHijoDer();
    }

    // 1. Nodo hoja, borrarlo
    if (padre == NULL) {
        this->raiz = hijo;
    } else {
        if (nodo == padre->obtenerHijoIzq())
            padre->fijarHijoIzq(hijo);
        else
            padre->fijarHijoDer(hijo);
    }

    delete nodo;
    return true;
}

//iterativa
template< class T >
bool ArbolAVL<T>::buscar(T val){
    NodoBinario<T>* nodo = this->raiz;
    bool encontrado = false;

    while (nodo!=NULL && !encontrado){
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
void ArbolAVL<T>::preOrden(NodoBinario<T>* nodo){
    if(nodo!=NULL){
        std::cout << nodo->obtenerDato()<<" ";
        this->preOrden(nodo->obtenerHijoIzq());
        this->preOrden(nodo->obtenerHijoDer());
    }

}
//recurrente
template< class T >
void ArbolAVL<T>::inOrden(){
    if(!this->esVacio())
        this->inOrden(this->raiz);
}

template< class T >
void ArbolAVL<T>::inOrden(NodoBinario<T>* nodo){
    if(nodo!=NULL){
        this->inOrden(nodo->obtenerHijoIzq());
        std::cout << nodo->obtenerDato()<<" ";
        this->inOrden(nodo->obtenerHijoDer());
    }
}
//Recurrente
template< class T >
void ArbolAVL<T>::posOrden(NodoBinario<T>* nodo){
    if(nodo!=NULL){
        this->posOrden(nodo->obtenerHijoIzq());
        this->posOrden(nodo->obtenerHijoDer());
        std::cout << nodo->obtenerDato()<<" ";
    }

}
//iterativo
template< class T >
void ArbolAVL<T>::nivelOrden(){
    if(!this->esVacio()){
        std::queue<NodoBinario<T>*>cola;
        cola.push(this->raiz);
        NodoBinario<T>* nodo;
        while(!cola.empty()){
            nodo = cola.front();
            cola.pop();
            std::cout<< nodo->obtenerDato() << " ";
            if(nodo->obtenerHijoIzq() != NULL){
                cola.push(nodo->obtenerHijoIzq());
            }
            if(nodo->obtenerHijoDer != NULL){
                cola.push(nodo->obtenerHijoDer());
            }
        }
    }
}

