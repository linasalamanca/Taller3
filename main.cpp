#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

#include <list>
#include <set>
// TODO #1: incluir cabeceras implementaciones propias
 #include "ArbolBinarioOrdenado.h"
 #include "ArbolAVL.h"

// -------------------------------------------------------------------------
typedef std::list< std::string > TList;
typedef std::set< std::string >  TSet;
// TODO #2: definir tipos de datos para arboles de cadenas de caracteres
// typedef implementacion_ArbolBinarioOrd< std::string > TArbolBO;
// typedef implementacion_ArbolAVL< std::string > TArbolAVL;

// -------------------------------------------------------------------------
template< class TTree >
bool ReadTree( TTree& tree, const std::string& filename );

// -------------------------------------------------------------------------
int main( int argc, char* argv[] ) {

  if( argc < 2 ) {
    std::cerr << "Uso: " << argv[ 0 ] << " archivo_entrada" << std::endl;
    return( -1 );
  }

  // TODO #3: declarar arboles
  // TArbolBO arbolBO;
  // TArbolAVL arbolAVL;
  TSet arbolRN;

  // Llenar arbol binario ordenado y obtener tiempo de ejecucion
  std::clock_t start_arbolBO = std::clock( );
  // TODO #4: llenar arbol desde archivo con funcion ReadTree
  // bool llenar_arbolBO = ReadTree( arbolBO, argv[ 1 ] );
  std::clock_t end_arbolBO = std::clock( );
  double tiempo_arbolBO =
    ( end_arbolBO - start_arbolBO ) / double( CLOCKS_PER_SEC );
  /* TODO #5: si se pudo llenar el arbol, imprimir el tiempo
     if( llenar_arbolBO )
       std::cout
         << "Tiempo de llenado Arbol Binario Ordenado = "
         << tiempo_arbolBO << "seg."
         << std::endl;
     else
       std::cout
         << "Error al usar \"" << argv[ 1 ]
         << "\" para llenar el arbol binario ordenado."
         << std::endl;
  */

  // Llenar arbol AVL y obtener tiempo de ejecucion
  std::clock_t start_arbolAVL = std::clock( );
  // TODO #6: llenar arbol AVL desde archivo con funcion ReadTree
  // bool llenar_arbolAVL = ReadTree( arbolAVL, argv[ 1 ] );
  std::clock_t end_arbolAVL = std::clock( );
  double tiempo_arbolAVL =
    ( end_arbolAVL - start_arbolAVL ) / double( CLOCKS_PER_SEC );
  /* TODO #7: si se pudo llenar el arbol, imprimir el tiempo
     if( llenar_arbolAVL )
       std::cout
         << "Tiempo de llenado Arbol AVL = "
         << tiempo_arbolAVL << "seg."
         << std::endl;
     else
       std::cout
         << "Error al usar \"" << argv[ 1 ]
         << "\" para llenar el arbol AVL."
         << std::endl;
  */

  // Llenar arbol RN y obtener tiempo de ejecucion
  std::clock_t start_arbolRN = std::clock( );
  bool llenar_arbolRN = ReadTree( arbolRN, argv[ 1 ] );
  std::clock_t end_arbolRN = std::clock( );
  double tiempo_arbolRN =
    ( end_arbolRN - start_arbolRN ) / double( CLOCKS_PER_SEC );
  if( llenar_arbolRN )
    std::cout
      << "Tiempo de llenado Arbol RN = "
      << tiempo_arbolRN << "seg."
      << std::endl;
  else
    std::cout
      << "Error al usar \"" << argv[ 1 ]
      << "\" para llenar el arbol RN."
      << std::endl;

  // Obtener recorrido en inorden del arbol binario ordenado
  TList inorden_arbolBO;
  // TODO #8: usar funcion del arbol para obtener recorrido en lista
  // arbolBO.inOrdenLista( inorden_arbolBO );

  // Obtener recorrido en inorden del arbol AVL
  TList inorden_arbolAVL;
  // TODO #9: usar funcion del arbol AVL para obtener recorrido en lista
  // arbolAVL.inOrdenLista( inorden_arbolAVL );

  if( inorden_arbolBO.size( ) != inorden_arbolAVL.size( ) ||
      inorden_arbolBO.size( ) != arbolRN.size( ) ||
      inorden_arbolAVL.size( ) != arbolRN.size( ) ) {

    std::cout << "Tamannos de los arboles no coinciden." << std::endl;
    return( -1 );
  }

  // Comparar los arboles
  TList::const_iterator aboIt = inorden_arbolBO.begin( );
  TList::const_iterator avlIt = inorden_arbolAVL.begin( );
  TSet::const_iterator rbIt = arbolRN.begin( );
  bool equal = true;
  for( ; rbIt != arbolRN.end( ); aboIt++, avlIt++, rbIt++ )
    equal &= ( *rbIt == *avlIt && *avlIt == *aboIt && *rbIt == *aboIt );

  // Informar si los arboles coinciden
  std::cout << "Los arboles ";
  if( !equal )
    std::cout << "no ";
  std::cout << "coinciden." << std::endl;

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

// eof - taller_3_ordenamiento_busqueda.cxx
