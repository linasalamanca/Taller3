
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>
using namespace std;

// TODO #1: incluir cabeceras implementaciones propias
#include "ArbolBinarioOrdenado.h"

// TODO #2: definir tipos de datos para arboles de cadenas de caracteres

// -------------------------------------------------------------------------
template< class TTree >
bool ReadTree( TTree& tree, const std::string& filename );

// -------------------------------------------------------------------------
int main( int argc, char* argv[] ) {

    if( argc < 2 ) {
        std::cerr << "Uso: " << argv[ 0 ] << " archivo_entrada" << std::endl;
        return( -1 );
    }else{
        cout<<"archivo de entrada "<<argv[1]<<endl;
    }

    // TODO #3: declarar arboles
    ArbolBinarioOrdenado< int > arbolB = ArbolBinarioOrdenado<int> ();

    cout<<"valor: "<<arbolB.insertar(6)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(2)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(20)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(1)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(3)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(16)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(30)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(11)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(15)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(0)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(35)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(14)<< std::endl;
    cout<<"valor: "<<arbolB.insertar(17)<< std::endl;

    arbolB.inOrden();

    cout<<"ELIMINACION"<< std::endl;
    cout<<"se elimino: "<<arbolB.eliminar(16)<< std::endl;
    arbolB.inOrden();

    /*
    // Llenar arbol binario ordenado y obtener tiempo de ejecucion
    std::clock_t start_arbolBO = std::clock( );

    // TODO #4: llenar arbol desde archivo con funcion ReadTree
    bool llenar_arbolBO = ReadTree( arbolBO, argv[ 1 ] );
    std::clock_t end_arbolBO = std::clock( );
    double tiempo_arbolBO = ( end_arbolBO - start_arbolBO ) / double( CLOCKS_PER_SEC );

    // TODO #5: si se pudo llenar el arbol, imprimir el tiempo
       if( llenar_arbolBO ){
           std::cout
                   << "Tiempo de llenado Arbol Binario Ordenado = "
                   << tiempo_arbolBO << "seg."
                   << std::endl;
       }

       else{
           std::cout
                   << "Error al usar \"" << argv[ 1 ]
                   << "\" para llenar el arbol binario ordenado."
                   << std::endl;
       }

    // Obtener recorrido en inorden del arbol binario ordenado
    // TODO #8: usar funcion del arbol para obtener recorrido en lista
    // arbolBO.inOrdenLista( inorden_arbolBO );
*/
    return( 0 );
}

// -------------------------------------------------------------------------
template< class TTree >
bool ReadTree( TTree& tree, const std::string& filename ) {

    std::ifstream input( filename.c_str( ) );
    if( !input )
        return( false );

    while( !input.eof( ) ) {

        std::string code, value;
        input >> code >> value;
        if( code == "add" )
            tree.insert( value );  // El arbol debe proveer el metodo "insert"
        else if( code == "del" )
            tree.erase( value );  // El arbol debe proveer el metodo "erase"

    }

    input.close( );
    return( true );
}
