#include "header.h"


void richard(){

        cout << "Hello world!" << endl;
}



tipoRet insertoTabla(tabla *tabl,string nombre){
tabla tablon;
tablon=*tabl;
tablon=insertarTabla(tablon,nombre);

*tabl=tablon;
return ok;
}

tabla insertarTabla(tabla tabl, string name){
//0 a null 1 a 0
tabla nuevatabla;
nuevatabla = new _tabla;

nuevatabla -> nombre=name;
nuevatabla -> ptrtabla=tabl; //1 -> null
tabl=nuevatabla; // l -->32

return tabl;
}



///Inicializar tabla
void creoTabla(tabla **tabl){

tabla nuevatabla;
nuevatabla = new _tabla;

nuevatabla -> ptrtabla=NULL; //1 -> null
//tabl=nuevatabla; // l -->32

//return tabl;


**tabl = nuevatabla;
//cout << "NEL";
}


tipoRet inicioTabla(tabla *tabl){

creoTabla(&tabl);

return ok;
}


///Muestro Retorno
void muestroR(tipoRet resultado){

switch(resultado){

case 0 :
cout << "ok";
break;

case 1:
cout << "Error";
break;

case 2:
cout << "No Implementado";
break;

}

}

bool esVaciaTabla(tabla tabl){

if(tabl == NULL){
    return true;

}else{
     return false;

}
}

tipoRet mostrarListaRet(tabla l){
if(!esVaciaTabla(l)){
    mostrarListaRecur(l);
    return ok;
}else{
    return error;
    cout << "Empty";
}
}

void mostrarListaRecur(tabla l){
if (!esVaciaTabla(l)){
cout << l->nombre;
cout << endl;
l=l->ptrtabla;

mostrarListaRecur(l); //recursiv
} else{

}

}

