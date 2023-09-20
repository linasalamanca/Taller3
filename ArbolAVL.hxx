#include "ArbolAVL.h"
#include "NodoBinario.h"
#include <queue>
#include <iostream>

template< class T >
ArbolAVL<T>::ArbolAVL(){
    this->raiz = nullptr;
}

template< class T >
ArbolAVL<T>::~ArbolAVL(){
    if(this->raiz != nullptr){
        delete this->raiz;
        this->raiz = nullptr;
    }

}
template< class T >
bool ArbolAVL<T>::esVacio(){
    return this->raiz==nullptr;
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

/*template< class T >
int ArbolAVL<T>::altura(NodoBinario<T>* nodo){
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
}*/
//recurrente
template<class T>
int ArbolAVL<T>::tamano() {
    return tamano(this->raiz);
}

template<class T>
int ArbolAVL<T>::tamano(NodoBinario<T>* nodo) {
    if (nodo == nullptr) {
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
int getBalance(NodoBinario<T>* nodo) {
    if (!nodo) return 0;
    return altura(nodo->obtenerHijoIzq()) - altura(nodo->obtenerHijoDer());
}

template<class T>
NodoBinario<T>* rotaciones(NodoBinario<T>* nodo) {
    // Altura del nodo actual
    nodo->altura = std::max(altura(nodo->obtenerHijoIzq()), altura(nodo->obtenerHijoDer())) + 1;

    int balance = getBalance(nodo);

    if (balance > 1) {
        if (getBalance(nodo->obtenerHijoIzq()) >= 0) {
            // Rotación simple a la derecha (LL)
            NodoBinario<T>* nodo2 = nodo->obtenerHijoIzq();
            NodoBinario<T>* T2 = nodo2->obtenerHijoDer();

            nodo2->fijarHijoDer(nodo);
            nodo->fijarHijoIzq(T2);

            nodo->altura = std::max(altura(nodo->obtenerHijoIzq()), altura(nodo->obtenerHijoDer())) + 1;
            nodo2->altura = std::max(altura(nodo2->obtenerHijoIzq()), altura(nodo2->obtenerHijoDer())) + 1;

            return nodo2;
        } else {
            // Rotación izquierda-derecha (LR)
            nodo->fijarHijoIzq(rotacionIzquierda(nodo->obtenerHijoIzq()));
            return rotacionDerecha(nodo);
        }
    }

    if (balance < -1) {
        if (getBalance(nodo->obtenerHijoDer()) <= 0) {
            // Rotación simple a la izquierda (RR)
            NodoBinario<T>* nodo2 = nodo->obtenerHijoDer();
            NodoBinario<T>* T2 = nodo2->obtenerHijoIzq();

            nodo2->fijarHijoIzq(nodo);
            nodo->fijarHijoDer(T2);

            nodo->altura = std::max(altura(nodo->obtenerHijoIzq()), altura(nodo->obtenerHijoDer())) + 1;
            nodo2->altura = std::max(altura(nodo2->obtenerHijoIzq()), altura(nodo2->obtenerHijoDer())) + 1;

            return nodo2;
        } else {
            // Rotación derecha-izquierda (RL)
            nodo->fijarHijoDer(rotacionDerecha(nodo->obtenerHijoDer()));
            return rotacionIzquierda(nodo);
        }
    }

    return nodo;
}

template<class T>
NodoBinario<T>* insertAVL(NodoBinario<T>* nodo, T val){

    if (!nodo)
        return new NodoBinario<T>(val);

    if (val < nodo->obtenerDato()) {
        nodo->fijarHijoIzq(insertAVL(nodo->obtenerHijoIzq(), val));
    } else if (val > nodo->obtenerDato()) {
        nodo->fijarHijoDer(insertAVL(nodo->obtenerHijoDer(), val));
    } else {
        return nodo; // No se permiten duplicados
    }

    nodo->altura = 1 + std::max(altura(nodo->obtenerHijoIzq()), altura(nodo->obtenerHijoDer()));

    int balance = getBalance(nodo);

    // Si este nodo se vuelve desequilibrado, hay 4 posibles casos

    // Caso izquierda izquierda
    if (balance > 1 && val < nodo->obtenerHijoIzq()->obtenerDato())
        return rotacionDerecha(nodo);

    // Caso derecha derecha
    if (balance < -1 && val > nodo->obtenerHijoDer()->obtenerDato())
        return rotacionIzquierda(nodo);

    // Caso izquierda derecha
    if (balance > 1 && val > nodo->obtenerHijoIzq()->obtenerDato()) {
        nodo->fijarHijoIzq(rotacionIzquierda(nodo->obtenerHijoIzq()));
        return rotacionDerecha(nodo);
    }

    // Caso derecha izquierda
    if (balance < -1 && val < nodo->obtenerHijoDer()->obtenerDato()) {
        nodo->fijarHijoDer(rotacionDerecha(nodo->obtenerHijoDer()));
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

template<class T>
bool ArbolAVL<T>::insertar(T val) {
    if (!this->raiz) {
        this->raiz = new NodoBinario<T>(val);
        return true;
    }

    this->raiz = insertAVL(this->raiz, val);
    return true;
}
//iterativa
template<class T>
bool ArbolAVL<T>::eliminar(T val) {
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
bool ArbolAVL<T>::buscar(T val){
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
void ArbolAVL<T>::preOrden(NodoBinario<T>* nodo){
    if(nodo!=nullptr){
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
    if(nodo!=nullptr){
        this->inOrden(nodo->obtenerHijoIzq());
        std::cout << nodo->obtenerDato()<<" ";
        this->inOrden(nodo->obtenerHijoDer());
    }
}
//Recurrente
template< class T >
void ArbolAVL<T>::posOrden(NodoBinario<T>* nodo){
    if(nodo!=nullptr){
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
            if(nodo->obtenerHijoIzq() != nullptr){
                cola.push(nodo->obtenerHijoIzq());
            }
            if(nodo->obtenerHijoDer() != nullptr){
                cola.push(nodo->obtenerHijoDer());
            }
        }
    }
}

