#include "header.h"

int main()
{
    ////Tablas
   // bool ricarddin;
    tabla tablas; //creo una variable de tipo tabla llamada talbas que ya es puntero a la struct _tablas
    //tablas = new _tabla;
    //tablas = new _tabla;


    /*muestroR(inicioTabla(&tablas));
    muestroR(insertoTabla(&tablas,"Darin"));
    muestroR(insertoTabla(&tablas,"Roshi"));
    muestroR(eliminoTabla(&tablas,"Roshi"));
    //muestroR(insertoTabla(tablas,"puertas"));

    //ricarddin=esVaciaTabla(tablas);
    muestroR(mostrarListaRet(tablas));
    muestroR(insertoColumna(&tablas, "nombre"))*/

    muestroR(inicioTabla(&tablas));
    muestroR(insertoTabla(&tablas,"clientes"));
    muestroR(insertoTabla(&tablas,"personas"));
    muestroR(insertoTabla(&tablas,"mascotas"));

    muestroR(insertoColumna(&tablas, "personas", "ci"));
    muestroR(insertoColumna(&tablas, "personas", "nombre"));
    muestroR(insertoColumna(&tablas, "personas", "apellido"));

    muestroR(insertoDato(&tablas,"personas", "1:Martin:Perdomo"));
    muestroR(insertoDato(&tablas,"personas", "4:Diego:Olivera"));
    muestroR(insertoDato(&tablas,"personas", "7:Lautaro:KASjkdsjk"));
    //muestroR(eliminoDato(&tablas, "personas","apellido","4"));


    muestroR(mostrarListaRet(tablas));
    cout << endl;

    //cout << tablas->nombre << endl;
    //cout << tablas->nombre;
    //cout << tablas->columna->nombreCol << endl;
    cout << tablas->ptrtabla->columna->fila->dato << endl;
    cout << tablas->ptrtabla->columna->fila->sgtFila->dato << endl;
    cout << tablas->ptrtabla->columna->fila->sgtFila->sgtFila->dato << endl;

    cout << tablas->ptrtabla->columna->sgtColumna->fila->dato << endl;
    cout << tablas->ptrtabla->columna->sgtColumna->fila->sgtFila->dato << endl;
    cout << tablas->ptrtabla->columna->sgtColumna->fila->sgtFila->sgtFila->dato << endl;

    cout << tablas->ptrtabla->columna->sgtColumna->sgtColumna->fila->dato << endl;
    cout << tablas->ptrtabla->columna->sgtColumna->sgtColumna->fila->sgtFila->dato << endl;



    //cout << ricarddin;


    //richard();

    ////Columnas
    return 0;
}
