#include "header.h"

int main()
{
    ////Tablas
    bool ricarddin;
    tabla tablas;
    //tablas = new _tabla;
    //tablas = new _tabla;

    muestroR(inicioTabla(&tablas));
    muestroR(insertoTabla(&tablas,"Darin"));
    muestroR(insertoTabla(&tablas,"Roshi"));
    //muestroR(insertoTabla(tablas,"puertas"));


    //ricarddin=esVaciaTabla(tablas);
    muestroR(mostrarListaRet(tablas));
    //cout << ricarddin;


    //richard();

    ////Columnas
    return 0;
}
