#ifndef __NODOBINARIO_H__
#define __NODOBINARIO_H__

template<class T>
class NodoBinario {
protected:
    T dato;
    NodoBinario<T>* hijoIzq;
    NodoBinario<T>* hijoDer;
public:
    NodoBinario();
    NodoBinario(T val);
    ~NodoBinario();
    T obtenerDato();
    void fijarDato(T val);
    NodoBinario<T>* obtenerHijoIzq();
    NodoBinario<T>* obtenerHijoDer();
    void fijarHijoIzq(NodoBinario<T>* izq);
    void fijarHijoDer(NodoBinario<T>* der);
    bool esHoja();
    int getAltura();
    void setAltura(int alt);

    int altura;
};

#include "NodoBinario.hxx"
#endif // __NODOBINARIO_H__
