#include <iostream>
#include <string>
using namespace std;



enum _Retorno{

ok,error,noImplementada //solo puede retornar estos 3 res, como array


};
typedef enum _Retorno tipoRet;


struct _tabla{
    string nombre;
    _tabla *ptrtabla;

};typedef struct _tabla *tabla;

struct _columna{
    string nombreCol;
    _columna *columna;
    tabla table;

};typedef struct _columna *columna;

struct _fila{
    string nombreCol;

    _fila *fila;
    columna colum;


};typedef struct _fila *fila;




////////////////////Functs
void richard();
void muestroR(tipoRet resultado);

tipoRet inicioTabla(tabla *tabl);
void creoTabla(tabla **tabl);


tipoRet insertoTabla(tabla *tabl,string nombre);
tabla insertarTabla(tabla tabl, string name);


void mostrarListaRecur(tabla l);
void mostrarLista(tabla l);
bool esVaciaTabla(tabla tabl);
tipoRet mostrarListaRet(tabla l);
