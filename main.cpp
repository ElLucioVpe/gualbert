#include "header.h"

int main()
{
    ////Tablas
    tabla tablas;

    muestroR(inicioTabla(&tablas));
    muestroR(insertoTabla(&tablas,"artistas"));
    muestroR(insertoTabla(&tablas,"canciones"));

    //ricarddin=esVaciaTabla(tablas);
    muestroR(mostrarListaRet(tablas));
    //cout << ricarddin;


    //richard();

    ////Columnas
    return 0;
}
