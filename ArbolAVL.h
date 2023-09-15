#ifndef __ARBOLAVL_H__
#define __ARBOLAVL_H__

#include "NodoBinario.h"
template<class T>
class ArbolAVL{
protected:
    NodoBinario<T>* raiz;
public:
    ArbolAVL();
    ~ArbolAVL();
    bool esVacio();
    T datoRaiz();
    int altura();
    int altura(NodoBinario<T>* nodo);
    int tamano();
    int tamano(NodoBinario<T>* nodo);
    int getBalance(NodoBinario<T>* nodo);
    NodoBinario<T>* rotacionDerecha(NodoBinario<T>* nodo);
    NodoBinario<T>* rotacionIzquierda(NodoBinario<T>* nodo);
    NodoBinario<T>* insertAVL(NodoBinario<T>* nodo, T val);
    bool insertar(T val);
    bool eliminar(T val);
    bool buscar(T val);
    void preOrden(NodoBinario<T>* nodo);
    void inOrden();
    void inOrden(NodoBinario<T>* nodo);
    void posOrden(NodoBinario<T>* nodo);
    void nivelOrden();
};
#include "ArbolAVL.hxx"
#endif // __ARBOLAVL_H__

