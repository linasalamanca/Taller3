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
template<class T>
bool arbolBinario<T>::insertar(T val){

    NodoBinario<T> *nodo = this->raiz;
    NodoBinario<T> *padre = this->raiz;
    bool duplicado = false;
    bool insertado = false;

    if(this->raiz == NULL){
        this->raiz = new NodoBinario<T>(val);
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
}

//iterativa
/*template< class T >
ArbolBinarioOrdenado<T>::eliminar(T val){
    //comparar con dato en nodo para bajar por izquierda o derecha
    //y para saber si val est� en el �rbol

    //Si val est� en el �rbol y ya baje
    //verificar situaci�n de eliminaci�n
    //1. Nodo hoja, borrarlo
    //2. Nodo con un solo hijo, usar hijo para reemplazar nodo
    //3. Nodo con dos hijos, usar elmaximo del subarbol izquierdo
    //   para reemplazazr nodo
}*/

template<class T>
bool arbolBinario<T>::eliminar(T val){
    NodoBinario<T> *nodo = this->raiz;
    NodoBinario<T> *padre = this->raiz;
    bool encontrado = false;
    bool eliminado = false;

    // comparar con dato en nodo para bajar por izq o der
    while(nodo != NULL){
        padre = nodo;
        if(val < nodo->getDato()){
            nodo = nodo->getHijoIzq();
        }
        else if(val > nodo->getDato()){
            nodo = nodo->getHijoDer();
        }
        if(val == nodo->getDato()){
            encontrado = true;
            break;
        }
    }

    // si el dato esta
    if(encontrado){
        std::cout<<"PADRE DEL NODO A BORRAR: "<<padre->getDato()<<std::endl;
        std::cout<<"NODO A BORRAR: "<<nodo->getDato()<<std::endl;

        // 3. nodo tiene 2 hijos: usar maximo del izq como sucesor
        if(nodo->getHijoIzq() != NULL && nodo->getHijoDer() != NULL){
            std::cout<<"CASO DOS HIJOS"<<std::endl;

            //encontrar maximo del subarbol izquierdo
            NodoBinario<T>* sucesor = nodo;
            NodoBinario<T>* padreSucesor = nodo;
            sucesor = nodo->getHijoIzq();
            while(sucesor->getHijoDer() != NULL){
                padreSucesor = sucesor;
                sucesor = sucesor->getHijoDer();
            }

            std::cout<<"PADRE DEL NODO SUCESOR: "<<padreSucesor->getDato()<<std::endl;
            std::cout<<"NODO SUCESOR: "<<sucesor->getDato()<<std::endl;

            eliminado = true;
            std::cout<<"SE ELIMINO EN CASO HOJA"<<std::endl;
            return eliminado;
            /*
            //revisar si sucesor tiene hijo izquierdo
            if(sucesor->getHijoIzq() != NULL){
                NodoBinario<T>* hijoSucesor = sucesor->getHijoIzq();
                padreSucesor->setHijoDer(hijoSucesor);
                sucesor->setHijoIzq(NULL);
            }

            //conectar sucesor con los hijos del eliminado
            sucesor->setHijoIzq(nodo->getHijoIzq());
            sucesor->setHijoDer(nodo->getHijoDer());

            //conectar sucesor con su padre
            if(padre->getHijoDer() == nodo){
               padre->setHijoDer(sucesor);
            }else if(padre->getHijoIzq() == nodo){
                padre->setHijoIzq(sucesor);
            }
            std::cout<<"SE ELIMINO EN CASO DOS HIJOS"<<std::endl;
            eliminado = true;*/
        }

        // 2.1 el nodo tiene un hijo izquierdo
        if(nodo->getHijoIzq() != NULL){
            std::cout<<"CASO UN HIJO IZQUIERDO"<<std::endl;
            if(padre->getHijoDer() == nodo){
                padre->setHijoDer(nodo->getHijoIzq());
            }else if(padre->getHijoIzq() == nodo){
                padre->setHijoIzq(nodo->getHijoIzq());
            }
            eliminado = true;
            nodo->setHijoIzq(NULL);
            //delete nodo;
            std::cout<<"SE ELIMINO EN CASO UN HIJO IZQUIERDO"<<std::endl;
            return eliminado;
        }

        // 2.2 el nodo tiene un hijo derecho
        if(nodo->getHijoDer() != NULL){
            std::cout<<"CASO UN HIJO DERECHO"<<std::endl;
            if(padre->getHijoDer() == nodo){
                padre->setHijoDer(nodo->getHijoDer());
            }else if(padre->getHijoIzq() == nodo){
                padre->setHijoIzq(nodo->getHijoDer());
            }
            eliminado = true;
            nodo->setHijoDer(NULL);
            //delete nodo;
            std::cout<<"SE ELIMINO EN CASO UN HIJO DERECHO"<<std::endl;
            return eliminado;
        }

        // 1. el nodo es hoja: borrar
        if(nodo->esHoja()){
            std::cout<<"CASO HOJA"<<std::endl;

            if(padre == NULL){
                std::cout<<"CASO HOJA PADRE NULL"<<std::endl;
                this->raiz = NULL;
            }

            if(padre->getHijoIzq()== nodo){
                std::cout<<"CASO HOJA ES EL HIJO IZQ"<<std::endl;
                padre->setHijoIzq(NULL);
            }

            if(padre->getHijoDer() == nodo){
                std::cout<<"CASO HOJA ES EL HIJO DER"<<std::endl;
                padre->setHijoDer(NULL);
            }

            eliminado = true;
            std::cout<<"SE ELIMINO EN CASO HOJA"<<std::endl;
            return eliminado;
        }
        if(eliminado){
            delete nodo;
        }
    }
    return eliminado;
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

