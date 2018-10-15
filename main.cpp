#include "header.h"

int main()
{
    ////Tablas
    tabla tablas; //creo una variable de tipo tabla llamada talbas que ya es puntero a la struct _tablas

    muestroR(inicioTabla(&tablas));
    muestroR(insertoTabla(&tablas,"clientes"));
    muestroR(insertoTabla(&tablas,"personas"));
    muestroR(insertoTabla(&tablas,"mascotas"));

    muestroR(insertoColumna(&tablas, "personas", "ci"));
    muestroR(insertoColumna(&tablas, "personas", "nombre"));
    muestroR(insertoColumna(&tablas, "personas", "apellido"));
        //muestroR(insertoColumna(&tablas, "personas", "correo"));

    //muestroR(insertoDato(&tablas,"personas", "1:Martin:Perdomo"));
    muestroR(insertoDato(&tablas,"personas", "1:Martin:Perdomo"));
    muestroR(insertoDato(&tablas,"personas", "4:Diego:Olivera"));
    muestroR(insertoDato(&tablas,"personas", "7:Lautaro:KASjkdsjk"));
    muestroR(insertoDato(&tablas,"personas", "4:Nicolas:Varela"));

    muestroR(actualizoDatos(&tablas, "personas", "ci", "1", "ci", "69"));
    //muestroR(eliminoTabla(&tablas, "personas"));
  //  muestroR(insertoDato(&tablas,"personas", "8:SOldado:KASjkdsjk"));
  //  muestroR(insertoDato(&tablas,"personas", "9:Zi:Rica"));
 //   muestroR(insertoDato(&tablas,"personas", "710:Robert:ole"));
   // muestroR(insertoDato(&tablas,"personas", "8:Luis:OJILI"));


    //muestroR(eliminoDato(&tablas, "personas","ci","69"));
    //muestroR(eliminoDato(&tablas, "personas","ci","4"));
    //muestroR(eliminoColumna(&tablas, "personas","nombre"));
    //muestroR(eliminoColumna(&tablas, "personas","nombre"));
   // muestroR(eliminoDato(&tablas, "personas","ci","8"));
    //muestroR(eliminoDato(&tablas, "personas","ci","9"));


    muestroR(mostrarListaRet(tablas));
    cout << endl;

    return 0;
}
