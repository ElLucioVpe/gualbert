#include "header.h"


void richard(){

        cout << "Hello world!" << endl;
}


//Inserto Tabla
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


//Eliminar Tabla

tipoRet eliminoTabla(tabla *tabl,string nombre){

//if tiene columnas pasar a eliminar las col primero
tabla tablon;
tablon=*tabl;
if (!esVaciaTabla(tablon)){
tablon=eliminarTabla(tablon,nombre);

*tabl=tablon;
return ok;
}else{
return error;
}
}

tabla eliminarTabla(tabla tabl, string name){
//0 a null 1 a 0
tabla BorrarTabl;
tabla anterior;

BorrarTabl = new _tabla;
anterior = new _tabla;

anterior=NULL;
BorrarTabl=tabl; //apunta al inicio de la lista

    while((BorrarTabl!=NULL)&&(BorrarTabl->nombre!=name)){ //mientras que BorrarTabl no sea null y no sea igual al nombre desdeado
    anterior=BorrarTabl; //anterior se iguala a BorrarTabl

    BorrarTabl=BorrarTabl->ptrtabla; //Borrartabl va al siguiente nodo 'Tabla'



    }

    //Casos cuando salga del while

    if(BorrarTabl==NULL){  // significa que recorrio toda la lista y cuando entro al while al final BorrarTabl es igual a null/ apunta al putero sig del ultimo nodo entonces NULL
    cout << "El elemento no existe";

    }
    else if(anterior==NULL){ // Si entra aca significa que no entro al while porque el elemento que buscamos es el primero en la lista, entonces  tabl apunta al sig nodo y deleteamos el primer nodo que esta en BorrarTabl.
    tabl = tabl->ptrtabla;
    delete BorrarTabl;
    }
    else{ // El elemento esta en la lista pero no es el primero
        anterior->ptrtabla=BorrarTabl->ptrtabla;  // hacemos que el que estaba atras apunte al mismo que estaba apuntando borrartabl 'el siguiente del actual'
        delete BorrarTabl; // borramos borrartabl
    }

return tabl;
}

