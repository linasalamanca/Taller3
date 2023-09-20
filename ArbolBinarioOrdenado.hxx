#include "ArbolBinarioOrdenado.h"
#include "NodoBinario.h"
#include <queue>
#include <iostream>

template< class T >
ArbolBinarioOrdenado<T>::ArbolBinarioOrdenado(){
    this->raiz = NULL;
}

template< class T >
ArbolBinarioOrdenado<T>::~ArbolBinarioOrdenado(){
    if(this->raiz != NULL){
        delete this->raiz;
        this->raiz = NULL;
    }

}

template< class T >
bool ArbolBinarioOrdenado<T>::esVacio(){
    return this->raiz==NULL;
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

        if(nodo->obtenerHijoIzq() != NULL)
            valt_izq = this -> altura(nodo->obtenerHijoIzq());
        if(nodo->obtenerHijoDer() != NULL)
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
    if (nodo == NULL) {
        return -1;
    } else {
        return 1 + tamano(nodo->obtenerHijoIzq()) + tamano(nodo->obtenerHijoDer());
    }
}

//iterativa
template<class T>
bool ArbolBinarioOrdenado<T>::insertar(T val){

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
            if (val < nodo->obtenerDato()){
                nodo = nodo->obtenerHijoIzq();
            }else if(val > nodo->obtenerDato()){
                nodo = nodo->obtenerHijoDer();
            }else{
                duplicado = true;
                break;
            }
        }

        if(!duplicado){
            NodoBinario<T>* nuevo = new NodoBinario<T>(val);
            if(nuevo != NULL){
                if(val < padre->obtenerDato()){
                    padre->fijarHijoIzq(nuevo);
                }else{
                    padre->fijarHijoDer(nuevo);
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
bool ArbolBinarioOrdenado<T>::eliminar(T val){
    NodoBinario<T> *nodo = this->raiz;
    NodoBinario<T> *padre = this->raiz;
    bool encontrado = false;
    bool eliminado = false;

    // comparar con dato en nodo para bajar por izq o der
    while(nodo != NULL){
        padre = nodo;
        if(val < nodo->obtenerDato()){
            nodo = nodo->obtenerHijoIzq();
        }
        else if(val > nodo->obtenerDato()){
            nodo = nodo->obtenerHijoDer();
        }
        if(val == nodo->obtenerDato()){
            encontrado = true;
            break;
        }
    }

    // si el dato esta
    if(encontrado){
        std::cout<<"PADRE DEL NODO A BORRAR: "<<padre->obtenerDato()<<std::endl;
        std::cout<<"NODO A BORRAR: "<<nodo->obtenerDato()<<std::endl;

        // 3. nodo tiene 2 hijos: usar maximo del izq como sucesor
        if(nodo->obtenerHijoIzq() != NULL && nodo->obtenerHijoDer() != NULL){
            std::cout<<"CASO DOS HIJOS"<<std::endl;

            //encontrar maximo del subarbol izquierdo
            NodoBinario<T>* sucesor = nodo;
            NodoBinario<T>* padreSucesor = nodo;
            sucesor = nodo->obtenerHijoIzq();
            while(sucesor->obtenerHijoDer() != NULL){
                padreSucesor = sucesor;
                sucesor = sucesor->obtenerHijoDer();
            }

            std::cout<<"PADRE DEL NODO SUCESOR: "<<padreSucesor->obtenerDato()<<std::endl;
            std::cout<<"NODO SUCESOR: "<<sucesor->obtenerDato()<<std::endl;

            eliminado = true;
            std::cout<<"SE ELIMINO EN CASO HOJA"<<std::endl;
            return eliminado;
            /*
            //revisar si sucesor tiene hijo izquierdo
            if(sucesor->obtenerHijoIzq() != NULL){
                NodoBinario<T>* hijoSucesor = sucesor->obtenerHijoIzq();
                padreSucesor->fijarHijoDer(hijoSucesor);
                sucesor->fijarHijoIzq(NULL);
            }

            //conectar sucesor con los hijos del eliminado
            sucesor->fijarHijoIzq(nodo->obtenerHijoIzq());
            sucesor->fijarHijoDer(nodo->obtenerHijoDer());

            //conectar sucesor con su padre
            if(padre->obtenerHijoDer() == nodo){
               padre->fijarHijoDer(sucesor);
            }else if(padre->obtenerHijoIzq() == nodo){
                padre->fijarHijoIzq(sucesor);
            }
            std::cout<<"SE ELIMINO EN CASO DOS HIJOS"<<std::endl;
            eliminado = true;*/
        }

        // 2.1 el nodo tiene un hijo izquierdo
        if(nodo->obtenerHijoIzq() != NULL){
            std::cout<<"CASO UN HIJO IZQUIERDO"<<std::endl;
            if(padre->obtenerHijoDer() == nodo){
                padre->fijarHijoDer(nodo->obtenerHijoIzq());
            }else if(padre->obtenerHijoIzq() == nodo){
                padre->fijarHijoIzq(nodo->obtenerHijoIzq());
            }
            eliminado = true;
            nodo->fijarHijoIzq(NULL);
            //delete nodo;
            std::cout<<"SE ELIMINO EN CASO UN HIJO IZQUIERDO"<<std::endl;
            return eliminado;
        }

        // 2.2 el nodo tiene un hijo derecho
        if(nodo->obtenerHijoDer() != NULL){
            std::cout<<"CASO UN HIJO DERECHO"<<std::endl;
            if(padre->obtenerHijoDer() == nodo){
                padre->fijarHijoDer(nodo->obtenerHijoDer());
            }else if(padre->obtenerHijoIzq() == nodo){
                padre->fijarHijoIzq(nodo->obtenerHijoDer());
            }
            eliminado = true;
            nodo->fijarHijoDer(NULL);
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

            if(padre->obtenerHijoIzq()== nodo){
                std::cout<<"CASO HOJA ES EL HIJO IZQ"<<std::endl;
                padre->fijarHijoIzq(NULL);
            }

            if(padre->obtenerHijoDer() == nodo){
                std::cout<<"CASO HOJA ES EL HIJO DER"<<std::endl;
                padre->fijarHijoDer(NULL);
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
void ArbolBinarioOrdenado<T>::preOrden(NodoBinario<T>* nodo){
    if(nodo!=NULL){
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
    if(nodo!=NULL){
        this->inOrden(nodo->obtenerHijoIzq());
        std::cout << nodo->obtenerDato()<<" ";
        this->inOrden(nodo->obtenerHijoDer());
    }
}
//Recurrente
template< class T >
void ArbolBinarioOrdenado<T>::posOrden(NodoBinario<T>* nodo){
    if(nodo!=NULL){
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
            if(nodo->obtenerHijoIzq != NULL){
                cola.push(nodo->obtenerHijoIzq());
            }
            if(nodo->obtenerHijoDer != NULL){
                cola.push(nodo->obtenerHijoDer());
            }
        }
    }
}

