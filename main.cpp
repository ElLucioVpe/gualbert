#include "header.h"

int main()
{
    ////Tablas
    bool ricarddin;
    tabla tablas; //creo una variable de tipo tabla llamada talbas que ya es puntero a la struct _tablas
    //tablas = new _tabla;
    //tablas = new _tabla;
    /*
    muestroR(inicioTabla(&tablas));
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
    muestroR(insertoColumna(&tablas, "ci"));
    muestroR(insertoColumna(&tablas, "nombre"));
    muestroR(insertoColumna(&tablas, "apellido"));


    muestroR(mostrarListaRet(tablas));



    //cout << ricarddin;


    //richard();

    ////Columnas
    return 0;
}
