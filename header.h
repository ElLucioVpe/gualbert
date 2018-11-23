#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <sstream>

#define LARGOCADENA 20

using namespace std;


enum _Retorno{

    ok,error,noImplementada //solo puede retornar estos 3 res, como array

};
typedef enum _Retorno tipoRet;

struct _fila{
    string dato;
    _fila *sgtFila;

};typedef struct _fila *fila;

struct _columna{
    string nombreCol;
    bool primaryKey;
    _columna *sgtColumna;
    _fila *fila;

};typedef struct _columna *columna;

struct _tabla{
    string nombre;
    _tabla *ptrTablaIzq;
    _tabla *ptrTablaDer;
    _columna *columna;

};typedef struct _tabla *tabla;


////////////////////Functs
void richard();
void muestroR(tipoRet resultado);

tipoRet inicioTabla(tabla *tabl);
void creoTabla(tabla **tabl);

tipoRet insertoTabla(tabla *tabl,string nombre);
tabla insertarTabla(tabla tabl, string name);

tipoRet eliminoTabla(tabla *tabl,string nombre);
tabla eliminarTabla(tabla *tabl, tabla *aux, string name);

tipoRet insertoColumna(tabla *tabl, string tabla, string columna);
tabla insertarColumna(tabla tabl, tabla auxTable, string nombreColumna, bool primaryKey);

tipoRet insertoDato(tabla *tabl, string nombreTabla, string dato);
tabla insertarDato(tabla *tabl, tabla *tablaInsertarDato, string dato, string name);

tipoRet actualizoDatos(tabla *tabl, string tablNom, string condicionCol, string condicionDato, string nuevoDatoCol, string nuevoDato);
tabla actualizarDatos(tabla tabl, tabla auxTabla, string condicionCol, string condicionDato, string nuevoDatoCol, string nuevoDato);

void mostrarListaRecur(tabla l);
void mostrarLista(tabla l);

bool esVacia(tabla tabl);
bool esVacia(columna colum);
bool esVacia(fila aux);


tipoRet mostrarListaRet(tabla l);


tipoRet eliminoDato(tabla *tabl, string tablNom, string colNom, string filNom);
int buscoDato(tabla tabl, string tablNom, string colNom, string filNom);
//tabla eliminarDatoReferencia(tabla tabl,string tablNom, string colNom, string filNom);
tabla eliminarDato(tabla tabl, int i, string tablNom);
tipoRet eliminoColumna(tabla *tabl,string tablNom, string colNom);
int buscoColumna(tabla tabl,string tablNom, string colNom);
tabla eliminarColumna(tabla tabl, int i, string tablNom);
fila vaciarFilas(fila fil);

bool verificoDuplicadoFila(tabla *tabl, string nombreTabla, string primaryKey);

int cuentoColumnas(string nombreTabla, tabla tabl);

tipoRet eliminoDatoTupla(tabla *tabl, string nombreTabla, string condicion);
tabla eliminarDatoTupla(tabla tabl, tabla tablaAux, string col, string dato, char comp);

void mostrarTabla(tabla l,string nomTabl);
tipoRet muestroTabla(tabla l, string nomtabl);

tipoRet insertoTablaAbb(tabla &tabl, string nombre);
//void insertarAbb(_tabla *&lista, string n);
void insertaNodoArbol( tabla &A, string valor );

void mostrarSim(tabla lista);

tabla buscarMenor(tabla tabl);
tabla HijoIzq(tabla tabl);
bool existeTabla(tabla tabl, string nombre);
bool existeColumna(tabla *tabl, string nombreTabla, string nombreColumna);

tabla retornarTablaBusacada(tabla A, string nombre);
columna retornarColumna(tabla *tabl, string nombreTabla, string nombreColumna);

tipoRet proyectoTabla(tabla *tabl, string tabla1, string columnas, string tabla2);
tabla proyectarTabla(tabla *tabl, columna col, string tabla2);

void eliminoTablaAbb(tabla &A, string valor);
tabla proyectoWhere(tabla tabl, tabla auxTabla, string nombreTabla1, string condicion, string nombreTabla2);
tipoRet proyectarWhere(tabla *tabl, string nombreTabla1, string condicion, string nombreTabla2);

void printTables(tabla lista);
tipoRet printoTables(tabla l);
void printMetadata(tabla lista);
tipoRet printoMetadata(tabla lista);

tipoRet unirTablas(tabla *tabl, string nombreTabla1, string nombreTabla2, string nombreTabla3);
tabla unoTablas(tabla *tabl, tabla tabla1, tabla tabla2, string nombreTabla3);
