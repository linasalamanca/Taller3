#ifndef __NODOGENERAL_H__
#define __NODOGENERAL_H__

#include <list>

template<class T>
class NodoGeneral{
protected:
   T dato;
   std::list<NodoGeneral<T>*> desc;
public:
    NodoGeneral();
    ~NodoGeneral();
    T& obtenerDato();
    void fijarDato(T& val);
    void limpiarLista();
    void adicionarDesc(T& nval);
    bool eliminarDesc(T& val);
};

#include "NodoGeneral.hxx"
#endif // __NODOGENERAL_H__
