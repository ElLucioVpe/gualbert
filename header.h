#include <iostream>
#include <string>
#include <sstream>
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
    _columna *sgtColumna;
    _fila *fila;

};typedef struct _columna *columna;

struct _tabla{
    string nombre;
    _tabla *ptrtabla;
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
tabla eliminarTabla(tabla tabl, string name);

tipoRet insertoColumna(tabla *tabl, string tabla, string columna);
tabla insertarColumna(tabla tabl, tabla auxTable, string columna);

tipoRet insertoDato(tabla *tabl, string nombreTabla, string dato);
tabla insertarDato(tabla tabl, tabla tablaInsertarDato, string dato);

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
